# opengl

## requirement
- glfw3 
- [glad](https://glad.dav1d.de/)
## Install glfw3
#### for x11
```bash
$ sudo pacman -S glfw3-x11 
```
#### for wayland
```bash
$ sudo pacman -S glfw3-wayland 
```

## How to compile 

while compiling in the subdirectories make sure to inculde the include folder -I../include -I../include/KHR

```bash
g++ main.cpp src/glad.c -o main -I./include -I./include/KHR  -lglfw
```
