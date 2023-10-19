#version 330 core

struct PointLight{
    vec2 position;

    vec3 ambient;
//    vec3 diffuse;
    // I don't know if I want to use diffuse or specular lighting, maybe later

    float constant;
    float linear;
    float quadratic;
};

in vec2 TexCoords;
in vec2 fragPos;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;
uniform PointLight pointLights[256];
uniform int usedLights;

vec3 calcPointLight(PointLight light, vec2 fragmentPosition){
//    vec2 lightDirection = normalize(light.position - fragmentPosition);
//    vec3 diffuse = light.diffuse * max(dot(lightDirection, normal), 0.0);
    float lightDistance = length(light.position - fragmentPosition);
    float attenuation = 1.0 / (light.constant + light.linear * lightDistance + light.quadratic * pow(lightDistance, 2));
//    return light.ambient + diffuse;
    vec3 ambient = light.ambient * attenuation;

    return ambient;
}

void main()
{
    vec4 textureColor = texture(image, TexCoords);
    if(textureColor.a < 0.1){
        discard;
    }

    vec3 lightColor = vec3(0.2);
    for(int i=0; i<usedLights; i++){
        lightColor += calcPointLight(pointLights[i], fragPos);
    }

    color = vec4(spriteColor, 1.0) * textureColor * min(vec4(lightColor, 1.0f), 1.0f);
}