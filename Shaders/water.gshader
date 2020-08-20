// Subdivides quad. Doesn't actually use vertices
#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices=256) out; 

uniform mat4 worldMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);
uniform float time_passed;

out vec3 fragmentPosition;
out vec3 vertexNormal;

float get_wave_height(float x, float y)
{
	return 0.2*sin(x + time_passed/10.0);
}

void main() {
   mat4 MVP = projectionMatrix * viewMatrix * worldMatrix;
   
   vec4 topLeft = vec4(-1.0, 0.0, -1.0, 1.0);
   vec4 bottomLeft = vec4(-1.0, 0.0, 1.0, 1.0);
   vec4 topRight = vec4(1.0, 0.0, -1.0, 1.0);
   vec4 bottomRight = vec4(1.0, 0.0, 1.0, 1.0);
   
   int xSections = 7;
   int ySections = 7;
   
   float scale = 50.0f;
   for(int j = 0; j < ySections - 1; j++)
   {
    float topZ = (2.0 * j)/ySections; 
	float bottomZ = (2.0 * (j + 1))/ySections;
	for(int i = 0; i < xSections; i++)
	{
		float x = (2.0 * i)/(xSections);
		vec3 pos1 = vec3(-1.0 + x, 0.0, -1.0 + topZ) * scale;
		pos1.y = get_wave_height(pos1.x, pos1.y);
		gl_Position = MVP * vec4(pos1, 1.0);
		fragmentPosition = vec3(worldMatrix * vec4(pos1, 1.0));
		vertexNormal = vec3(0, 1.0, 0.0);
		EmitVertex();		
        
		vec3 pos2 = vec3(-1.0 + x, 0.0, -1.0 + bottomZ) * scale;
		pos2.y = get_wave_height(pos2.x, pos2.y);
		gl_Position = MVP * vec4(pos2, 1.0);
		fragmentPosition = vec3(worldMatrix * vec4(pos2, 1.0));
		vertexNormal = vec3(0, 1.0, 0.0);
		EmitVertex();
	}
	EndPrimitive();
	
   }
}