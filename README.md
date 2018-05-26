# PHYSICS ENGINE
# physics_engine

## Build an Application
There is an application object, all applications should inherit the Application class. The following functions can be overriden to produce desired effects. The window creation uses GLFW3.

---
```cpp
virtual void render();
```
This function will include all the render details.

```cpp
virtual void tick();
```
This function should be defined to include the calculation details.

```cpp
virtual void key_callback(GLFWwindow* window,int key,int scancode,int action,int mods);
```
This function should be defined to set the keyboard keys.

```cpp
virtual void cursor_position_callback(GLFWwindow* window,double xpos,double ypos);
```
This function should be defined to set the actions related to the cursor positions.

```cpp
virtual void mouse_button_callback(GLFWwindow* window,int button,int action,int mods);
```
This function should be defined to set the mouse actions.

```cpp

```cpp
virtual void init();
```
This function should be defined to create all the physics objects, physics laws, rendering effects, etc...



