#version 330 core
out vec4 fragColor;  

uniform vec3 lightObjectColor;


void main()
{
    fragColor = vec4(lightObjectColor, 1.0f);
}