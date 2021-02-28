// engine
#include "AndroidConfiguration.hpp"

// stl
#include <sstream>

AndroidConfiguration::AndroidConfiguration(AAssetManager* manager)
    : mManager(manager)
    , m_configuration(AConfiguration_new(), &AConfiguration_delete)
    , m_cacheForToString()
{
    m_cacheForToString.reserve(AproximateToStringLength);
}

void AndroidConfiguration::reload()
{

    AConfiguration_fromAssetManager(m_configuration.get(), mManager);
    reloadCacheForToString();
}

std::string AndroidConfiguration::toString() const
{

    return m_cacheForToString;
}

void AndroidConfiguration::reloadCacheForToString()
{

    AConfiguration* config = m_configuration.get();

    std::stringstream stream;

    char lang[2], country[2];
    AConfiguration_getLanguage(config, lang);
    AConfiguration_getCountry(config, country);

    stream << "Config: "
           << "mcc=" << AConfiguration_getMcc(config) << " "
           << "mnc=" << AConfiguration_getMnc(config) << " "
           << "lang=" << lang[0] << lang[1] << " "
           << "cnt=" << country[0] << country[1] << " "
           << "orien=" << AConfiguration_getOrientation(config) << " "
           << "touch=" << AConfiguration_getTouchscreen(config) << " "
           << "dens=" << AConfiguration_getDensity(config) << " "
           << "keys=" << AConfiguration_getKeyboard(config) << " "
           << "nav=" << AConfiguration_getNavigation(config) << " "
           << "keysHid=" << AConfiguration_getKeysHidden(config) << " "
           << "navHid=" << AConfiguration_getNavHidden(config) << " "
           << "sdk=" << AConfiguration_getSdkVersion(config) << " "
           << "size=" << AConfiguration_getScreenSize(config) << " "
           << "long=" << AConfiguration_getScreenLong(config) << " "
           << "modetype=" << AConfiguration_getUiModeType(config) << " "
           << "modenight=" << AConfiguration_getUiModeNight(config) << ""
           << "\n";
    m_cacheForToString = stream.str();
}

void AndroidConfiguration::reset()
{

    m_cacheForToString.clear();
    m_configuration.reset();
}
