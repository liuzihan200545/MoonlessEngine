#include <Moonless.h>
#include <GLFW/glfw3.h>

class ExampleLayer : public Moonless::Layer {
public:
    ExampleLayer() : Layer("Example"){}

    void OnUpdate() override {
        //ML_CLIENT_INFO("Example Layer OnUpdate");
        if(Moonless::Input::IsKeyPressed(GLFW_KEY_TAB))
        {
            ML_CORE_ERROR("TAB KEY is Pressed!");
        }

        if(Moonless::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
        {
            ML_CORE_ERROR("Mouse Left Pressed");
        }
        
    }

    void OnEvent(Moonless::Event& event) override {
        //ML_CLIENT_TRACE(event);
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
