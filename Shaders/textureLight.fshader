#version 330 core
in vec2 vertexUV;
uniform sampler2D textureSampler;
uniform vec3 lightPosition;
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform vec3 eyePosition;

uniform float kAmbient = 0.4;
uniform float kDiffuse = 0.4;
uniform float kSpecular = 0.5;

uniform float specularExponent = 32;

in vec3 fragmentPosition;
in vec3 vertexNormal;
out vec4 FragColor; 
void main()
{
   vec3 ambientColor = texture( textureSampler, vertexUV ).rgb;
   
   vec3 normal = vertexNormal;
   vec3 lightDirection = normalize(fragmentPosition - lightPosition);
   float diffuse = max(dot(normal, lightDirection), 0.0f);
   vec3 diffuseColor = diffuse * lightColor;
   vec3 viewDirection = normalize(eyePosition - fragmentPosition);
   vec3 lightReflectDirection = reflect(lightDirection, normal);
   
   // The dot is the cos(theta) because it's normalized
   float specularComponent = pow(max(dot(viewDirection, lightReflectDirection), 0.0f), specularExponent); 
   vec3 specularColor = specularComponent * lightColor;
   vec3 finalLight = kAmbient * ambientColor + kDiffuse * diffuseColor + kSpecular * specularColor;
   
   FragColor = vec4(finalLight.rgb, 1.0f);
}
