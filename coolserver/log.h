#ifndef __COOLSERVER_LOG_H__
#define __COOLSERVER_LOG_H__

#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdarg.h>
#include <map>
#include <utility>

#define COOLSERVER_LOG_LEVEL(logger, level) \
    if(logger->getLevel() <= level) \
        coolserver::LogEventWrap(coolserver::LogEvent::ptr(new coolserver::LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, coolserver::GetThreadId(),\
                coolserver::GetFiberId(), time(0) ))).getSS()

/**
 * @brief 使用流式方式将日志级别debug的日志写入到logger
 */
#define COOLSERVER_LOG_DEBUG(logger) COOLSERVER_LOG_LEVEL(logger, coolserver::LogLevel::DEBUG)

/**
 * @brief 使用流式方式将日志级别info的日志写入到logger
 */
#define COOLSERVER_LOG_INFO(logger) COOLSERVER_LOG_LEVEL(logger, coolserver::LogLevel::INFO)

/**
 * @brief 使用流式方式将日志级别warn的日志写入到logger
 */
#define COOLSERVER_LOG_WARN(logger) COOLSERVER_LOG_LEVEL(logger, coolserver::LogLevel::WARN)

/**
 * @brief 使用流式方式将日志级别error的日志写入到logger
 */
#define COOLSERVER_LOG_ERROR(logger) COOLSERVER_LOG_LEVEL(logger, coolserver::LogLevel::ERROR)

/**
 * @brief 使用流式方式将日志级别fatal的日志写入到logger
 */
#define COOLSERVER_LOG_FATAL(logger) COOLSERVER_LOG_LEVEL(logger, coolserver::LogLevel::FATAL)



namespace coolserver{
class Logger;
class LogLevel{
    public:
        enum Level{
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5
        };

    static const char* ToString(LogLevel::Level level);
};

class LogEvent {
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char* file, int32_t line, uint32_t elapse, 
                uint32_t thread_id, uint32_t fiber_id, uint64_t time);

    
    const char* getFile() const {return m_file;}
    int32_t getLine() const {return m_line;}
    uint32_t getElapse() const {return m_elapse;}
    uint32_t getThreadId() const {return m_threadId;}
    uint32_t getFiberId() const {return m_fiberId;}
    uint32_t getTime() const {return m_time;}
    std::string getContent() const {return m_ss.str();}
    std::shared_ptr<Logger> getLogger() const {return m_logger;}
    LogLevel::Level getLevel() const {return m_level;}
    

    std::stringstream& getSS() {return m_ss;}
    
private:
    /// filename
    const char* m_file = nullptr;
    /// lines
    int32_t m_line = 0;
    /// timer
    uint32_t m_elapse = 0;
    /// threadID
    uint32_t m_threadId = 0;
    /// coroutineID
    uint32_t m_fiberId = 0;
    /// timeStamp
    uint64_t m_time = 0;
    std::stringstream m_ss;

    std::shared_ptr<Logger> m_logger;
    LogLevel::Level m_level;
};
class LogEventWrap{
    public:
        LogEventWrap(LogEvent::ptr e);
        ~LogEventWrap();
        std::stringstream& getSS();

    private:
        LogEvent::ptr m_event;
};


class LogFormatter{
    public:
        typedef std::shared_ptr<LogFormatter> ptr;
        LogFormatter(const std::string& pattern);

        //t% %thread_id %m %n
        std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
    public:
        class FormatItem{
            public:
                typedef std::shared_ptr<FormatItem> ptr;
                // FormatItem(const std::string& fmt = "");
                virtual ~FormatItem(){}
                virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
        };

        void init();
    private:
        std::string m_pattern;
        std::vector<FormatItem::ptr> m_items;
};

class LogAppender{
    public:
        typedef std::shared_ptr<LogAppender> ptr;
        virtual ~LogAppender(){}
        virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
        void setFormatter(LogFormatter::ptr val){m_formatter = val;}
        LogFormatter::ptr getFormatter() const {return m_formatter;}
    protected:
        LogLevel::Level m_level = LogLevel::DEBUG;//must be  init
        LogFormatter::ptr m_formatter;
};

class Logger : public std::enable_shared_from_this<Logger>{
    public:
        typedef std::shared_ptr<Logger> ptr;
        Logger(const std::string& name = "root");
        void log(LogLevel::Level level, LogEvent::ptr event);
        void debug(LogEvent::ptr event);
        void warn(LogEvent::ptr event);
        void info(LogEvent::ptr event);
        void error(LogEvent::ptr event);
        void fatal(LogEvent::ptr event);
        void addAppender(LogAppender::ptr appender);
        void delAppender(LogAppender::ptr appender);
        LogLevel::Level getLevel() const {return m_level;}
        void setLevel(LogLevel::Level val){m_level = val;}

        const std::string& getName() const {return m_name;}
    private:
        std::string m_name;
        LogLevel::Level m_level;
        std::list<LogAppender::ptr> m_appenders;
        LogFormatter::ptr m_formatter;
};


class StdoutLogAppender : public LogAppender{
    public:
        typedef std::shared_ptr<StdoutLogAppender> ptr;
        void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;
};

class FileLogAppender: public LogAppender{
    public:
        typedef std::shared_ptr<FileLogAppender> ptr;
        FileLogAppender(const std::string& filename);
        void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;
        bool reopen();
    private:
        std::string m_filename;
        std::ofstream m_filestream;
};

}

#endif