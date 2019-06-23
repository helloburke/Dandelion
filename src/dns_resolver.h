#ifndef DANDELION_DNS_RESOLVER_H_
#define DANDELION_DNS_RESOLVER_H_
#include "eventloop.h"
namespace Dandelion{
class DnsResolver{
    public:
        bool AddToLoop(EventLoop& loop);
};
};
#endif
