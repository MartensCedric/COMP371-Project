#version 330 core
uniform vec3 ambientColor;
uniform vec3 lightPosition;

in vec3 fragmentPosition;
in vec3 vertexNormal;
out vec4 FragColor;

void main()
{
   vec3 vertexColor = vec3(0.75f, 0.75f, 0.75f);
   vec3 normal = normalize(vertexNormal);
   vec3 lightDirection = normalize(fragmentPosition - lightPosition);
   float diffuse = max(dot(normal, lightDirection), 0.0f);
   vec3 diffuseColor = diffuse * vertexColor;
   FragColor = vec4(diffuseColor.rgb, 1.0f);
}
