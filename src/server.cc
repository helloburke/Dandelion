#include "configdata.h"
#include "spdlog/spdlog.h"
#include "pthread.h"
#include "dns_resolver.h"
#include "tcp_relay.h"
#include "udp_relay.h"
using namespace Dandelion;

#include "spdlog/sinks/daily_file_sink.h"

void* func(void* data){
    spdlog::info("this is pthread");
    return NULL;
}
int main(int argc, char** argv){
    ConfigData config;
    config.Load(argc, argv, false);
    std::cout<<config.ToString()<<std::endl;
    if(config.daemon()){
        //TODO: anzhao config's user set user
        RunAsDaemon();
    }

    auto daily_logger = spdlog::daily_logger_mt("server", "log/server.log", 0, 0); 
    spdlog::set_default_logger(daily_logger);

    //TODO: checkconfig

    DnsResolver dns_resolver;
    std::vector<TcpRelay> tcp_servers;
    std::vector<UdpRelay> udp_servers;
    for(auto &item: config.port_password()){
        config.set_server_port(item.first);
        config.set_password(item.second);
        tcp_servers.push_back(TcpRelay(config,dns_resolver, false));
        udp_servers.push_back(UdpRelay(config,dns_resolver, false));
    }

    //TODO: add sigal handle

    EventLoop event_loop;  
    dns_resolver.AddToLoop(event_loop);
    for(auto item: tcp_servers){
        if(item.Init()){
            //spdlog::info("initsucc");
            item.AddToLoop(event_loop);
        }else{
            spdlog::critical("server init fail");
            exit(-1);
        }
    }

    for(auto item: udp_servers){
        if(item.Init()){
            //spdlog::info("initsucc");
            item.AddToLoop(event_loop);
        }else{
            spdlog::critical("server init fail");
            exit(-1);
        }
    }
    event_loop.Run();
    spdlog::info("alldone"); 
    return 0;
}
