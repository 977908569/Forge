//
// Created by Дмитрий Метелица on 2/4/20.
//

#include "DefaultApplication.h"

namespace Forge
{
    PlatformApiProvider* DefaultApplication::createPlatformApiProvider()
    {
        return new PlatformApiProvider();
    }
}