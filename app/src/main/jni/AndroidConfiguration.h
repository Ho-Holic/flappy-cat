#ifndef FLAPPY_CAT_ANDROIDCONFIGURATION_H
#define FLAPPY_CAT_ANDROIDCONFIGURATION_H

// ndk
#include <android/configuration.h>

// self
#include "macro.h"

// std
#include <memory>
#include <string>

class AndroidConfiguration {
private:
  using ConfigurationDeleter = void (*)(AConfiguration*);
  enum { AproximateToStringLength = 150 };

private:
  DISABLE_COPY(AndroidConfiguration)

public:
  AndroidConfiguration();

public:
  std::string toString() const;
  void reloadFrom(AAssetManager* manager);

private:
  void reloadCacheForToString();

private:
  std::unique_ptr<AConfiguration, ConfigurationDeleter> mConfiguration;
  std::string mCacheForToString;
};


#endif //FLAPPY_CAT_ANDROIDCONFIGURATION_H
