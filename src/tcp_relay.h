#ifndef DANDELION_TCP_RELAY_H_
#define DANDELION_TCP_RELAY_H_

#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "eventloop.h"
#include "configdata.h"
#include "dns_resolver.h"
#include "string.h"
#include "spdlog/spdlog.h"

namespace Dandelion{
    class TcpRelay{
    public:
        TcpRelay(const ConfigData& config, const DnsResolver& dns_resolver, bool is_local);
        bool AddToLoop(EventLoop& loop);
        bool Init();
    private:
        ConfigData config_;
        DnsResolver dns_resolver_;
        bool is_local_;
        EventLoop event_loop;
        int server_socket_;
    };
};
#endif
