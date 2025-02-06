#pragma once
#include "Application.h"

#ifdef ML_PLATFORM_WINDOWS

extern Moonless::Application* Moonless::CreateApplication();

int main(int argc,char** argv) {
    Moonless::Application* sandbox = Moonless::CreateApplication();

    sandbox->run();

    delete sandbox;
}

#endif