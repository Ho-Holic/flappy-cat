#pragma once

// ndk
#include <android/configuration.h>

// style
#include "style/Guidelines.hpp"

// std
#include <memory>
#include <string>

class AndroidConfiguration {
private:
    using ConfigurationDeleter = void (*)(AConfiguration*);
    enum { AproximateToStringLength = 150 };

private:
    AndroidConfiguration(const AndroidConfiguration&) = delete;
    AndroidConfiguration& operator=(const AndroidConfiguration&) = delete;

public:
    AndroidConfiguration(AAssetManager* manager);

public:
    std::string toString() const;
    void reload();
    void reset();

private:
    void reloadCacheForToString();

private:
    AAssetManager* mManager;
    std::unique_ptr<AConfiguration, ConfigurationDeleter> mConfiguration;
    std::string mCacheForToString;
};
