#include "EditorLayer.h"
#include "Moonless/Core/EntryPoint.h"

namespace Moonless {

class MoonlessEditor : public Application
{
public:
    MoonlessEditor()
    {
        PushLayer(new EditorLayer());
    }
    ~MoonlessEditor()
    {
        
    }
};

Application* CreateApplication()
{
    return new MoonlessEditor();
}

}