#pragma once

constexpr int BIT(int x) { return 1 << x; }

#ifdef ML_PLATFORM_WINDOWS
    #if ML_DYNAMIC_LINK
        #ifdef ML_BUILD_DLL
            #define ML_DLL_API __declspec(dllexport)
        #else
            #define ML_DLL_API __declspec(dllimport)
        #endif
    #else
        #define ML_DLL_API 
    #endif
#else
    #error Engine only support Windows Platform. 
#endif

#ifdef ML_ENABLE_ASSERTS
    #define ML_CORE_ASSERT(x,...)  {if(!x){ML_CORE_ERROR("Assertion failed: {0}",__VA_ARGS__);__debugbreak();}}
#else
    #define ML_CORE_ASSERT(x,...)  
#endif



