#version 330

layout (location = 0) in vec3 vPosition;

uniform mat4 uWorld;

out vec4 Color;

void main(void)
{
	gl_Position = uWorld * vec4(vPosition, 1.0);
	Color = vec4(clamp(vPosition, 0.0, 1.0), 1.0);
}