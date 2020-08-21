#version 330 core
in vec2 vertexUV;

uniform sampler2D textureSampler; 
uniform sampler2D shadow_map; 

uniform vec3 lightDirection;
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform vec3 eyePosition;

uniform float kAmbient = 0.2;
uniform float kDiffuse = 0.6;
uniform float kSpecular = 0.3;

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
   vec3 ambientColor = texture(textureSampler, vertexUV ).rgb;
   vec3 lightDirectionNorm = normalize(lightDirection);
   float diffuse = max(dot(normalize(vertexNormal), lightDirectionNorm), 0.0f);
   vec3 diffuseColor = diffuse * ambientColor;
   vec3 viewDirection = normalize(eyePosition - fragmentPosition);
   vec3 lightReflectDirection = reflect(lightDirectionNorm, normalize(vertexNormal));
   
   // The dot is the cos(theta) because it's normalized
   float specularComponent = pow(max(dot(viewDirection, lightReflectDirection), 0.0f), specularExponent); 
   vec3 specularColor = specularComponent * lightColor;
   float shadowScalar = 1.0f;
   if(dot(vec3(0.0f,1.0f,0.0f), lightDirectionNorm) >= 0.0)
       shadowScalar = 1 - dot(vec3(0.0f,1.0f,0.0f), lightDirectionNorm);
   vec3 finalLight = kAmbient * ambientColor + kDiffuse * shadowScalar * diffuseColor + kSpecular * shadowScalar * specularColor;
   
   FragColor = vec4(finalLight.rgb, 0.55f); //This is the actual line we want to have
   //FragColor = vec4(shadow_scalar(), shadow_scalar(), shadow_scalar(), 1.0); //Use this line to debug and see in white/black shadows
}
