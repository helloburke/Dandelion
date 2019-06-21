#ifndef DANDELION_CONFIG_H_
#define DANDELION_CONFIG_H_

#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

namespace Dandelion{

class ConfigData{
private:
    std::string server_host_;
	short server_port_;

    std::string local_address_;
    short local_port_;

    std::string password_;
    std::string port_password_;
    std::string method_;
    std::string manager_address_;
    std::string user_;
    std::vector<std::string> forbidden_ip_;
    std::string pid_file_;
    std::string log_file_;

    bool daemon_;
    bool verbose_;
    bool fastopen_;

    short timeout_;
    short workers_;
    std::string FindConfig();
    bool LoadFromFile(const std::string& configfile);
    void ShowHelp();
    void ShowVersion();
    bool LoadLong(const option* longopts, int longpos, char* value);

public:
    ConfigData(){
        method_ = "aes-256-cfb";
        password_ = "";
        port_password_ = "";
        server_host_ = "0.0.0.0";
        server_port_ = 8399; 

        local_address_ = "127.0.0.1";
        local_port_ = 1080;
    }

    bool Load(int argc, char** argv);
};

}
#endif

