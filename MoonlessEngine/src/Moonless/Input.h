#pragma once

#include "Core.h"
#include <memory>

namespace Moonless
{

    class ML_DLL_API Input {
    public:
        static bool IsKeyPressed(int keycode) {
            return m_handle->IsKeyPressedImpl(keycode);
        }

        static bool IsMouseButtonPressed(int keycode) {
            return m_handle->IsMouseButtonPressedImpl(keycode);
        }

        static std::pair<float,float> GetMousePosition() {
            return m_handle->GetMousePositionImpl();
        }

        static float GetMousePosX() {
            return m_handle->GetMousePosXImpl();
        }

        static float GetMousePosY() {
            return m_handle->GetMousePosYImpl();
        }
    

    protected:
        virtual bool IsKeyPressedImpl(int keycode) = 0;
        
        virtual bool IsMouseButtonPressedImpl(int keycode) = 0;

        virtual std::pair<float,float> GetMousePositionImpl() = 0;

        virtual float GetMousePosXImpl() = 0;

        virtual float GetMousePosYImpl() = 0;

    private:
        static std::unique_ptr<Input> m_handle;
    };

}
