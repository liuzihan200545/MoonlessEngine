#pragma once

#include "Core.h"

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
