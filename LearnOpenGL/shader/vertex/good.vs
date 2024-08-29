#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;

// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;

out vec4 vertexColor;
out vec2 textureCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    vertexColor = vec4(aColor, 1.0f);
    textureCoord = aUV;
}