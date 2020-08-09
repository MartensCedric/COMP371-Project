// Algorithm found : https://subscription.packtpub.com/book/game_development/9781849695046/1/ch01lvl1sec13/dynamically-subdividing-a-plane-using-the-geometry-shader
#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices=256) out; 
int sub_divisions = 5;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);
uniform float dt;

out vec4 vertexColor;
out vec3 vertexNormal;
out vec2 vertexUV;

void main() {
  mat4 MVP = projectionMatrix * viewMatrix * worldMatrix;
  
  //vertexNormal = mat3(transpose(inverse(worldMatrix))) * -aNormal;
   vec4 topLeft = vec4(-1.0, 0.0, -1.0, 1.0);
   vec4 bottomLeft = vec4(-1.0, 0.0, 1.0, 1.0);
   vec4 topRight = vec4(1.0, 0.0, -1.0, 1.0);
   vec4 bottomRight = vec4(1.0, 0.0, 1.0, 1.0);
   
   int xSections = 4;
   int ySections = 4;
   
   
   for(int j = 0; j < ySections - 1; j++)
   {
    float topY = (2.0 * j)/ySections; 
	float bottomY = (2.0 * (j + 1))/ySections;
	for(int i = 0; i < xSections; i++)
	{
		float x = (2.0 * i)/(xSections);
		gl_Position = MVP * vec4(-1.0 + x, 0.0, -1.0 + topY, 1.0);
		vertexNormal = vec3(0, 1.0, 0.0);
		EmitVertex();		
        
		gl_Position = MVP * vec4(-1.0 + x, 0.0, -1.0 + bottomY, 1.0);
		vertexNormal = vec3(0, 1.0, 0.0);
		EmitVertex();
	}
	EndPrimitive();
	
   }
   
   
   gl_Position = MVP * topRight;
   vertexNormal = vec3(0, 1.0, 0.0);
   EmitVertex();

   gl_Position = MVP * bottomRight;
   vertexNormal = vec3(0, 1.0, 0.0);
   EmitVertex();
   
   EndPrimitive();
}