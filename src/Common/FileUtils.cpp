#include "FileUtils.h"
#include "Windows.h"
#include <iostream>

void getRootPath(char* utf8Path, size_t size)
{
	WCHAR utf16Path[256] = {0};
	GetCurrentDirectoryW(sizeof(utf16Path)-1, utf16Path);

	int nNum = WideCharToMultiByte(CP_UTF8, 0, utf16Path, -1, utf8Path, size, nullptr, nullptr);

	convertPathFormatToUnixStyle(utf8Path);

	std::string root(utf8Path);

	std::string::size_type pos = root.find("Debug");
	if (pos != std::string::npos)
	{
		for (int i = 0; i != 5; ++i)
		{
			*(utf8Path + pos + i) = '\0';
		}
	}
	pos = root.find("Release");
	if (pos != std::string::npos)
	{
		for (int i = 0; i != 7; ++i)
		{
			*(utf8Path + pos + i) = '\0';
		}
	}
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

	sprintf_s(fullPath, size, "%s%s", path, filePath);
}
