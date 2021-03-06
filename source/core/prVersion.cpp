/**
 * prVersion.cpp
 *
 *  Copyright 2018 Paul Michael McNab
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


#include <stdio.h>
#include "core/prConfig.h"
#include "core/prVersion.h"


namespace Proteus {
namespace Core {

    int versionMajor    = PR_VERSION_MAJOR;
    int versionMinor    = PR_VERSION_MINOR;
    int versionRevision = PR_VERSION_VERSION;


    // ---------------------------------------------------------------------------
    // Acquire engine version number.
    // ---------------------------------------------------------------------------
    void prGetVersion(int &major, int &minor, int &revision)
    {
        major    = versionMajor;
        minor    = versionMinor;
        revision = versionRevision;
    }


    // ---------------------------------------------------------------------------
    // Acquire engine version number as a string.
    // ---------------------------------------------------------------------------
    const char *prGetVersionAsString()
    {
        static char buffer[64];

#if defined(PLATFORM_PC)
        sprintf_s(buffer, sizeof(buffer), "%i.%i.%i", versionMajor, versionMinor, versionRevision);
#else
        sprintf(buffer, "%i.%i.%i", versionMajor, versionMinor, versionRevision);
#endif

        return buffer;
    }

}}

