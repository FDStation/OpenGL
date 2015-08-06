#version 330

layout (location = 0) in vec3 vPosition;

uniform float gScale;
uniform mat4 gWorld;

out vec4 Color;

void main(void)
{
	Color = vec4(clamp(vPosition, 0.0, 1.0), 1.0);		//clamp�ǶԵ�һ�������ڵ�ÿһ���������������䴦�ڵڶ�����������֮��
	gl_Position = gWorld * vec4(vPosition, 1.0);			//˳���ܱ䡣�����Ǳ任�����������
}