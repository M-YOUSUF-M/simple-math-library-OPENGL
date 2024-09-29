#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
out vec3 fragcolor;

uniform mat4 mvpMatrix;


void main()
{
    // Apply translation after scaling
    gl_Position = mvpMatrix * vec4(position, 1.0f);
    fragcolor = color;
}