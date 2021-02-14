#include "Log.hpp"
#include <memory>

std::unique_ptr<ILog> Log::m_handler = nullptr;

void Log::info(std::string tag, std::string message) {
    m_handler->writeMessage(tag, message);
}

void Log::assert_condition(bool cond, std::string condAsString, std::string tag, std::string message)
{
    m_handler->assert_condition(cond, condAsString, tag, message);
}

void Log::setHandler(ILog* handler)
{
    m_handler = std::unique_ptr<ILog>(handler);
}
