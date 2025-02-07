#include "mlpch.h"

#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Moonless
{
    ML_DLL_API std::shared_ptr<spdlog::logger> Log::m_core_logger;
    ML_DLL_API std::shared_ptr<spdlog::logger> Log::m_client_logger;

    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        m_core_logger = spdlog::stdout_color_mt("Moonless");
        m_core_logger->set_level(spdlog::level::trace);
        m_client_logger = spdlog::stdout_color_mt("SandBox");
        m_client_logger->set_level(spdlog::level::trace);
    }
}
