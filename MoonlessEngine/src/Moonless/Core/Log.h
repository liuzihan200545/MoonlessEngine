#pragma once

#include "mlpch.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "Moonless/Core/Core.h"
#include "Moonless/Events/Event.h"

template <class T>
struct fmt::formatter<T, std::enable_if_t<std::is_base_of_v<Moonless::Event, T>, char>> {
    constexpr auto parse(fmt::format_parse_context& ctx) {
        return ctx.begin();
    }
    
    template <typename FormatContext>
    auto format(const Moonless::Event& obj, FormatContext& ctx) const {
        return fmt::format_to(ctx.out(), "{}", obj.ToString());
    }
};

namespace Moonless
{
    // In Log.h
    class Log {
    public:
        static ML_DLL_API void Init();  // Export Init function
        
        static ML_DLL_API std::shared_ptr<spdlog::logger> m_core_logger;
        static ML_DLL_API std::shared_ptr<spdlog::logger> m_client_logger;

        static ML_DLL_API std::shared_ptr<spdlog::logger>& get_core_logger() {  
            return m_core_logger;
        }

        static ML_DLL_API std::shared_ptr<spdlog::logger>& get_client_logger() {  
            return m_client_logger;
        }
    };
}

#ifdef ML_DEBUG
    #define ML_CORE_TRACE(...)     Moonless::Log::get_core_logger()->trace(__VA_ARGS__)
    #define ML_CORE_INFO(...)      Moonless::Log::get_core_logger()->info(__VA_ARGS__)
    #define ML_CORE_WARN(...)      Moonless::Log::get_core_logger()->warn(__VA_ARGS__)
    #define ML_CORE_ERROR(...)     Moonless::Log::get_core_logger()->error(__VA_ARGS__)
    #define ML_CORE_FATAL(...)     Moonless::Log::get_core_logger()->cirtical(__VA_ARGS__)

    #define ML_CLIENT_TRACE(...)     Moonless::Log::get_client_logger()->trace(__VA_ARGS__)
    #define ML_CLIENT_INFO(...)      Moonless::Log::get_client_logger()->info(__VA_ARGS__)
    #define ML_CLIENT_WARN(...)      Moonless::Log::get_client_logger()->warn(__VA_ARGS__)
    #define ML_CLIENT_ERROR(...)     Moonless::Log::get_client_logger()->error(__VA_ARGS__)
    #define ML_CLIENT_FATAL(...)     Moonless::Log::get_client_logger()->cirtical(__VA_ARGS__)
#else
    #define ML_CORE_TRACE(...)     
    #define ML_CORE_INFO(...)      
    #define ML_CORE_WARN(...)      
    #define ML_CORE_ERROR(...)     
    #define ML_CORE_FATAL(...)     

    #define ML_CLIENT_TRACE(...)     
    #define ML_CLIENT_INFO(...)      
    #define ML_CLIENT_WARN(...)      
    #define ML_CLIENT_ERROR(...)     
    #define ML_CLIENT_FATAL(...)     
#endif
    

