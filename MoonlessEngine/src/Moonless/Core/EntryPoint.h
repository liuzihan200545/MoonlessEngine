#pragma once
#include "Moonless/Core/Application.h"
#include "Moonless/Core/Log.h"

#include "mlpch.h"

#ifdef ML_PLATFORM_WINDOWS

extern Moonless::Application* Moonless::CreateApplication();

int main(int argc,char** argv) {
    Moonless::Log::Init();
    ML_CORE_INFO("Moonless Engine launched");
    
    ML_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Startup.json");
    Moonless::Application* sandbox = Moonless::CreateApplication();
    ML_PROFILE_END_SESSION();
   
    ML_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");
    sandbox->run();
    ML_PROFILE_END_SESSION();
    
    ML_PROFILE_BEGIN_SESSION("ShutDown", "HazelProfile-Shutdown.json");
    delete sandbox;
    ML_PROFILE_END_SESSION();
}

#endif