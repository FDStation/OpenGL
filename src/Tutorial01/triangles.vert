#version 330

layout (location = 0) in vec3 vPosition;

uniform float gScale;
uniform mat4 gWorld;

out vec4 Color;

void main(void)
{
	Color = vec4(clamp(vPosition, 0.0, 1.0), 1.0);		//clamp是对第一个参数内的每一个分量做处理，让其处于第二第三个参数之间
	gl_Position = gWorld * vec4(vPosition, 1.0);			//顺序不能变。必须是变换矩阵乘以向量
}