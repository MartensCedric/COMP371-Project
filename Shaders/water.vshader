#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

out vec4 vertexColor;
out vec3 fragmentPosition;

void main()
{
   vertexColor = aColor;
   mat4 modelViewProjection = projectionMatrix * viewMatrix * worldMatrix;
   fragmentPosition = vec3(worldMatrix * vec4 (aPos.xyz, 1.0));
   gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}