#ifndef FLAPPY_CAT_ANDROIDCONFIGURATION_H
#define FLAPPY_CAT_ANDROIDCONFIGURATION_H

// ndk
#include <android/configuration.h>

// self
#include "Guidelines.h"

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


#endif //FLAPPY_CAT_ANDROIDCONFIGURATION_H
