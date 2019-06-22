#include "util.h"
namespace Dandelion{

    /*from redis's daemonize*/
    void RunAsDaemon(){
      int fd;
    
        if (fork() != 0) exit(0); /* parent exits */
        setsid(); /* create a new session */
    
        if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
            dup2(fd, STDIN_FILENO);
            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            if (fd > STDERR_FILENO) close(fd);
        } 
    }

    std::string printVector(const std::vector<std::string>& v){
        std::string s = "";
        for(int i=0; i<v.size(); ++i){
            s += v[i];
        }
        return s;
    }

    std::string printMap(const std::unordered_map<short, std::string>& v){
        std::string s = "";
        std::unordered_map<short, std::string>::const_iterator iter;
        for(iter=v.begin(); iter!=v.end(); ++iter){
            s += iter->first +" = " + iter->second+"\n";
        }
        return s;
    }
}
