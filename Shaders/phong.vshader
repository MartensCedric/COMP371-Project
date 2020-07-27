#version 330 core

// Reference used learnopengl.com

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aNormal;

uniform mat4 worldMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

out vec3 fragmentPosition;
out vec4 vertexColor;
out vec3 vertexNormal;
uniform mat4 transform_in_light_space;

out vec4 fragment_position_light_space;

void main()
{
   vertexColor = aColor;

	// Transforms normal in world coordinates. Translations can be ignored
   vertexNormal = mat3(transpose(inverse(worldMatrix))) * -aNormal;
   fragmentPosition = vec3(worldMatrix * vec4(aPos, 1.0));
   fragment_position_light_space = transform_in_light_space * vec4(fragmentPosition, 1.0);
   mat4 modelViewProjection = projectionMatrix * viewMatrix * worldMatrix;
   gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}