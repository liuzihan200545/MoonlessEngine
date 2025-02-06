#include <Moonless.h>

class Sandbox : public Moonless::Application {
public:
    Sandbox() {
        
    }

    ~Sandbox() override {
        
    }
};

Moonless::Application* Moonless::CreateApplication() {
    return new Sandbox();
}
