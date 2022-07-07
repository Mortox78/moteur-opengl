// ===================================== MODERN OPENGL ====================================== // 

By : NOVO Steeven
Released the : 29/01/2020

// ====================================== DESCRIPTION ============================================ // 

This project consisted in making the graphic part of a video game engine with modern Opengl

// =================================== HOW TO BUILD ========================================= //

Use the command "make" in the terminal

// =================================== HOW TO RUN ========================================= //

Use the command "bin/gl" in the terminal

// =================================== FEATURES ========================================= //

- Log
- Model (.obj files parsing)
- Textures
- Shader
- Transform
- Mesh
- ResourcesManager
- Graph
- Scene
- camera (ortho/perspective)

// ================================== INPUT ========================================== //

In this scene, you have 4 objects with different textures :
- Sword
- watch_tower
- Cube
- Plante

The input will change the scale/rotation of the sword.
The others objects will move too because they are sword's childrens.

You can move the camera with the mouse
Go up with "Space bar"
Go down with "left ctrl"
"+" and "-" change the scale of the sword
"x", "y" and "z" rotate the sword in the x, y and z axis.

// ==================================== NOT ADDED FEATURES & BUGS ===================================== // 

- "assertion" not added
- Light does not work
- Sometimes obj parsing does an infinite loop because the parser does not detect the end of the file
