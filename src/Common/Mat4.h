#ifndef __FD_MAT4_H__
#define __FD_MAT4_H__
namespace fd
{

class Mat4
{
	enum {MATRIX_SIZE = 16 * sizeof(float)};

public:
	Mat4();

	Mat4(float num);

	Mat4(const Mat4& mat);

	Mat4(const float* mat);
private:
	void set(float num);
	void set(const Mat4& mat);
	void set(const float* mat);

private:
	float m[4][4];
};

}
#endif	//__FD_MAT4_H__