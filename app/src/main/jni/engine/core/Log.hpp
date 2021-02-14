#pragma once

#include <string>
#include <sstream>

class ILog
{
public:
    virtual ~ILog() = default;
    virtual void writeMessage(std::string tag, std::string message) = 0;
    virtual void assert_condition(bool condition, std::string conditionAsString, std::string tag, std::string message) = 0;
};

struct Log {
public:
    template <typename... Args>
    static void i(std::string tag, Args... args) {
        std::ostringstream out;
        (void)(out << ... << args);
        Log::info(tag, out.str());
    }
    static void info(std::string tag, std::string message);
    static void assert_condition(bool cond, std::string condAsString, std::string tag, std::string message);
    static void setHandler(ILog* handler);
private:
    static std::unique_ptr<ILog> m_handler;
};
