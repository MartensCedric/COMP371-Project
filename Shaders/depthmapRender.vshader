#version 330 core

// Reference used learnopengl.com

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 worldMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);
uniform mat4 lightSpaceMatrix = mat4(1.0);

void main()
{
   mat4 modelViewProjection = projectionMatrix * viewMatrix * worldMatrix;
   gl_Position = lightSpaceMatrix * modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}