# opengl

## requirement
- glfw3 
- [glad](https://glad.dav1d.de/)
- [stbi image loader](https://github.com/nothings/stb/blob/master/stb_image.h)
- glm (opengl mathematics)
## Install glfw3
#### for x11
```bash
$ sudo pacman -S glfw3-x11 
```
#### for wayland
```bash
$ sudo pacman -S glfw3-wayland 
```

#### Using the image loader
````c++
#define STB_IMAGE_IMPLEMENTATION
#define "include/std_image.h"
````
 be sure to add this at the top and #define STB_IMAGE_IMPLEMENTATION before including the std_image.h header file 
## How to compile 

while compiling in the subdirectories make sure to inculde the include folder -I../include -I../include/KHR

```bash
g++ main.cpp src/glad.c -o main -I./include -I./include/KHR  -lglfw
```
