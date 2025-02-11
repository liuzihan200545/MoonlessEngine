#include <Moonless.h>
#include <GLFW/glfw3.h>

#include "Moonless/Events/KeyEvent.h"

class ExampleLayer : public Moonless::Layer {
public:
    ExampleLayer() : Layer("Example"){}

    void OnUpdate() override {
        //ML_CLIENT_INFO("Example Layer OnUpdate");
    }

    void OnEvent(Moonless::Event& event) override {
        Moonless::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Moonless::KeyPressedEvent>([](Moonless::KeyPressedEvent& event)
        {
            if(event.GetKeyCode() == ML_KEY_TAB)
            {
                ML_CORE_ERROR("TAB KEY is Pressed!");
                
            }
            ML_CORE_ERROR("{} KEY IS RELEASED",static_cast<char>(event.GetKeyCode()));
            return false;
        });
    }
};

class Sandbox : public Moonless::Application {
public:
    Sandbox() {
        ExampleLayer* layer = new ExampleLayer();
        PushLayer(layer);
        Moonless::ImguiLayer* imgui_layer = new Moonless::ImguiLayer();
        PushOverlay(imgui_layer);
    }

    ~Sandbox() override {
        
    }
};

Moonless::Application* Moonless::CreateApplication() {
    return new Sandbox();
}
