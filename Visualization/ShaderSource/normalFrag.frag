#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material{
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct LightDirectional{
    vec3 pos;
    vec3 color;
    vec3 dirToLight;
};

struct LightPoint{
    vec3 pos;
    vec3 color;
    vec3 dirToLight;
    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform LightDirectional lightD;
uniform LightPoint lightP;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 FragColor;

// function
// light direction
vec3 CalcLightDirectional(LightDirectional light, vec3 normal, vec3 dirToCamera){

    // diffuse
    float diffIntensity = max(dot(light.dirToLight, normal), 0);
    vec3 diffColor = diffIntensity * light.color;
//    vec3 diffColor = diffIntensity * light.color * texture(material.diffuse, TexCoord).xyz;
    
    // specular
    vec3 R = normalize(reflect(-light.dirToLight, normal));
    float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess);
    vec3 specColor = specIntensity * light.color;
//    vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).xyz;

    vec3 result = diffColor;
    return result;
}

vec3 CalcLightPoint(LightPoint light, vec3 normal, vec3 dirToCamera){
    // attenuation
    float dist = length(light.pos - FragPos);
    float attenuation = 1 / (light.constant + light.linear * dist + light.quadratic * pow(dist, 2));

    // diffuse
    float diffIntensity = max(dot(normalize(light.pos - FragPos), normal), 0) * attenuation;
    vec3 diffColor = diffIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

    // specular
    vec3 R = normalize(reflect((FragPos - light.pos), normal));
    float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess) * attenuation;
    vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).xyz;


    vec3 result =  diffColor + specColor;
    return result;
}

void main()
{
    vec3 finalResult = vec3(0.0, 0.0, 0.0);
    vec3 uNormal = normalize(Normal);
    vec3 dirToCamera = normalize(cameraPos - FragPos);
    finalResult += CalcLightDirectional(lightD, uNormal, dirToCamera);
    // finalResult += CalcLightPoint(lightP, uNormal, dirToCamera);
    // finalResult += texture(material.emission, TexCoord).rgb;
    FragColor = vec4(finalResult * vec3(0.4, 0.2, 0.3) , 1.0);
//    FragColor = vec4(objColor * ambientColor, 1.0);

} 