#version 330 core

out vec4 FragColor;
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform samplerCube skybox;
uniform float environment_map = 0.75f;
uniform vec3 lightDirection;
uniform vec3 eyePosition;

uniform float kAmbient = 0.4;
uniform float kDiffuse = 0.4;
uniform float kSpecular = 0.5;

in vec3 vertexNormal;
in vec3 fragmentPosition;
uniform float specularExponent = 32;

void main()
{
   vec4 water_color  = vec4(124.0/255.0, 183.0/255.0, 247.0/255.0, 1.0);
   vec3 frag_to_eye = normalize(fragmentPosition - eyePosition);
   vec3 look_at_reflection = reflect(frag_to_eye, normalize(vertexNormal));
   vec3 skybox_env_color = texture(skybox, look_at_reflection).rgb;
  
   vec3 lightDirectionNorm = normalize(lightDirection);
   float diffuse = max(dot(vertexNormal, lightDirectionNorm), 0.0f);
   vec3 diffuseColor = diffuse * lightColor;
   vec3 viewDirection = normalize(eyePosition - fragmentPosition);
   vec3 lightReflectDirection = reflect(lightDirectionNorm, vertexNormal);
   
   // The dot is the cos(theta) because it's normalized
   float specularComponent = pow(max(dot(viewDirection, lightReflectDirection), 0.0f), specularExponent); 
   vec3 specularColor = specularComponent * lightColor;
   vec3 finalWaterColor = kAmbient * vec3(water_color) + kDiffuse * diffuseColor + kSpecular * specularColor;
   
   FragColor = vec4((1 - environment_map) * finalWaterColor.rgb + environment_map  * skybox_env_color, 1.0);
}
