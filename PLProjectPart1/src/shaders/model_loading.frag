#version 330 core
out vec4 FragColor;

in vec2 texCoords;

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_normal1;
};

uniform Material material;

void main()
{    
    FragColor = texture(material.texture_diffuse1, texCoords);
}