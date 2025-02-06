#pragma once

#ifdef ML_PLATFORM_WINDOWS
    #ifdef ML_BUILD_DLL
        #define ML_DLL_API __declspec(dllexport)
    #else
        #define ML_DLL_API __declspec(dllimport)
    #endif
#else
    #error Engine only support Windows Platform. 
#endif