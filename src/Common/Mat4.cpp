#include <cstring>

#include "FileUtils.h"
#include "Mat4.h"
namespace fd
{

Mat4::Mat4(float num)
{
	set(num);
}


Mat4::Mat4()
{

}

Mat4::Mat4(const Mat4& mat)
{
	set(mat);
}

Mat4::Mat4(const float* mat)
{
	set(mat);
}

void Mat4::set(float num)
{
	m[0][0] = num;	m[0][1] = 0;		m[0][2] = 0;		m[0][3] = 0;
	m[1][0] = 0;		m[1][1] = num;	m[1][2] = 0;		m[1][3] = 0;
	m[2][0] = 0;		m[2][1] = 0;		m[2][2] = num;	m[2][3] = 0;
	m[3][0] = 0;		m[3][1] = 0;		m[3][2] = 0;		m[3][3] = num;
}

void Mat4::set(const Mat4& mat) 
{
#ifdef _WIN32
	memcpy_s(this->m, MATRIX_SIZE, mat.m, MATRIX_SIZE);
#else
	memcpy(this->m, mat.m, MATRIX_SIZE);
#endif
}


void Mat4::set(const float* mat)
{
	FD_ASSERT(mat);
#ifdef _WIN32
	memcpy_s(this->m, MATRIX_SIZE, mat, MATRIX_SIZE);
#else
	memcpy(this->m, mat, MATRIX_SIZE);
#endif
}

}