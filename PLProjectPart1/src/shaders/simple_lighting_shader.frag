#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    int lightType; // 1 : directional || 2 : point || 3 : spot
    vec3 direction;
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
    float inverseCutOffAngle;
};

  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

void main()
{
    vec3 textureColor = vec3(texture(material.diffuse, texCoords));
    vec3 norm = normalize(normal);
    vec3 lightDir = vec3(0.0);
    float attenuation = 1;
    float spotDistanceFactor = 1;

    if (light.lightType == 1){
        lightDir = normalize(-light.direction);

    } else if (light.lightType == 2){
        float distanceP = length(light.position - fragPos);
        attenuation = 1 / (light.constant + light.linear * distanceP + 
    		    light.quadratic * (distanceP * distanceP));  
        lightDir = normalize(light.position - fragPos);

    } else if (light.lightType == 3) {
        lightDir = normalize(light.position - fragPos);
        float cosTheta = dot(lightDir, normalize(-light.direction));
        /*if (cosTheta <= light.cutOff){
            lightDir = vec3(0.0);
        } else {
            
            // optional for fancy transition between light and dark area
            //spotDistanceFactor = -light.inverseCutOffAngle * acos(cosTheta) + 1; // makes function going from 1 to 0 given theta going from 0 to light.cutoff
            //spotDistanceFactor = pow(spotDistanceFactor, 1.0/2.0);

            
        }*/
        // optional second option for transition

        float epsilon = light.cutOff - light.outerCutOff;
        spotDistanceFactor = clamp((cosTheta - light.outerCutOff) / epsilon, 0.0, 1.0); 
    }

    // ambient
    vec3 ambient = light.ambient * textureColor;

    // diffuse 
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * textureColor * light.diffuse * spotDistanceFactor;
    
    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * vec3(texture(material.specular, texCoords)) * light.specular * spotDistanceFactor;  
        
    vec3 result = (ambient + diffuse + specular) * attenuation;
    FragColor = vec4(result, 1.0);
}