#include "configdata.h"
using namespace Dandelion;

int main(int argc, char** argv){
    ConfigData config;
    config.Load(argc, argv);
    if(config.daemon()){
        RunAsDaemon();
    }
    return 0;
}
