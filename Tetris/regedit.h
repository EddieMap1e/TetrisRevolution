#pragma once
#include <Windows.h>
#include <tchar.h>

DWORD get_dowrd(char *path, char *keyname)	//失败返回unsigned long 最大值
{
	HKEY key;
	LPCTSTR data = _T(path);
	DWORD dwValue = ULONG_MAX;
	if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_CURRENT_USER, data, 0, KEY_READ, &key))
	{
		DWORD dwSize = sizeof(DWORD);
		DWORD dwType = REG_DWORD;
		if (::RegQueryValueEx(key, _T(keyname), 0, &dwType, (LPBYTE)&dwValue, &dwSize) != ERROR_SUCCESS)
		{
			::RegCloseKey(key);
			return ULONG_MAX;
		}
	}
	return dwValue;
}

bool write_dword(char *path, char *fileFolder, char *keyname, DWORD value)
{
	HKEY hkey;
	HKEY hTmpKey;
	DWORD dwSize = sizeof(DWORD);
	DWORD dwType = REG_DWORD;
	LPCTSTR data = _T(path);
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, data, 0, KEY_SET_VALUE, &hkey))
	{
		if (ERROR_SUCCESS == ::RegCreateKey(hkey, _T(fileFolder), &hTmpKey))
		{
			if (ERROR_SUCCESS != ::RegSetValueEx(hTmpKey, _T(keyname), 0, REG_DWORD, (CONST BYTE*)&value, sizeof(DWORD)))
			{
				return false;
			}
		}
		else return false;
	}
	else return false;
	return true;
}

