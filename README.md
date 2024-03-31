# opengl

## requirement
- glfw3 
- [glad](https://glad.dav1d.de/)
## Install glfw3
```bash
$ sudo pacman -S glfw3-x11 

```
## How to compile 
```bash
g++ main.cpp src/glad.c -o main -I./include -I./include/KHR  -lglfw
```
