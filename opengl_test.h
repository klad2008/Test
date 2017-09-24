#pragma once

#include "objects.h"
#include "platform.hpp"
#include "Program.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class OpenGL_Test{
    public:
    void LoadShaders();
    void LoadTriangle();
    void Render();
    void Number_Draw(Screen &);
    void Draw(Screen &);
};