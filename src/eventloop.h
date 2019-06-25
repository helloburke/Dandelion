#ifndef DANDELION_EVENTLOOP_H_
#define DANDELION_EVENTLOOP_H_

#include <stdint.h>
#include <sys/epoll.h>
#include <vector>
#include "spdlog/spdlog.h"

namespace Dandelion{

    class TimedEvent{
        public:
        virtual void  callback()=0;
    };
    
    class FileEvent{
        public:
        virtual void  callback()=0;
    };

    class EventLoop{
        public:
            EventLoop();
            int Add(int fd,uint32_t events, FileEvent* file_event);
            int Del(int fd);
            void AddPeriodic(TimedEvent* event);
            void RemovePeriodic(TimedEvent* event);
            void Run();
            void Stop();
        private:
            int epoll_fd_;
            std::vector<TimedEvent*> timed_events_;
            int time_precise_;
            bool stop_;
            int last_active_time_;
    };
};
#endif
