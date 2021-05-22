#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 LightPos;

struct Material{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

struct PointLight{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

};

uniform Material material;
uniform PointLight pointLights[1];

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir, Material material);

void main()
{    
    vec3 viewDir = normalize(-FragPos);
    vec3 normal = normalize(Normal);
    vec3 result = calcPointLight(pointLights[0], normal, viewDir, material);

    FragColor = vec4(result, 1.0);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir, Material material) {
    //ambient
    vec3 ambient = light.ambient * texture(material.texture_diffuse1, TexCoords).rgb;

    //diffuse
    vec3 LightDir = normalize(LightPos - FragPos);
    float diff = max(dot(normal, LightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse1, TexCoords).rgb;

    //specular
    vec3 reflDir = reflect(-LightDir, normal);
    float spec = pow(max(dot(viewDir, reflDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.texture_specular1, TexCoords).rgb;

    //attenuation
    float d = length(light.position - FragPos);
    float attenuation = 1.0/(light.constant + light.linear * d + light.quadratic * d * d);

    return attenuation * (diffuse + specular) + ambient;

}
