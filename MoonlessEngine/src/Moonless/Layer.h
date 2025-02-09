#pragma once

#include "Events/Event.h"

namespace Moonless
{
    class Layer
    {
    public:
        ML_DLL_API Layer(const std::string& name = "Layer");
        virtual ML_DLL_API ~Layer() = default;

        virtual ML_DLL_API void OnAttach() {}
        virtual ML_DLL_API void OnDetach() {}
        virtual ML_DLL_API void OnUpdate() {}
        virtual ML_DLL_API void OnImGuiRender() {}
        virtual ML_DLL_API void OnEvent(Event& event) {}

        ML_DLL_API const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };
}
