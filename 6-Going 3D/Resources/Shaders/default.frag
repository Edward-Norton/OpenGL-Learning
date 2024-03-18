#version 330 core //Version of opengl
out vec4 FragColor; 

in vec3 color; //color from vert shader

in vec2 texCoord; //imported from vert shader

uniform sampler2D tex0;

void main()
{
   FragColor = texture(tex0, texCoord);
}