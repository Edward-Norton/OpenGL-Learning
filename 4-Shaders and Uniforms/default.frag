#version 330 core //Version of opengl
out vec4 FragColor; 

in vec3 color; //color from vert shader

void main()
{
   FragColor = vec4(color, 1.0f);
}