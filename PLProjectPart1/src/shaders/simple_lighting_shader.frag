#version 330 core
out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 normal;
in vec3 fragPos;

void main()
{
    // ambient component
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // point light (constant strength) component
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    // specular component
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), 32);
     
    // calculate resulting fragment color
    vec3 result = (ambient + diff + spec) * objectColor * lightColor;
    FragColor = vec4(result, 1.0);
}