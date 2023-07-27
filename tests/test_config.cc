#include "../coolserver/config.h"
#include "../coolserver/log.h"
#include <yaml-cpp/yaml.h>
coolserver::ConfigVar<int>::ptr g_int_value_config =
    coolserver::Config::Lookup("system.port", (int)8080, "system port");

void print_yaml(const YAML::Node& node, int level) {
    if(node.IsScalar()) {
        COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << std::string(level * 4, ' ')
            << node.Scalar() << " - " << node.Tag() << " - " << level;
    } else if(node.IsNull()) {
        COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << std::string(level * 4, ' ')
            << "NULL - " << node.Tag() << " - " << level;
    } else if(node.IsMap()) {
        for(auto it = node.begin();
                it != node.end(); ++it) {
            COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << std::string(level * 4, ' ')
                    << it->first << " - " << it->second.Tag() << " - " << level;
            print_yaml(it->second, level + 1);
        }
    } else if(node.IsSequence()) {
        for(size_t i = 0; i < node.size(); ++i) {
            COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << std::string(level * 4, ' ')
                << i << " - " << node[i].Tag() << " - " << level;
            print_yaml(node[i], level + 1);
        }
    }
}

void test_yaml(){
    YAML::Node root = YAML::LoadFile("/home/lance/Desktop/server-demo/bin/conf/log.yml");
    print_yaml(root,0);
    // COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) <<root;
}   
int main(int argc, char** argv){
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << g_int_value_config -> getValue();
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << g_int_value_config -> toString();

    test_yaml();
    return 0;
}