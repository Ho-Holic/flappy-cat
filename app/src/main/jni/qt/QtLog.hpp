#pragma once

#include <QDebug>
#include <core/Log.hpp>
#include <string>

class QtLog : public ILog {
public:
    void writeMessage(std::string tag, std::string message) override
    {
        qDebug() << tag.c_str() << "|" << message.c_str();
    }

    void assert_condition(bool condition, std::string conditionAsString, std::string tag, std::string message) override
    {
        if (!condition) {
            qDebug() << tag.c_str() << "|" << conditionAsString.c_str() << ", " << message.c_str();
            assert(condition);
        }
    }
};
