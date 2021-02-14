#pragma once

#include "core/TypeIndex.hpp"
#include "style/Guidelines.hpp"
#include <map>
#include <memory>

class Services {
public:
    template <typename Derived, typename Base, typename... Args>
    void emplaceService(Args&&... args)
    {
        auto baseIndex = unorderedTypeIndex<Services, Base>();
        auto derivedIndex = unorderedTypeIndex<Services, Derived>();

        std::shared_ptr<void> newService(new Derived(std::forward(args)...));
        m_services.insert({ baseIndex, newService });
        m_services.insert({ derivedIndex, newService });

        m_totalSizeInBytes += sizeof(Derived);
    }

    template <typename T>
    T* viewService()
    {
        auto index = unorderedTypeIndex<Services, T>();        
        REQUIRE(TAG, m_services.find(index) != m_services.end(), "access to non-existing service");
        return static_cast<T*>(m_services[index].get());
    }

private:
    std::map<TypeIndex, std::shared_ptr<void>> m_services;
    int m_totalSizeInBytes = 0;
};

Services& services();

template <typename T>
T* service()
{
    return services().viewService<T>();
}
