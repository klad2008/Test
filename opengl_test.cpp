#pragma once

#include "opengl_test.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

const glm::vec2 SCREEN_SIZE(800, 600);

GLFWwindow* gWindow = NULL;
tdogl::Program* gProgram = NULL;
GLuint gVAO = 0;
GLuint gVBO = 0;

GLfloat vertexData[80000000];

void OpenGL_Test :: Number_Draw(Screen &screen){
    freopen("test.out", "w", stdout);
    for (int i = 0; i <= screen.width; i++) {
        for (int j = 0; j <= screen.height; j++)
//            printf("(% 4d, % 4d, % 4d)  ", int(screen.color[i][j].a[0]), int(screen.color[i][j].a[1]), int(screen.color[i][j].a[2]));
            if (fabs(screen.color[i][j].a[0] + screen.color[i][j].a[1] + screen.color[i][j].a[2]) < 1e-5) printf("0");
            else printf("1");
        printf("\n");
    }
}

void LoadShaders() {
    std::vector<tdogl::Shader> shaders;
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("vertex-shader.txt"), GL_VERTEX_SHADER));
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("fragment-shader.txt"), GL_FRAGMENT_SHADER));
    gProgram = new tdogl::Program(shaders);
}

void vertex_push(GLfloat *A, int i, int j, Screen & screen){
    double x = double(i) / (screen.width + 1) * 2 - 1;
    double y = double(j) / (screen.height + 1) * 2 - 1;
    double z = 0;
    A[0] = x;
    A[1] = y;
    A[2] = z;
    A[3] = screen.color[i][j].a[0];
    A[4] = screen.color[i][j].a[1];
    A[5] = screen.color[i][j].a[2];
}

void LoadTriangle(Screen &screen) {
    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);

    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);

/*    GLfloat vertexData[] = {
            //  X     Y     Z     R     G     B
            -0.3f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.8f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.2f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            1.0f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    };*/
    printf("1\n");
    for (int i = 0; i < screen.width; i++) {
        printf("%d\n", i);
        for (int j = 0; j < screen.height; j++) {
            int head = (i * screen.height + j) * 3 * 2 * 6;
            vertex_push(vertexData + head + 0 * 6, i, j, screen);
            vertex_push(vertexData + head + 1 * 6, i + 1, j, screen);
            vertex_push(vertexData + head + 2 * 6, i, j + 1, screen);
            vertex_push(vertexData + head + 3 * 6, i + 1, j, screen);
            vertex_push(vertexData + head + 4 * 6, i, j + 1, screen);
            vertex_push(vertexData + head + 5 * 6, i + 1, j + 1, screen);
        }
    }

/*    freopen("test.out", "w", stdout);
    for (int i = 0; i < screen.width; i++)
        for (int j = 0; j < screen.height; j++)
            for (int k = 0; k < 6; k++){
                int head = (i * screen.height + j) * 3 * 2 * 6;
                for (int t = 0; t < 6; t++)
                    printf("%.3f ", vertexData[head * 6 + t]);
                printf("\n");
            }
*/
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(gProgram->attrib("vert"));
    glEnableVertexAttribArray(gProgram->attrib("color"));
    glVertexAttribPointer(gProgram->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glVertexAttribPointer(gProgram->attrib("color"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const GLvoid *)(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Render(Screen &screen) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    gProgram->use();



    glBindVertexArray(gVAO);

    glDrawArrays(GL_TRIANGLES, 0, screen.width * screen.height * 3 * 2);

    glBindVertexArray(0);

    gProgram->stopUsing();

    glfwSwapBuffers(gWindow);
}

void OnError(int errorCode, const char* msg) {
    throw std::runtime_error(msg);
}

// the program starts here
void AppMain(Screen &screen) {
    // initialise GLFW
    glfwSetErrorCallback(OnError);
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");

    // open a window with GLFW
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    gWindow = glfwCreateWindow((int)screen.width, (int)screen.height, "OpenGL Tutorial", NULL, NULL);
    if(!gWindow)
        throw std::runtime_error("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");

    // GLFW settings
    glfwMakeContextCurrent(gWindow);

    // initialise GLEW
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // print out some info about the graphics drivers
/*    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;*/

    // make sure OpenGL version 3.2 API is available
    if(!GLEW_VERSION_3_2)
        throw std::runtime_error("OpenGL 3.2 API is not available.");

    // load vertex and fragment shaders into opengl
    LoadShaders();

    // create buffer and fill it with the points of the triangle
    LoadTriangle(screen);

    // run while the window is open
    while(!glfwWindowShouldClose(gWindow)){
        // process pending events
        glfwPollEvents();

        // draw one frame
        Render(screen);
    }

    // clean up and exit
    glfwTerminate();
}

void OpenGL_Test :: Draw(Screen &screen){
    /*
        Number_Draw(screen);
        play a magic
    */
    Number_Draw(screen);
    AppMain(screen);
}
