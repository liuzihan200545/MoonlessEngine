#pragma once

#include <spdlog/spdlog.h>
#include "Core.h"

namespace Moonless
{
    class ML_DLL_API Log {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger> m_core_logger;

        static std::shared_ptr<spdlog::logger> m_client_logger;

        static std::shared_ptr<spdlog::logger>& get_core_logger() {
            return m_core_logger;
        }
        
        static std::shared_ptr<spdlog::logger>& get_client_logger() {
            return m_client_logger;
        }
    };
}

#define ML_CORE_TRACE(...)     Moonless::Log::get_core_logger()->trace(__VA_ARGS__)
#define ML_CORE_INFO(...)      Moonless::Log::get_core_logger()->info(__VA_ARGS__)
#define ML_CORE_WARN(...)      Moonless::Log::get_core_logger()->warn(__VA_ARGS__)
#define ML_CORE_ERROR(...)     Moonless::Log::get_core_logger()->error(__VA_ARGS__)
#define ML_CORE_FATAL(...)     Moonless::Log::get_core_logger()->fatal(__VA_ARGS__)

#define ML_CLIENT_TRACE(...)     Moonless::Log::get_client_logger()->trace(__VA_ARGS__)
#define ML_CLIENT_INFO(...)      Moonless::Log::get_client_logger()->info(__VA_ARGS__)
#define ML_CLIENT_WARN(...)      Moonless::Log::get_client_logger()->warn(__VA_ARGS__)
#define ML_CLIENT_ERROR(...)     Moonless::Log::get_client_logger()->error(__VA_ARGS__)
#define ML_CLIENT_FATAL(...)     Moonless::Log::get_client_logger()->fatal(__VA_ARGS__)

