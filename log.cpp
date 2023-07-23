#include "log.h"
namespace coolserver{
    static const char* ToString(LogLevel::Level level){
        switch(level) {
#define XX(name) \
    case LogLevel::name: \
        return #name; \
        break;

    XX(DEBUG);
    XX(INFO);
    XX(WARN);
    XX(ERROR);
    XX(FATAL);
#undef XX
    default:
        return "UNKNOW";
    }
    return "UNKNOW";
    }

    Logger(const std::string& name)
            :m_name(name){
        
    }
    void Logger::addAppender(LogAppender::ptr appender){
        m_appenders.push_back(appender);
    }
    void Logger::delAppender(LogAppender::ptr appender){
        for(auto it = m_appenders.begin();
                it != m_appenders.end();
                ++it){
            if(*it == appender){
                m_appenders.erase(it);
                break;
            }
        }
    }
    void Logger::log(LogLevel::Level level, LogEvent::ptr event){
        if(level >= m_level){
            for(auto& i : m_appenders){
                i->log(level,event);
            }
        }
    }
    void Logger::debug(LogEvent::ptr event){
        debug(LogLevel::DEBUG, event);
    }
    void Logger::warn(LogEvent::ptr event){
        debug(LogLevel::WARN, event);
    }
    void Logger::info(LogEvent::ptr event){
        debug(LogLevel::INFO, event);
    }
    void Logger::error(LogEvent::ptr event){
        debug(LogLevel::ERROR, event)
    
    }
    void Logger::fatal(LogEvent::ptr event){
        debug(LogLevel::FATAL, event)
    
    }
    FileLogAppender::FileLogAppender(const std::string& filename)
            :m_filename(filename){

            }


    void StdoutLogAppender::log(LogLevel::Level level, LogEvent::ptr event){
        if(level >= m_level){
            std::cout << m_formatter.format(event);
        }
    }

    bool FileLogAppender::reopen(){
        if(m_filestream){
            m_filestream.close();
        }
        m_filename.open(m_filename);
        return !!m_filestream;
    }

    void FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event){
        if(level >= m_level){
            m_filestream << m_formatter.format(event);
        }
    }

    LogFormatter::LogFormatter(const std::string& pattern)
            :m_pattern(pattern){

    }

    void LogFormatter::init(){
        //str,format,type
        std::vector<std::pair<std::string, int> > vec;
        std::string nstr;

        for(size_t i=0;i<m_pattern.size();i++){
            if(m_pattern[i] != '%'){
                nstr.append(1,m_pattern[i]);
                continue;
            }
            if((i+1) < m_pattern.size()){
                if(m_pattern[i+1] == '%'){
                    nstr.append(1,'%');
                    continue;
                }
            }

            size_t  n = i+1;
            int fmt_status = 0;
            size_t fmt_begin = 0;

            std::string str;
            std::string fmt;
            while(n < m_pattern.size()){
                if(isspace(m_pattern[n])){
                    break;
                }
                if(fmt_status == 0){
                    if(m_pattern[n]=='{'){
                        str = m_pattern.substr(i+1, n-i-1);
                        fmt_status = 1;
                        fmt_begin =n;
                        ++n;
                        continue;
                    }
                }
                if(fmt_status == 1){
                    if(m_pattern[n] == '}'){
                        fmt = m_pattern.substr(fmt_begin + 1, n - fmt_begin -1);
                        fmt_status = 2;
                        break;
                    }
                }
            }

            if(fmt_status == 0){
                if(!nstr.empty()){
                    vec.push_back(std::make_pair(nstr,"",0));
                }

                str = m_pattern.substr(i+1,n-i-1);
                vec.push_back(std::make_tuple(str,fmt,1));
                i=n;
            }else if(fmt_status == 1){
                std::cout << "pattern parse error: " << m_pattern << " - " << m_pattern.substr(i) << str::endl;
                vec.push_back(std::make_tuple("<<pattern_error>>", fmt,0));
            }else if(fmt_status == 2){
                if(!nstr.empty()){
                    vec.push_back(std::make_pair(nstr,"",0));
                }
                vec.push_back(std::make_tuple(str,fmt,1));
                i = n;
            }
        }

        if(!nstr.empty()){
            vec.push_back(std::make_pair(nstr, "",0));
        }

        //%m -- message
        //%p -- level
        //%r -- timespend after start
        //%t -- corotine Id
        //%n -- change line
        //%d -- time
        //%f -- filename
        //%l -- lines
    }

    class MessageFormatItem : public LogFormatter::FormatItem{
            public:
                void format(std::ostream& os, LogLevel::Level level, LogEvent::ptr event) override{
                    os << event-> getContent();
                }
    };

    class LevelFormatItem : public LogFormatter::FormatItem{
            public:
                void format(std::ostream& os, LogLevel::Level level, LogEvent::ptr event) override{
                    os << LogLevel::ToString(level);
                }
    };

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


    std::string LogFormatter::format(LogLevel::Level level, LogEvent::ptr event){
        std::stringstream ss;
        for(auto& i : m_items){
            i->format(ss,level, event);
        }
        return ss.str();
    }
}