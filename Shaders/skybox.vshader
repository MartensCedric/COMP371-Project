#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

void main()
{
    TexCoords = aPos;
    gl_Position = projectionMatrix * viewMatrix * vec4(aPos, 1.0);
}  