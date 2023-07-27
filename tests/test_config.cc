#include "coolserver/config.h"
#include "coolserver/log.h"

coolserver::ConfigVar<int>::ptr g_int_value_config =
    coolserver::Config::Lookup("system.port", (int)8080, "system port");
int main(int argc, char** argv){
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << g_int_value_config -> getValue();
    COOLSERVER_LOG_INFO(COOLSERVER_LOG_ROOT()) << g_int_value_config -> toString();
    return 0;
}