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

namespace coolserver{

class LogEvent {
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent();
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
    std::string m_content;
};

class LogLevel{
    public:
        enum Level{
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5
        };
};

class LogFormatter{

}

class LogAppender{
    public:
        typedef std::shared_ptr<LogAppender> ptr;
        virtual ~LogAppender(){}
        virtual void log(LogLevel::Level level, LogEvent::ptr event) = 0;
        void setFormatter(LogFormatter::ptr val){m_formatter = val;}
        LogFormatter::ptr getFormatter() const (return m_formatter;)
    protected:
        LogLevel::Level m_level;
        LogFormatter::ptr m_formatter;
};

class Logger{
    public:
        typedef std::shared_ptr<Logger> ptr;
        Logger(const std::string& name = "root");
        void log(LogLevel::Level level, LogEvent::ptr event);
        void debug(LogEvent::ptr event)
        void warn(LogEvent::ptr event);
        void info(LogEvent::ptr event);
        void error(LogEvent::ptr event);
        void fatal(LogEvent::ptr event);
        void addAppender(LogAppender::ptr appender);
        void delAppender(LogAppender::ptr appender);
        LogLevel::Level getLevel() const {return m_level;}
        void setLevel(LogLevel::Level val){m_level = val;}

    private:
        std::string m_name;
        LogLevel::Level m_level;
        std::list<LogAppender::ptr> m_appenders;
};


class StdoutLogAppender : public LogAppender{
    public:
        typedef std::shared_ptr<StdoutLogAppender> ptr;
        void log(LogLevel::Level level, LogEvent::ptr event) override;
};

class FileLogAppender: public LogAppender{
    public:
        typedef std::shared_ptr<FileoutAppender> ptr;
        FileLogAppender(const std::string& filename);
        void log(LogLevel::Level level, LogEvent::ptr event) override;
        void reopen();
    private:
        std::string m_filename;
        std::ofstream m_filestream;
};

}

#endif