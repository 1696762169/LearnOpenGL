#version 460 core

in vec4 vertexColor;
in vec2 textureCoord;

uniform vec4 ourColor;
uniform sampler2D texture0;

out vec4 FragColor;

void main()
{
    FragColor = texture(texture0, textureCoord);
} 