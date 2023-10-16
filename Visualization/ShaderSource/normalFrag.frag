#version 330 core
// in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

// uniform sampler2D ourTexture;
uniform sampler2D ourFace;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;

out vec4 FragColor;
void main()
{
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 diffuse = max(dot(lightDir, Normal), 0) * lightColor;

    FragColor = vec4((ambientColor + diffuse) * objColor , 1.0f);
    // FragColor = mix(texture(ourTexture, TexCoord), texture(ourFace, TexCoord), 0.2) * vec4(ambientColor, 1.0);
} 