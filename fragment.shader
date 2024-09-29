#version 330 core
out vec4 pixelcolor;
in vec3 fragcolor;

void main()
{
	pixelcolor = vec4(fragcolor,1.0f);
}