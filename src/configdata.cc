#include "configdata.h"
namespace  Dandelion{
    std::string ConfigData::FindConfig(){
        std::string default_config_file = "config.json";
        std::ifstream f(default_config_file.c_str());
        if(f.good()){
            return  default_config_file;
        }
        return "";
    }

    bool ConfigData::LoadFromFile(const std::string& configfile){
    }

    void ConfigData::ShowHelp(){
        std::cout<<"show Help:\n";
    }

    void ConfigData::ShowVersion(){
        std::cout<<"show version:\n";
    }

    bool ConfigData::LoadLong(const option* longopts, int longpos, char* value){

        std::cout<<"longpos="<<longpos<<std::endl;
        std::string key = longopts[longpos].name; 
        std::cout<<"ke="<<key<<std::endl;
            if(key == "help"){
                ShowHelp();
                exit(0);
            }else if(key == "fast-open"){
                fastopen_ = true;
            }else if(key == "pid-file"){
                pid_file_ = value;
            }else if(key == "log-file"){
                log_file_ = value;
            }else if(key == "workers"){
                workers_ = atoi(value);
            }else if(key == "forbidden-ip="){
                int pos = 0;
                char *p = value;
                int len = 0;
                char c= 0;
                while(c=value[pos++]){
                    if(c==','){
                        forbidden_ip_.push_back(std::string(p,len));
                        len = 0;
                        p = value+pos;
                    }
                    len++;
                }
                if(len>0){
                    forbidden_ip_.push_back(std::string(p,len));
                }
            }else if(key == "user="){
                user_ = value;
            }else if(key == "manager-address="){
                manager_address_ = value;
            }else if(key == "version"){
                ShowVersion();
                exit(0);
            }
    
    }

    bool ConfigData::Load(int argc, char** argv){
        std::string  config_file = this->FindConfig(); 

        const char shortopts[] = "hd:s:p:k:m:c:t:vq";
        int flag = 0;
        struct option longopts[] = {
            {"help",no_argument, &flag,0},
            {"fast-open",required_argument, &flag,0},
            {"pid-file=",required_argument, &flag ,0},
            {"log-file=",required_argument, &flag,0},
            {"workers=",required_argument, &flag,0},
            {"forbidden-ip=",required_argument, &flag,0},
            {"user=",required_argument, &flag,0},
            {"manager-address=",required_argument, &flag,0},
            {"version",required_argument, &flag,0},
        };

        int ch;
        opterr = 0;
        int longpos = -1;
        while((ch=getopt_long(argc, argv, shortopts, longopts,&longpos))!=-1){
            std::cout<<"ch="<<ch<<" args="<<std::endl;
            switch(ch){
                case 0:
                    std::cout<<"hhhh\n";
                    LoadLong(longopts, longpos, optarg);
                    break;
                case 'p':
                    server_port_ = atoi(optarg);
                    break;
                case 'k':
                    password_  = std::string(optarg);
                case 'l':
                    local_port_ = atoi(optarg);
                    break;
                case 's':
                    server_host_= std::string(optarg);
                    break;
                case 'm':
                    method_ = std::string(optarg);
                    break;
                case 'b':
                    local_address_ = std::string(optarg);
                    break;
                case 'v':
                    verbose_ = true;
                    break;
                case 't':
                    timeout_=  atoi(optarg);
                    break;
                case 'h':
                    ShowHelp();
                    exit(0);
                case 'd':
                    daemon_ = true;
                    break;
                case 'q':
                    verbose_ = true;
                    break;
                case 'c':
                    config_file = "";
                    break;
            }
        }
        return true;
    }


} 

int main(int argc,char** argv){
    Dandelion::ConfigData config;
    config.Load(argc, argv);
    return 0;
}
