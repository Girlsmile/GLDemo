//
//  Triangle.cpp
//  Bullet2FileLoader
//
//  Created by mastergu on 2020/4/4.
//

#include "Triangle.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "CONST.hpp"
#include "cmath"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
GLFWwindow* triangleWindowInit();

//const char *vertexShaderSource = "#version 330 core\n"
//    "layout (location = 0) in vec3 aPos;\n"
//    "out vec4 vertexColor;\n"
//    "void main()\n"
//    "{\n"
//    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//    "}\0";

//const char *vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"out vec4 vertexColor;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos, 1.0);\n"
//    "vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
//"}\0";

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"uniform float offset;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4((aPos.x - offset),aPos.y,aPos.z, 1.0);\n"
//    "ourColor = aColor;\n"
    "ourColor = aPos;\n"
"}\0";

//const char *fragmentShaderSource = "#version 330 core\n"
//    "out vec4 FragColor;\n"
//    "int vec4 vertexColor;\n"
//    "void main()\n"
//    "{\n"
//    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//    "}\n\0";

//const char *fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec4 vertexColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vertexColor;\n"
//"}\n\0";
//
//const char *fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"uniform vec4 ourColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = ourColor;\n"
//"}\n\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0);\n"
"}\n\0";

void drawTriangle() {
    
    GLFWwindow* window = triangleWindowInit();
    
    //compile shader program
    //顶点shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error vertexShader"<< infoLog << std::endl;
    }
    
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    //链接shader
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    glad_glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    
//    float vertices[] = {
//        -0.5f, -0.5f, 0.0f,
//        0.5f,  -0.5f, 0.0f,
//        0.0f, 0.5f, 0.0f
//    };
    //坐标 + 颜色
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
    };

//
//    float vertices[] = {
//        0.5f, 0.5f, 0.0f,
//        0.5f, -0.5f, 0.0f,
//        -0.5f,-0.5f, 0.0f,
//        -0.5f, 0.5f, 0.0f,
//    };
    
    unsigned int indices[] = {
        0,1,3,
        1,2,3
    };
    
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
   
    unsigned int VBO, VAO;
        
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    //先绑定定点缓冲数组， 然后把定点缓冲Buffer设置到数组里面去
    //简单来说就是把一个坐标的标量转成一维数组
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
//    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(0); //配置location0的属性
    
    //颜色属性
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1); //配置location1的属性
    
    //unbind
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        int offsetLocation = glGetUniformLocation(shaderProgram, "offset");
        
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        
        //四种设置uniform类型的函数 glUniform4f, glUniformi, glUniformui, glUniform3f, glUniformfv
        //location + 值 这里是四个
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        glUniform1f(offsetLocation, 0.2f);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//        glBindVertexArray(VAO);
        //0是顶点数组的开始索引， 最后一个是绘制的顶点数
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    
    glad_glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate();
}


GLFWwindow* triangleWindowInit() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return NULL;
    }
    
    return window;
}

