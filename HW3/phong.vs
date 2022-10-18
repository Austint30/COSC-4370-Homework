
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // TODO: Your code here
    // Remember to set gl_Position (correctly) or you will get a black screen...

    // Transformation chain
    // gl_Position = projection * view * model * vec4(position, 1.0);
    gl_Position = projection * view * model * vec4(position, 1.0);
    FragPos = vec3(model * vec4(position, 1.0));

    // Fix non-perpendicular normals on non-uniform scales
    Normal = mat3(transpose(inverse(model))) * normal;
} 
