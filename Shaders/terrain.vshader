#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aUV;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

out vec2 vertexUV;
out vec3 vertexNormal;
out vec3 fragmentPosition; //Actual position in the xyz world space

uniform mat4 transform_in_light_space;

out vec4 fragment_position_light_space;

void main()
{
   vertexNormal = mat3(transpose(inverse(worldMatrix))) * -aNormal;
   fragmentPosition = vec3(worldMatrix * vec4(aPos, 1.0));
   fragment_position_light_space = transform_in_light_space * vec4(fragmentPosition, 1.0);
   mat4 modelViewProjection = projectionMatrix * viewMatrix * worldMatrix;
   gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   vertexUV = aUV;
}