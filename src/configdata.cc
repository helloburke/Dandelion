#include "configdata.h"
#include <sstream>
#include "univalue.h"
namespace  Dandelion{
    std::string ConfigData::FindConfig(int argc, char** argv){
        std::string config_file = "config.json";
        int ch;
        opterr = 0;
        ch=getopt(argc, argv, "c:");
        if(ch == 'c'){
            config_file = optarg;
        }

        std::cout<<"configfile="<<config_file<<std::endl;
        std::ifstream f(config_file.c_str());
        if(f.good()){
            std::string str((std::istreambuf_iterator<char>(f)),  
                                     std::istreambuf_iterator<char>()); 
            if(!LoadFromFile(str)){
                std::cout<<"invalid configfile, exit\n";
                exit(0);
            };
            return config_file;
        }
        std::cout<<"notfoudnconfig"<<std::endl;
        return "";
    }

    bool ConfigData::LoadFromFile(const std::string& configstr){
        if(configstr.size() == 0){
            return false;
        }
        UniValue val;
        if(!val.read(configstr)){
            std::cout<<"invalid config"<<std::endl;
            return false;
        };
        const std::vector<std::string>& keys = val.getKeys();
        for(int i=0; i<keys.size(); ++i)
        {
            const std::string& key = keys[i];
            UniValue uvalue = find_value(val, key);

            if(key == "server"){
                server_address_ =  uvalue.get_str();
            }else if(key == "server_port"){
                server_port_ = uvalue.get_int();
            }else if(key == "local_address"){
                local_address_ = uvalue.get_str();
            }else if(key == "local_port"){
                local_port_ = uvalue.get_int();
            }else if(key == "password"){
                password_ = uvalue.get_str();
            }else if(key == "port_password"){
                UniValue port_password_obj = uvalue.get_obj(); 
                std::vector<std::string> ports = port_password_obj.getKeys();
                for(int j=0; j<ports.size(); ++j){
                    short port = atoi(ports[j].c_str());
                    port_password_[port] = port_password_obj[ports[j]].get_str(); 
                }
            }else if(key == "manager_address"){
                manager_address_ = uvalue.get_str();
            }else if(key == "user"){
                user_ = uvalue.get_str();
            }else if(key == "timeout"){
                timeout_ = uvalue.get_int();
            }else if(key == "fast-open"){
                fastopen_ = true;
            }else if(key == "pid-file"){
                pid_file_ = uvalue.get_str();
            }else if(key == "log-file"){
                log_file_ = uvalue.get_str();
            }else if(key == "daemon"){
                daemon_ = uvalue.get_bool();
            }else if(key == "workers"){
                workers_ = uvalue.get_int(); 
            }else if(key == "forbidden-ip"){
                int pos1 = 0, pos2 = 0;
                std::string s = uvalue.get_str();
                while(true){
                    pos2 = s.find(",",pos1);
                    if(pos2 == std::string::npos){
                        pos2 = s.size();
                        std::cout<<s.substr(pos1, pos2-pos1)<<std::endl;
                        forbidden_ip_.push_back(s.substr(pos1, pos2-pos1));
                        break;
                    }
                    forbidden_ip_.push_back(s.substr(pos1, pos2-pos1));
                    pos1 = pos2+1;
                }
            }
        }
        return true;
    }

    void ConfigData::ShowHelp(){
        std::cout<<"show Help:\n";
    }

    void ConfigData::ShowVersion(){
        std::cout<<"show version:\n";
    }

    bool ConfigData::LoadLong(const option* longopts, int longpos, char* value){

        std::string key = longopts[longpos].name; 
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

        FindConfig(argc, argv); 

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
        optind = 0;
        int longpos = -1;
        while((ch=getopt_long(argc, argv, shortopts, longopts,&longpos))!=-1){
            switch(ch){
                case 0:
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
                    server_address_= std::string(optarg);
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
                    daemon_ = optarg;
                    break;
                case 'q':
                    verbose_ = true;
                    break;
            }
        }

        if(port_password_.size() == 0){
            port_password_[server_port_] =  password_;
        }
        return true;
    }

    std::string ConfigData::ToString(){
        std::stringstream ss;
        ss<<"server_address="<<server_address_<<"|";
        ss<<"server_port="<<server_port_<<"|";
        ss<<"local_address="<<local_address_<<"|";
        ss<<"local_port=="<<local_port_<<"|";
        ss<<"password="<<password_<<"|";
        ss<<"port_password_="<<printMap(port_password_)<<"|";
        ss<<"method="<<method_<<"|";
        ss<<"manager_address="<<manager_address_<<"|";
        ss<<"forbidden_ip="<<printVector(forbidden_ip_)<<"|";
        ss<<"pid-file="<<pid_file_<<"|";
        ss<<"log-file="<<log_file_<<"|";
        ss<<"daemon="<<daemon_<<"|";
        ss<<"verbose_="<<verbose_<<"|";
        ss<<"fastopen="<<fastopen_<<"|";
        ss<<"timeout="<<timeout_<<"|";
        ss<<"workers="<<workers_<<"|";
        return ss.str();
    }
} 

/*
int main(int argc,char** argv){
    Dandelion::ConfigData config;
    config.Load(argc, argv);
    std::cout<<config.ToString();
    return 0;
}
*/
