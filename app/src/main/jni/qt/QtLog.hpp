#pragma once

#include <QDebug>
#include <string>
#include <core/Log.hpp>

class QtLog : public ILog {
public:
    void writeMessage(std::string tag, std::string message) override
    {
        qDebug() << tag.c_str() << "|" << message.c_str();
    }

    void assert_condition(bool condition, std::string conditionAsString, std::string tag, std::string message) override
    {
        qDebug() << tag.c_str() << "|" << conditionAsString.c_str() << ", " << message.c_str();
        assert(condition);
    }
};
