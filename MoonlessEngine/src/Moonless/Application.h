#pragma once

#include "Core.h"
#include "Log.h"

namespace Moonless
{
    class ML_DLL_API Application {
    public:
        Application();

        virtual ~Application();

        void run();
    };

    Application* CreateApplication();
}
