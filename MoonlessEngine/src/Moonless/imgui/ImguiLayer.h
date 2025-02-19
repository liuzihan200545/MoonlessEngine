#pragma once

#include "Moonless/Core/Layer.h"


namespace Moonless
{
    class ImguiLayer : public Layer{
    public:
        ML_DLL_API ImguiLayer();
        ~ImguiLayer();
        
        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;
        void OnEvent(Event& event) override;

        void Begin();
        void End();

        void BlockEvents(bool block) { m_BlockEvents = block; }

    private:
        float m_time = 0.0f;
        bool m_BlockEvents = true;
    };

}
