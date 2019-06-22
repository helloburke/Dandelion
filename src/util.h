#ifndef DANDELION_UTIL_H_
#define DANDELION_UTIL_H_

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include<fcntl.h>
#include<string>
#include<vector>
#include<unordered_map>

namespace Dandelion{
    void RunAsDaemon();
    std::string printVector(const std::vector<std::string>& v);
    std::string printMap(const std::unordered_map<short, std::string>& v);
}
#endif
