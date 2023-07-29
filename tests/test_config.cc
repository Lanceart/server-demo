#include "../coolserver/config.h"
#include "../coolserver/log.h"
#include <yaml-cpp/yaml.h>
coolserver::ConfigVar<int>::ptr g_int_value_config =
    coolserver::Config::Lookup("system.port", (int)8080, "system port");

coolserver::ConfigVar<std::vector<int> >::ptr g_int_vec_value_config =
    coolserver::Config::Lookup("system.int_vec", std::vector<int>{1,2}, "system int vec");

void print_yaml(const YAML::Node& node, int level) {
    if(node.IsScalar()) {
        COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << std::string(level * 4, ' ')
            << node.Scalar() << " - " << node.Type() << " - " << level;
    } else if(node.IsNull()) {
        COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << std::string(level * 4, ' ')
            << "NULL - " << node.Type() << " - " << level;
    } else if(node.IsMap()) {
        for(auto it = node.begin();
                it != node.end(); ++it) {
            COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << std::string(level * 4, ' ')
                    << it->first << " - " << it->second.Type() << " - " << level;
            print_yaml(it->second, level + 1);
        }
    } else if(node.IsSequence()) {
        for(size_t i = 0; i < node.size(); ++i) {
            COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << std::string(level * 4, ' ')
                << i << " - " << node[i].Type() << " - " << level;
            print_yaml(node[i], level + 1);
        }
    }
}

void test_yaml(){
    YAML::Node root = YAML::LoadFile("/home/lance/Desktop/server-demo/bin/conf/log.yml");
    print_yaml(root,0);
    // COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) <<root;
}

void test_config() {
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << "before: " << g_int_value_config->getValue();
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << "before: " << g_int_value_config->toString();
    YAML::Node root = YAML::LoadFile("/home/lance/Desktop/server-demo/bin/conf/log.yml");
    coolserver::Config::LoadFromYaml(root);
    print_yaml(root,0);
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << "after: " << g_int_value_config->getValue();
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << "after: " << g_int_value_config->toString();


    auto v = g_int_vec_value_config->getValue();
    for(auto& i : v){
        COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << "int_vec: " << i;
    }
}
int main(int argc, char** argv){
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << g_int_value_config -> getValue();
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << g_int_value_config -> toString();

    // test_yaml();
    test_config();
    return 0;
}