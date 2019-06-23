#ifndef DANDELION_EVENTLOOP_H_
#define DANDELION_EVENTLOOP_H_

namespace Dandelion{
    class EventLoop{
        public:
            void Add();
            void Del();
            void Run();
        private:
            int epoll_fd_;
    };
};
#endif
