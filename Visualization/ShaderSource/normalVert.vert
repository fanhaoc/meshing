#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal; 
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aOffset;


uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;
void main()
{
    gl_Position = projMat * viewMat * modelMat * vec4(aPos + aOffset, 1.0);
    FragPos = (modelMat * vec4(aPos, 1.0)).xyz;
    Normal = mat3(transpose(inverse(modelMat))) * aNormal; 
    TexCoord = aTexCoord;
}