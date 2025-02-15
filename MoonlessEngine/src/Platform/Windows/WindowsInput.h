#pragma once
#include "mlpch.h"
#include "Moonless/Core/Input.h"

namespace Moonless
{
class ML_DLL_API WindowsInput : public Input {
    
protected:
    bool IsKeyPressedImpl(int keycode) override;

    bool IsMouseButtonPressedImpl(int keycode) override;

    std::pair<float, float> GetMousePositionImpl() override;
    
    float GetMousePosXImpl() override;
    
    float GetMousePosYImpl() override;
};

}
