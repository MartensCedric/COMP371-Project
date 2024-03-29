#version 330 core
in vec2 vertexUV;

uniform sampler2D textureSampler; 
uniform sampler2D shadow_map; 

uniform vec3 lightDirection;
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform vec3 eyePosition;

uniform float kAmbient = 0.1;
uniform float kDiffuse = 0.5;
uniform float kSpecular = 0.5;

uniform float specularExponent = 32;

in vec3 fragmentPosition;
in vec3 vertexNormal;
out vec4 FragColor;

in vec4 fragment_position_light_space;

float shadow_scalar() {
    // this function returns 1.0 when the surface receives light, and 0.0 when it is in a shadow
    // perform perspective divide
    vec3 ndc = fragment_position_light_space.xyz / fragment_position_light_space.w;
    // transform to [0,1] range
    ndc = ndc * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragment_position_light_space as coords)
    float closest_depth = texture(shadow_map, ndc.xy).r;
    // get depth of current fragment from light's perspective
    float current_depth = ndc.z;
    // check whether current frag pos is in shadow
    float bias = 0.0;  // bias applied in depth map: see shadow_vertex.glsl
    return ((current_depth - bias) < closest_depth) ? 1.0 : 0.0;
}

void main()
{
   float height = fragmentPosition.y / 10.0;
   vec3 ambientColor = vec3(252.0f/255.0f, 252.0f/255.0f, 252.0f/255.0f);
   
   if(height < 0.6)
   {
		ambientColor = vec3(122.0f/255.0f, 113.0f/255.0f, 109.0f/255.0f);
   }
   
   if(height < 0.2)
   {
		ambientColor = vec3(162.0f/255.0f, 235.0f/255.0f, 193.0f/255.0f);
   }
  
   vec3 lightDirectionNorm = normalize(lightDirection);
   float diffuse = max(dot(vertexNormal, lightDirectionNorm), 0.0f);
   vec3 diffuseColor = diffuse * ambientColor;
   vec3 viewDirection = normalize(eyePosition - fragmentPosition);
   vec3 lightReflectDirection = reflect(lightDirectionNorm, normalize(vertexNormal));
   
   // The dot is the cos(theta) because it's normalized
   float specularComponent = pow(max(dot(viewDirection, lightReflectDirection), 0.0f), specularExponent); 
   vec3 specularColor = specularComponent * lightColor;
   float shadowScalar = shadow_scalar();
   //vec3 finalLight = kAmbient * ambientColor + kDiffuse * shadowScalar * diffuseColor + kSpecular * shadowScalar * specularColor;
   vec3 finalLight = kAmbient * ambientColor + kDiffuse * diffuseColor + kSpecular * specularColor;
   FragColor = vec4(finalLight.rgb, 1.0f); //This is the actual line we want to have
   //FragColor = vec4(shadow_scalar(), shadow_scalar(), shadow_scalar(), 1.0); //Use this line to debug and see in white/black shadows
}
