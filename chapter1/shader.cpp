#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <ostream>
// #include <cmath>

// vertex shader source code
const char *vertexShaderSource = "#version 330 core \n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 5) in vec3 aColor;\n"
                                 // "flat"
                                 "out vec3  ourColor;"
                                 "void main(){\n"
                                 "  gl_Position = vec4( aPos, 1.0);\n"
                                 "  ourColor = aColor;\n"
                                 "}\0";

// fragment shader source code
const char *fragmentShaderSource = "#version 330 core \n"
                                   "out vec4 FragColor;\n"
                                   // "flat"
                                   "in vec3 ourColor;\n"
                                   "void main(){\n"
                                   "FragColor =vec4(ourColor , 1.0);\n"
                                   "}\0";

int main() {
  // initialize glfw
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW \n";
    return -1;
  }
  // opengl version 3.3 , use the core profile
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "Welcome", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW Window " << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    return -1;
  }

  // building and compile our shader program
  // compiling vertex shader
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  /*
   * to check number of max vertex attributes
  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes <<
  std::endl;
  */

  // checking if compilation for the vertex shader was succesful
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER:::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // compiling fragment shader
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // checking if compilation is correct
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // shader program object
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // checking if there is any error in the attaching and linking of shader
  // progra
  glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING::FAILED \n"
              << infoLog << std::endl;
  }
  // deleting the vertex and fragment shader as we no longer need them
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  // linking vertex attributes
  // vertex shader
  float vertices[]{0.5f,  -0.5f, 0.0f, 1.0f, 0.5f, 0.2f, // bottom right
                   -0.5f, -0.5f, 0.0f, 0.2f, 1.0f, 0.5f, // bottom left
                   0.0f,  0.5f,  0.0f, 0.5f, 0.2f, 1.0f};
  // creating and binding the vertices data in to vertex buffer object
  float innerVertices[] = {
      // positions        // colors (choose as desired)
      0.0f,   -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom (Midpoint of BR and BL)
      0.25f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f, // Right (Midpoint of BR and T)
      -0.25f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f  // Left (Midpoint of BL and T)
  };

  unsigned int VBO[2], VAO[2];
  glGenBuffers(1, &VBO[0]);
  glGenVertexArrays(1, &VAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBindVertexArray(VAO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(5);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(VAO[0]);

  glGenBuffers(1, &VBO[1]);
  glGenVertexArrays(1, &VAO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBindVertexArray(VAO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(innerVertices), innerVertices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(5);
  glBindBuffer(GL_ARRAY_BUFFER, 1);
  glBindVertexArray(VAO[1]);

  // glUseProgram(shaderProgram);
  // glviewport specifies window rectangle , (x , y , height , width)
  glViewport(0, 0, 800, 600);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    /*
     *
     * using the uniform variable to set color from outside the shader program
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.3f;
    float redValue = (sin(timeValue)  /2.0f) + 0.5f;
    float blueValue = (sin(timeValue) / 2.0f) + 0.7f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram , "ourColor");
    glUseProgram(shaderProgram);
    glUniform4f(vertexColorLocation ,redValue , greenValue ,blueValue , 1.0f);
    */

    // seeing as we only have a single VAO there's no need to bind it every
    // time, but we'll do so to keep things a bit more organized
    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_LINE_LOOP, 0, 3);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_LINE_LOOP, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &VAO[2]);
  glDeleteBuffers(1, &VBO[2]);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}
