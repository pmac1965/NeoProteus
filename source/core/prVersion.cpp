/**
 * prVersion.cpp
 *
 *  Copyright 2014 Paul Michael McNab
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


//#include "../prConfig.h"


#include <stdio.h>
#include "prVersion.h"


namespace
{
    int versionMajor    = 3;
    int versionMinor    = 0;
    int versionRevision = 0;
}


/// ---------------------------------------------------------------------------
/// Acquire engine version number.
/// ---------------------------------------------------------------------------
void prGetVersion(int &major, int &minor, int &revision)
{
    major    = versionMajor;
    minor    = versionMinor;
    revision = versionRevision;
}


/// ---------------------------------------------------------------------------
/// Acquire engine version number as a string.
/// ---------------------------------------------------------------------------
const char *prGetVersionAsString()
{
    static char buffer[256];

    sprintf_s(buffer, sizeof(buffer), "%i.%i.%i", versionMajor, versionMinor, versionRevision);
    //sprintf(buffer, "%i.%i.%i", versionMajor, versionMinor, versionRevision);

    return buffer;
}
