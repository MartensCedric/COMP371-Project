#version 330 core
in vec4 vertexColor;
out vec4 FragColor;
uniform samplerCube skybox;
uniform float environment_map = 0.0f;
uniform vec3 lightDirection;
uniform vec3 eyePosition;

in vec3 vertexNormal;
in vec3 fragmentPosition;

void main()
{
   vec3 frag_to_eye = normalize(fragmentPosition - eyePosition);
   vec3 look_at_reflection = reflect(frag_to_eye, normalize(vertexNormal));
   vec3 skybox_env_color = texture(skybox, look_at_reflection).rgb;
   FragColor = vec4(skybox_env_color, 1.0f);
}
