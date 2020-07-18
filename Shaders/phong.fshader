#version 330 core
uniform vec3 ambientColor;
out vec4 FragColor;
void main()
{
   vec3 vertexColor = vec3(0.75f, 0.75f, 0.75f);
   FragColor = vec4(vertexColor.r, vertexColor.g, vertexColor.b, 1.0f);
}
