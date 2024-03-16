#version 330 core
layout (location = 0) in vec3 aPos; //Vert pointer for coordinates

layout (location = 1) in vec3 aColor; //Vert pointer for color

layout (location = 2) in vec2 aTex;

//Export to the fragment shader
out vec3 color; //we want to output color to fragement shader

out vec2 texCoord;

uniform float scale; //After use program we can use a uniform to change the output

void main()
{
   gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y  + aPos.y * scale, aPos.z  + aPos.z * scale, 1.0); 
   color = aColor; //color to output to frag shader
   texCoord = aTex; //Texture to frag shader
}