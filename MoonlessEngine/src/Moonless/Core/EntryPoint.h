#pragma once
#include "Moonless/Core/Application.h"
#include <spdlog/spdlog.h>

#include "Moonless/Core/Log.h"

#ifdef ML_PLATFORM_WINDOWS

extern Moonless::Application* Moonless::CreateApplication();

int main(int argc,char** argv) {
    Moonless::Log::Init();

    ML_CORE_INFO("Moonless Engine launched");
    
    Moonless::Application* sandbox = Moonless::CreateApplication();

    sandbox->run();

    delete sandbox;
}

#endif