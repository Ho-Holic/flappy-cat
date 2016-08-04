// self
#include "AndroidConfiguration.h"

// stl
#include <sstream>

AndroidConfiguration::AndroidConfiguration()
: mConfiguration(AConfiguration_new(), &AConfiguration_delete)
, mCacheForToString() {
  mCacheForToString.reserve(AproximateToStringLength);
}

void AndroidConfiguration::reloadFrom(AAssetManager* manager) {

  AConfiguration_fromAssetManager(mConfiguration.get(), manager);
  reloadCacheForToString();
}

std::string AndroidConfiguration::toString() const {

  return mCacheForToString;
}

void AndroidConfiguration::reloadCacheForToString() {

  AConfiguration* config = mConfiguration.get();

  std::stringstream stream;

  char lang[2], country[2];
  AConfiguration_getLanguage(config, lang);
  AConfiguration_getCountry(config, country);

  stream << "Config: "
         << "mcc="       << AConfiguration_getMcc(config)         << " "
         << "mnc="       << AConfiguration_getMnc(config)         << " "
         << "lang="      << lang[0] << lang[1]                    << " "
         << "cnt="       << country[0] << country[1]              << " "
         << "orien="     << AConfiguration_getOrientation(config) << " "
         << "touch="     << AConfiguration_getTouchscreen(config) << " "
         << "dens="      << AConfiguration_getDensity(config)     << " "
         << "keys="      << AConfiguration_getKeyboard(config)    << " "
         << "nav="       << AConfiguration_getNavigation(config)  << " "
         << "keysHid="   << AConfiguration_getKeysHidden(config)  << " "
         << "navHid="    << AConfiguration_getNavHidden(config)   << " "
         << "sdk="       << AConfiguration_getSdkVersion(config)  << " "
         << "size="      << AConfiguration_getScreenSize(config)  << " "
         << "long="      << AConfiguration_getScreenLong(config)  << " "
         << "modetype="  << AConfiguration_getUiModeType(config)  << " "
         << "modenight=" << AConfiguration_getUiModeNight(config) << ""
         << "\n";
  mCacheForToString = stream.str();
}

void AndroidConfiguration::reset() {

  mCacheForToString.clear();
  mConfiguration.reset();
}
