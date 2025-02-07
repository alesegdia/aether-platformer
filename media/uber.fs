#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

// texture samplers
uniform sampler2D texture1;

uniform vec3 diffuseLightColor;
uniform vec3 specularLightColor;
uniform vec3 ambientLightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float ambientStrength;
uniform float specularStrength;

uniform int shininess;

void main()
{
    // FragColor = (texture(texture1, TexCoord)) * vec4(color, 1) * vec4(lightColor, 1);
    // ambient
    vec3 ambient = ambientStrength * ambientLightColor;
  	//float attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));
    float attenuation = 1;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseLightColor * attenuation;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(0.0, dot(viewDir, reflectDir)), shininess);
    vec3 specular = specularStrength * spec * specularLightColor * attenuation;  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);

}
