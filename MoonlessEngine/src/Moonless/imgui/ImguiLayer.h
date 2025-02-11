#pragma once

#include <Moonless/Layer.h>


namespace Moonless
{
    class ImguiLayer : public Layer{
    public:
        ML_DLL_API ImguiLayer();
        ~ImguiLayer();
        
        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;

        void Begin();
        void End();

    private:
        float m_time = 0.0f;
    };

}
