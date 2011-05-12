// from the GLOB forums

#ifndef WCHAR_LOGGING_H_
#define WCHAR_LOGGING_H_

#include <iostream>
#include <string>
#include <wchar.h>

inline std::ostream& operator<<(std::ostream& out, const wchar_t* str)
{
#ifdef _WIN32
#pragma warning(disable:4996)
#endif // _WIN32
    size_t len = wcsrtombs(NULL, &str, 0, NULL);
    char* buf = (char*)malloc(len + 1);
    buf[len] = 0;
    wcsrtombs(buf, &str, len, NULL);
    out << buf;
    free(buf);
    return out;
}

inline std::ostream& operator<<(std::ostream& out, const std::wstring& str)
{
    return operator<<(out, str.c_str());
}

inline std::ostream& LogWString(std::ostream& out, const wchar_t* str)
{
    return operator<<(out, str);
}

inline std::ostream& LogWString(std::ostream& out, const std::wstring&str)
{
    return operator<<(out, str.c_str());
}

#endif  // WCHAR_LOGGING_H_
