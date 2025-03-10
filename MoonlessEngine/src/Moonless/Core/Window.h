#pragma once

#include "mlpch.h"

#include <Moonless/Core/Core.h>
#include "Moonless/Events/Event.h"

namespace Moonless
{
    struct WindowProps {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& title = std::string("Moonless Engine"),unsigned int width = 1080,unsigned int height = 720)
            : Title(title) , Width(width) , Height(height) {}
    };

    class ML_DLL_API Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void OnUpdate() = 0;
 
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback_fn) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() = 0;

        static Window* Create(const WindowProps& props = WindowProps());
        
    };

}


