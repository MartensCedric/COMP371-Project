#version 330 core

out vec4 FragColor;
uniform samplerCube skybox;
uniform float environment_map = 0.5f;
uniform vec3 lightDirection;
uniform vec3 eyePosition;

in vec3 vertexNormal;
in vec3 fragmentPosition;

void main()
{
   vec4 water_color  = vec4(124.0/255.0, 183.0/255.0, 247.0/255.0, 1.0);
   vec3 frag_to_eye = normalize(fragmentPosition - eyePosition);
   vec3 look_at_reflection = reflect(frag_to_eye, normalize(vertexNormal));
   vec3 skybox_env_color = texture(skybox, look_at_reflection).rgb;
   FragColor = (1 - environment_map) * water_color  + environment_map  * vec4(skybox_env_color, 1.0f);
}
