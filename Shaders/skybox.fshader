#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;
uniform vec3 lightDirection;
uniform float night_weight = 0.2;
void main()
{    
    float skylight = max(dot(vec3(0,1,0), normalize(-lightDirection)), 0.0);
	vec3 skyColor = texture(skybox, TexCoords).rgb;
    FragColor = vec4(skyColor * night_weight + skyColor * (1-night_weight) * skylight, 1.0);
}