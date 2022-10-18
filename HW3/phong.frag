
#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

// Lighting parameters
uniform float ambientStrength = 0.1;
uniform float specularStrength = 0.5;
uniform float specularComponent = 32.0;

void main()
{

    // Much of this code is derived from https://learnopengl.com/Lighting/Basic-Lighting

    // Ambient lighting --------------------------

        vec3 ambient = ambientStrength * lightColor;

    // -------------------------------------------


    // Diffuse lighting --------------------------

        // Surface normal
        vec3 normal = normalize(Normal);

        // Compute direction of light at fragment position
        vec3 lightDir = normalize(lightPos - FragPos);

        // Compute lighting strength caused by angle between the surface normal and light source
        float diff = max(dot(normal, lightDir), 0.0);

        vec3 diffuse = diff * lightColor;

    // -------------------------------------------


    // Specular lighting -------------------------

        // Compute direction of view
        vec3 viewDir = normalize(viewPos - FragPos);

        // Reflection direction of light
        vec3 reflectDir = reflect(-lightDir, normal);

        // Compute specular component
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularComponent);
        vec3 specular = specularStrength * spec * lightColor;

    // -------------------------------------------


    // Combine Ambient, Diffuse, and Specular lighting
    vec3 result = (ambient + diffuse + specular) * objectColor;

    // If gl_Position was set correctly, this gives a totally red cube
    color = vec4(result, 1.0);
} 
