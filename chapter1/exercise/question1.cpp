/* Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data:
 */

#include <iostream>
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

// vertex shader source code 
const char *vertexShaderSource = "#version 330 core \n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main(){\n"
   "  gl_Position = vec4(aPos.x , aPos.y, aPos.z , 1);\n"
  "}\0";

// fragment shader source code
const  char *fragmentShaderSource = "#version 330 core \n"
  "out vec4 FragColor;"
  "void main(){\n"
  "FragColor = vec4(1.0f , 0.5f , 0.2f , 1.0f);\n"
  "}\0";

int main(){
  // initialize glfw
	if(!glfwInit()){
		std::cerr <<"Failed to initialize GLFW \n"; 
		return -1;
	}
  // opengl version 3.3 , use the core profile 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800 , 600 , "Welcome" , NULL , NULL);
  if (window == NULL){
    std::cout << "Failed to create GLFW Window " << std::endl;
	  glfwTerminate();
	  return -1;
  }
  glfwMakeContextCurrent(window);
       
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
	  std::cout << "Failed to initialize GLAD" << std::endl;
	  glfwTerminate();
	  return -1;
  }
  // building and compile our shader program 
 // compiling vertex shader
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader , 1 , &vertexShaderSource , NULL);
  glCompileShader(vertexShader);

  // checking if compilation for the vertex shader was succesful
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader , GL_COMPILE_STATUS , &success);
  if(!success){
    glGetShaderInfoLog(vertexShader , 512 , NULL , infoLog);
    std::cout << "ERROR::SHADER:::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // compiling fragment shader 
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader , 1, &fragmentShaderSource , NULL);
  glCompileShader(fragmentShader);

  // checking if compilation is correct
  glGetShaderiv(fragmentShader , GL_COMPILE_STATUS , &success);
  if(!success){
    glGetShaderInfoLog(fragmentShader , 512 , NULL , infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" <<  infoLog << std::endl;
  }
  // shader program object
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram , vertexShader);
  glAttachShader(shaderProgram , fragmentShader);
  glLinkProgram(shaderProgram);

  // checking if there is any error in the attaching and linking of shader progra
  glGetShaderiv(shaderProgram , GL_LINK_STATUS , &success);
  if(!success){
    glGetProgramInfoLog(shaderProgram , 512 , NULL , infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING::FAILED \n" << infoLog << std::endl;
  }
  // deleting the vertex and fragment shader as we no longer need them
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  // linking vertex attributes
 // vertex shader
  float vertices [] = {
	  // first triangle
	  -0.5f,0.5f,0.0f,
	  -0.5f,-0.5f,0.0f,
	  0.5f,-0.5f,0.0f,
	  // second triangle
	  0.2f , 0.2f,0.0f,
	  0.9f, 0.5f , 0.0f,
	  0.8f,0.8f , 0.0f
  };
  // creating and binding the vertices data in to vertex buffer object
  unsigned int VBO , VAO;
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);
  glBindBuffer(GL_ARRAY_BUFFER , VBO);
  glBindVertexArray(VAO);
  glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);
  glVertexAttribPointer(0,3,GL_FLOAT , GL_FALSE , 3 * sizeof(float) , (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0); 

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // glUseProgram(shaderProgram);
  // glviewport specifies window rectangle , (x , y , height , width)
  glViewport(0,0,800,600);
  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO); 
// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(window);
	  glfwPollEvents();
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}
