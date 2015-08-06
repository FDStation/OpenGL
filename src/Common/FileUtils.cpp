#include "FileUtils.h"
#include "Windows.h"

void getRootPath(char* utf8Path, size_t size)
{
	WCHAR utf16Path[256] = {0};
	GetCurrentDirectoryW(sizeof(utf16Path)-1, utf16Path);

	int nNum = WideCharToMultiByte(CP_UTF8, 0, utf16Path, -1, utf8Path, size, nullptr, nullptr);

	convertPathFormatToUnixStyle(utf8Path);
}

void convertPathFormatToUnixStyle(char* path)
{
	int len = strlen(path);
	for (int i = 0; i != len; ++i)
	{
		if (*(path + i) == '\\')
		{
			*(path + i) = '/';
		}
	}
}

void getFullPath(const char* filePath, char* fullPath, size_t size)
{
	char path[256] = {0};

	getRootPath(path, sizeof(path));

	sprintf_s(fullPath, size, "%s/%s", path, filePath);
}
