#include<iostream>
#include<thread>
#include "../coolserver/log.h"
#include "../coolserver/util.h"
int main(int argc, char ** argv)
{
    coolserver::Logger::ptr logger(new coolserver::Logger);
    logger->addAppender(coolserver::LogAppender::ptr(new coolserver::StdoutLogAppender));


    coolserver::FileLogAppender::ptr file_appender(new coolserver::FileLogAppender("./log.txt"));
    logger->addAppender(file_appender);
    // coolserver::LogEvent::ptr event(new coolserver::LogEvent(__FILE__, __LINE__, 0, coolserver::GetThreadId(),coolserver::GetFiberId(), 2,time(0)));

    // logger->log(coolserver::LogLevel::DEBUG, event);
    std::cout << "Hello World!" <<std::endl;
    COOLSERVER_LOG_INFO(logger) << "tests mircal";
    COOLSERVER_LOG_ERROR(logger) << "opps a error";

    COOLSERVER_LOG_FMT_ERROR(logger, "test fmt error %s", "aa");

    auto l = coolserver::LoggerMgr::GetInstance()->getLogger("xx");
    COOLSERVER_LOG_INFO(l) << "xxx";

    return 0;
}
