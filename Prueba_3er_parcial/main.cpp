#include <iostream>
#include "DemostracionComplejidad.h"

int main()
{
    try
    {
        DemostracionComplejidad demo;
        demo.demostrar();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}