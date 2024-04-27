#define GLM_ENABLE_EXPERIMENTAL
#include "../include/glad/glad.h"
#include "../include/shader.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/matrix.hpp>
#include <iostream>
#include <ostream>

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

  Shader ourShader("../shaders/b_vert.glsl", "../shaders/b_frag.glsl");
  // co ordinates
  float vertices[] = {
      0.5f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
  };
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glEnableVertexAttribArray(0);
  glViewport(0, 0, 800, 600);
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    ourShader.use();
    glm::mat4 transform = glm::mat4(1.0f);
    float scaleAmount = static_cast<float>(cos(glfwGetTime()));
    std::cout << scaleAmount << std::endl;
    transform = glm::scale(transform, glm::vec3((scaleAmount / 2) + 1,
                                                (scaleAmount / 2) + 1,
                                                (scaleAmount / 2) + 1));
    transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, (float)glfwGetTime(),
                            glm::vec3(1.0f, 1.0f, 1.0f));
    std::cout << glm::to_string(transform) << std::endl;
    std::cout << glGetUniformLocation(ourShader.ID, "transform") << std::endl;
    glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "transform"), 1,
                       GL_FALSE, glm::value_ptr(transform));
    ourShader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  glfwTerminate();
  return 0;
}
