#include "../coolserver/config.h"
#include "../coolserver/log.h"
#include <yaml-cpp/yaml.h>
coolserver::ConfigVar<int>::ptr g_int_value_config =
    coolserver::Config::Lookup("system.port", (int)8080, "system port");

void test_yaml(){
    YAML::Node root = YAML::LoadFile("/home/lance/Desktop/server-demo/bin/conf/log.yml");
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) <<root;
}   
int main(int argc, char** argv){
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << g_int_value_config -> getValue();
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << g_int_value_config -> toString();

    test_yaml();
    return 0;
}