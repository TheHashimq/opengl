/*Create two shader programs where the second program uses a different fragment shader that outputs the color yellow , draw npth triangles again where on outputs the color yellow ;
 *
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

const  char *fragmentShaderSource2 = "#version 330 core \n"
  "out vec4 FragColor;"
  "void main(){\n"
  "FragColor = vec4(1.0f , 1.0f , 0.0f , 1.0f);\n"
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

  glGetShaderiv(fragmentShader , GL_COMPILE_STATUS , &success);
  if(!success){
    glGetShaderInfoLog(fragmentShader , 512 , NULL , infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" <<  infoLog << std::endl;
  }
  unsigned int fragmentShader2;
  fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader2 , 1, &fragmentShaderSource2 , NULL);
  glCompileShader(fragmentShader2);
  // checking if compilation is correct
  glGetShaderiv(fragmentShader2 , GL_COMPILE_STATUS , &success);
  if(!success){
    glGetShaderInfoLog(fragmentShader2 , 512 , NULL , infoLog);
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
  // linking vertex attributes

  unsigned int shaderProgram2;
  shaderProgram2 = glCreateProgram();
  glAttachShader(shaderProgram2 , vertexShader);
  glAttachShader(shaderProgram2 , fragmentShader2);
  glLinkProgram(shaderProgram2);
  glGetShaderiv(shaderProgram2 , GL_LINK_STATUS , &success);
  if(!success){
    glGetProgramInfoLog(shaderProgram2 , 512 , NULL , infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING::FAILED \n" << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  glDeleteShader(fragmentShader2);
 // vertex shader
  float vertices []= {
    -0.9f , 0.2f , 0.0f,
    0.9f , -0.5f , 0.0f,
    -0.3f , -0.5f ,0.0f
  };

  float vertices2 [] = {
    -0.9f , 0.5f , 0.0f,
    0.9f , -0.2f , 0.0f,
    0.3f , 0.5f ,0.0f
  };
  // creating and binding the vertices data in to vertex buffer object
  unsigned int VBOs[2] , VAOs[2];
  glGenBuffers(1, &VBOs[0]);
  glGenVertexArrays(1, &VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER , VBOs[0]);
  glBindVertexArray(VAOs[0]);
  glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);
  glVertexAttribPointer(0,3,GL_FLOAT , GL_FALSE , 3 * sizeof(float) , (void*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0); 

  glGenBuffers(1, &VBOs[1]);
  glGenVertexArrays(1, &VAOs[1]);
  glBindBuffer(GL_ARRAY_BUFFER , VBOs[1]);
  glBindVertexArray(VAOs[1]);
  glBufferData(GL_ARRAY_BUFFER , sizeof(vertices2) , vertices2 , GL_STATIC_DRAW);
  glVertexAttribPointer(0,3,GL_FLOAT , GL_FALSE , 3 * sizeof(float) , (void*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0); 
  // glUseProgram(shaderProgram);
  // glviewport specifies window rectangle , (x , y , height , width)
  glViewport(0,0,800,600);
  while(!glfwWindowShouldClose(window)) {
    // glClearColor(0.7f, 0.9f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram2);
    glBindVertexArray(VAOs[0]); 
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAOs[1]); 
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(2, &VAOs[2]);
  glDeleteBuffers(2, &VBOs[2]);
  glDeleteProgram(shaderProgram);
  glDeleteProgram(shaderProgram2);

  glfwTerminate();
  return 0;
}
