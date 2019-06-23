#include "tcp_relay.h"
namespace Dandelion{

    bool TcpRelay::Init(){
        short listen_port = 0;
        std::string listen_addr = "";
        if(config_.is_local()){
            listen_port = config_.local_port();
            listen_addr = config_.local_address();
        }else{
            listen_port = config_.server_port();
            listen_addr = config_.server_address();
        }


        //getipfrom hostname 
        addrinfo hints, *res;
        in_addr addr;
        int err;
        memset(&hints, 0, sizeof(addrinfo));
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_family = AF_INET;

        if((err = getaddrinfo(listen_addr.c_str(), NULL, &hints, &res)) != 0){
            spdlog::error("error {} : {}", err, gai_strerror(err));
            return false;
        }

        addr.s_addr = ((sockaddr_in*)(res->ai_addr))->sin_addr.s_addr;
        freeaddrinfo(res);

        int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if(sock < 0 ){
            spdlog::error("getscoketfail errno[{}]",errno);
            return false;
        }

        bind(sock, (struct sockaddr *)(&addr.s_addr) , sizeof(struct sockaddr_in));
        //set unblocking
        fcntl(sock, F_SETFL, O_NONBLOCK);
        if(config_.fastopen()){
            fcntl(sock, F_SETFL, O_NONBLOCK);
            int qlen = 5;                 // Value to be chosen by application
            if(setsockopt(sock, IPPROTO_TCP/*SOL_TCP*/, 23/*TCP_FASTOPEN*/, &qlen, sizeof(qlen))<0){
                spdlog::error("setfastopenfail");
                config_.set_fastopen(false);
            };
        }
        listen(sock,1024);
        server_socket_ = sock; 
        return true;
    }

    TcpRelay::TcpRelay(const ConfigData& config, const DnsResolver& dns_resolver, bool is_local){
        config_ = config;
        dns_resolver_ = dns_resolver;
        is_local_ = is_local;
    };

    bool TcpRelay::AddToLoop(EventLoop& loop){
        return true;
    }
};
