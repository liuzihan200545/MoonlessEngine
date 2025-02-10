#pragma once

#include <Moonless/Layer.h>


namespace Moonless
{
    class ImguiLayer : public Layer{
    public:
        ML_DLL_API ImguiLayer();
        ~ImguiLayer();

        void OnEvent(Event& event) override;
        void OnUpdate() override;
        void OnAttach() override;
        void OnDetach() override;

    private:
        float m_time = 0.0f;
    };

}
