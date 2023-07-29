#include "coolserver/config.h"
#include "coolserver/log.h"
#include <yaml-cpp/yaml.h>
coolserver::ConfigVar<int>::ptr g_int_value_config =
    coolserver::Config::Lookup("system.port", (int)8080, "system port");

coolserver::ConfigVar<float>::ptr g_int_valuex_config =
    coolserver::Config::Lookup("system.port", (float)8080, "system port");

coolserver::ConfigVar<std::vector<int> >::ptr g_int_vec_value_config =
    coolserver::Config::Lookup("system.int_vec", std::vector<int>{1,2}, "system int vec");

coolserver::ConfigVar<std::list<int> >::ptr g_int_list_value_config =
    coolserver::Config::Lookup("system.list_vec", std::list<int>{10,20}, "system int vec");
    
coolserver::ConfigVar<std::set<int> >::ptr g_int_set_value_config =
    coolserver::Config::Lookup("system.set_vec", std::set<int>{10,20}, "system int vec");

coolserver::ConfigVar<std::map<std::string,int> >::ptr g_int_map_value_config =
    coolserver::Config::Lookup("system.str_int_map", std::map<std::string, int>{{"hello",20}}, "system int vec");



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

#define XX(g_var, name, prefix) \
    { \
        auto& v = g_var->getValue(); \
        for(auto& i : v){ \
            COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) <<  #prefix " " #name ": " << i; \
        } \
        COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << #prefix " " #name " yaml: " <<g_var->toString(); \
    }

#define XX_M(g_var, name, prefix) \
    { \
        auto& v = g_var->getValue(); \
        for(auto& i : v){ \
            COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) <<  #prefix " " #name ": {"  \
                    << i.first << " - " <<i.second << "}"; \
        } \
        COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << #prefix " " #name " yaml: " <<g_var->toString(); \
    }

    XX(g_int_list_value_config,int_list, before);
    XX(g_int_vec_value_config,int_vec, before);
    XX(g_int_set_value_config,set_list, before);
    XX_M(g_int_map_value_config,str_int_map, before);

    YAML::Node root = YAML::LoadFile("/home/lance/Desktop/server-demo/bin/conf/log.yml");
    coolserver::Config::LoadFromYaml(root);
    // print_yaml(root,0);
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << "after: " << g_int_value_config->getValue();
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << "after: " << g_int_value_config->toString();

    XX(g_int_vec_value_config,int_vec, after);
    XX(g_int_list_value_config,int_list, after);
    XX(g_int_set_value_config,set_list, after);
    XX_M(g_int_map_value_config,str_int_map, after);

}

class Resume{
    public:
        Resume(){};
        std::string m_name = "";
        int m_age = 0;
        std::string m_university = "";

        std::string toString() const{
            std::stringstream ss;
            ss <<"[Employee name: " <<m_name
                <<"age: " << m_age
                <<"graduate from: " << m_university << "]";
            return ss.str();
        }
};
namespace coolserver{
        template<>
        class LexicalCast<std::string, Resume>{
            public:
                Resume operator()(const std::string& v){
                    YAML::Node node = YAML::Load(v);
                    Resume r;
                    r.m_name = node["name"].as<std::string>();
                    r.m_name = node["age"].as<int>();
                    r.m_name = node["university"].as<std::string>();
                    return r;
                }
        };

        template<>
        class LexicalCast<Resume, std::string >{
            public:
                std::string operator()(const Resume& p){
                    YAML::Node node;
                    node["name"] = p.m_name;
                    node["age"] = p.m_age;
                    node["university"] = p.m_university;
                    std::stringstream ss;
                    ss << node;

                    return ss.str();
                }
        };
}
coolserver::ConfigVar<Resume>::ptr g_employee =
        coolserver::Config::Lookup("class.employee", Resume(), "system port");
        

void test_class(){ //test should accept all kinds all input class type
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) <<"before: "<< g_employee->getValue().toString() << " - " << g_employee->toString();
    YAML::Node root = YAML::LoadFile("/home/lance/Desktop/server-demo/bin/conf/log.yml");
    coolserver::Config::LoadFromYaml(root);
    // COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) <<"after: " << g_employee->getValue().toString() << " - " << g_employee->toString();
}
int main(int argc, char** argv){
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << g_int_value_config -> getValue();
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << g_int_value_config -> toString();

    // test_yaml();
    // test_config();
    test_class();
    return 0;
}