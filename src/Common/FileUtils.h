#ifndef __FD_FILEUTILS_H__
#define __FD_FILEUTILS_H__

#include <cstdio>
#include <assert.h>

#ifdef _DEBUG
#define FD_ASSERT(x)	\
	do							\
	{								\
	assert(x);				\
	} while (0);
#else
#define FD_ASSERT(x) do {} while (0);
#endif






void getFullPath(const char* filePath, char* fullPath, size_t size);

void getRootPath(char* utf8Path, size_t size);

void convertPathFormatToUnixStyle(char* path);

#endif // !__FD_FILEUTILS_H__



