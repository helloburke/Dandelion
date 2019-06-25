#include "eventloop.h"
#include <sys/epoll.h>

namespace Dandelion{
    EventLoop::EventLoop()
    {
        epoll_fd_ = epoll_create(1024);
        stop_ = false;
        time_precise_ = 10;
        last_active_time_ = 0;
    }

    int EventLoop::Add(int fd,uint32_t events, FileEvent* file_event){
        epoll_event e;
        e.events = events;
        e.data.ptr = file_event; 
        return  epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &e);
    };

    int EventLoop::Del(int fd){
        epoll_event e;
        return  epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, &e);
    };

    void EventLoop::AddPeriodic(TimedEvent* event){
        timed_events_.push_back(event);
    }

    void EventLoop::RemovePeriodic(TimedEvent* event){
        std::vector<TimedEvent*>::iterator iter;
        for(iter=timed_events_.begin(); iter!=timed_events_.end(); ++iter){
            if(*iter == event){
                timed_events_.erase(iter);
                break;
            }
        }
    }

    void EventLoop::Run(){
        while(!stop_){
            epoll_event events[128];
            int num = epoll_wait(epoll_fd_, events, 128,time_precise_);
            if(num<0){
                spdlog::error("epollwait fail errno={}",errno);
            }else if(num >0){
                for(int i=0; i<num; ++i){
                    epoll_event event = events[i];
                    ((FileEvent*)event.data.ptr)->callback();
                }
            }

            int now = time(NULL);
            if(now - last_active_time_ >=time_precise_){
                for(auto timed_event : timed_events_){
                    timed_event->callback();
                }
                last_active_time_ = now;
            }
        }
    };

    void EventLoop::Stop(){
        stop_ = true;
    };
};
