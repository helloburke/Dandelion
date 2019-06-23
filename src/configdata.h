#ifndef DANDELION_CONFIG_H_
#define DANDELION_CONFIG_H_

#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "util.h"

namespace Dandelion{

class ConfigData{
private:
    std::string server_address_;
	short server_port_;

    std::string local_address_;
    short local_port_;

    std::string password_;
    std::unordered_map<short, std::string> port_password_;
    std::string method_;
    std::string manager_address_;
    std::string user_;
    std::vector<std::string> forbidden_ip_;
    std::string pid_file_;
    std::string log_file_;

    bool daemon_;
    bool verbose_;
    bool fastopen_;

    int timeout_;
    int workers_;
    bool is_local_;
private:
    std::string FindConfig(int argc, char** argv);
    bool LoadFromFile(const std::string& configfile);
    void ShowHelp();
    void ShowVersion();
    bool LoadLong(const option* longopts, int longpos, char* value);

public:
    ConfigData(){
        method_ = "aes-256-cfb";
        password_ = "";
        server_address_ = "0.0.0.0";
        server_port_ = 8399; 

        local_address_ = "127.0.0.1";
        local_port_ = 1080;

        pid_file_ = "/var/log/dandelion.pid";
        log_file_ = "/var/log/dandelion.log";
        timeout_ = 0;
        workers_ = 1;
        verbose_ = false;
        daemon_ = false;
        verbose_ = false;
        fastopen_ = true;
        is_local_= false;
    }

    bool daemon(){
        return daemon_;
    }

    bool is_local(){return is_local_;}
    short local_port(){return local_port_;}
    std::string local_address(){return local_address_;}
    bool fastopen(){return fastopen_;}

    short server_port(){return server_port_;}
    std::string server_address(){return server_address_;}
    void set_fastopen(bool fast_open){fastopen_ = fast_open;}
    void set_server_port(short port){server_port_ = port;}
    void set_server_address(const std::string& address){server_address_ = address;}
    void set_password(const std::string& password){password_= password;}

    std::unordered_map<short, std::string> port_password(){
        return port_password();
    }

    bool Load(int argc, char** argv);
    std::string ToString();
};

}
#endif

