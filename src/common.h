#ifndef COMMON_H
#define COMMON_H

#include <stdarg.h>
#include <memory>
#include <vector>
#include <sstream>
#include <string>
#include <xlocbuf>
#include <codecvt>

#define LOG_STRING_MAX_LEN 4096

typedef std::string														SLUtf8String;
typedef std::wstring													SLUtf16String;
typedef std::basic_ostringstream<char>									SLOUtf8StringStream;
typedef std::basic_ostringstream<wchar_t>								SLOUtf16StringStream;
typedef std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> SLUtf16StringConvert;

#endif