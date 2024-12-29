#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer.h"


int main()
{
    GLRenderer renderer{ 640, 360 };
    if (!renderer.start()) return -1;
    return 0;
}
