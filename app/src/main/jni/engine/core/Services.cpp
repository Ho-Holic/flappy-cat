#include "Services.hpp"

Services& services()
{
    static Services instance;
    return instance;
}
