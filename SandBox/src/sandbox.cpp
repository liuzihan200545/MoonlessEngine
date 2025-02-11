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
    }

    ~Sandbox() override {
        
    }
};

Moonless::Application* Moonless::CreateApplication() {
    return new Sandbox();
}
