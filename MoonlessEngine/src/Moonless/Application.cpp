#include "Application.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

Moonless::Application::Application() {
    
}

Moonless::Application::~Application() {
    
}

void Moonless::Application::run() {
    WindowResizeEvent e(1080,720);
    ML_CORE_ERROR(e);
    while(true);
}
