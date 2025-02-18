/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/std/time.h>
#include <AzCore/PlatformIncl.h>

namespace AZStd
{
    AZStd::sys_time_t GetTimeTicksPerSecond()
    {
        static AZStd::sys_time_t freq = 0;
        if (freq == 0)
        {
            QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
        }
        return freq;
    }

    AZStd::sys_time_t GetTimeNowTicks()
    {
        AZStd::sys_time_t timeNow;
        QueryPerformanceCounter((LARGE_INTEGER*)&timeNow);
        return timeNow;
    }

    AZStd::sys_time_t GetTimeNowMicroSecond()
    {
        AZStd::sys_time_t timeNowMicroSecond;
        // NOTE: The default line below was not working on systems with smaller TicksPerSecond() values (like in Windows7, for example)
        // So we are now spreading the division between the numerator and denominator to maintain better precision
        timeNowMicroSecond = (GetTimeNowTicks() * 1000) / (GetTimeTicksPerSecond() / 1000);
        return timeNowMicroSecond;
    }

    AZStd::sys_time_t GetTimeNowSecond()
    {
        AZStd::sys_time_t timeNowSecond;
        // Using get tick count, since it's more stable for longer time measurements.
        timeNowSecond = GetTickCount() / 1000;
        return timeNowSecond;
    }
}
