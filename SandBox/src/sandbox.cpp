#include "SandBox2D.h"

using namespace Moonless;

class Sandbox : public Application {
public:
    Sandbox() {
        /*ExampleLayer* layer = new ExampleLayer();
        PushLayer(layer);*/

    	SandBox2D* layer = new SandBox2D();
    	PushLayer(layer);
    }

    ~Sandbox() override {
        
    }
};

Application* Moonless::CreateApplication() {
    return new Sandbox();
}
