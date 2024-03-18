#version 330 core //Version of opengl
out vec4 FragColor; 

in vec3 color; //color from vert shader
in vec2 texCoord; //imported from vert shader

uniform sampler2D tex0;
uniform float time; // Corrected declaration of the time variable

void main()
{
   // Applying the distortion effect
    vec2 uv = texCoord; // Texture coordinates
    float distanceToCenterOfImage = distance(vec2(0.5), uv); // Distance from the center
    vec2 directionToCenterOfImage = vec2(0.5) - uv; // Direction towards the center
    uv -= distanceToCenterOfImage * directionToCenterOfImage * 0.3; // Applying distortion

    // Discarding fragments outside the texture boundaries
    if (uv.x < 0 || uv.x > 1 || uv.y < 0 || uv.y > 1)
        discard;

    float offsetSeed = floor(uv.y * 25); // Change 25 to change the thickness
    float offsetValue = sin(offsetSeed + time);

    // Applying time offset
    uv += vec2(offsetValue * 0.10, 0);

    // Sampling the texture using the distorted texture coordinates
    FragColor = texture(tex0, uv); // Final color output
}


//Above makes it look like an old TV while also making the texture move weirdly. 