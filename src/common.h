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

/// <summary>
/// The UTF-8 string type.
/// </summary>
typedef std::string														SLUtf8String;

/// <summary>
/// The UTF-16 string type.
/// </summary>
typedef std::wstring													SLUtf16String;

/// <summary>
/// The UTF-8 output string stream.
/// </summary>
typedef std::basic_ostringstream<char>									SLOUtf8StringStream;

/// <summary>
/// The UTF-16 output string stream.
/// </summary>
typedef std::basic_ostringstream<wchar_t>								SLOUtf16StringStream;

/// <summary>
/// The UTF-8 and UTF16 converter type.
/// </summary>
typedef std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> SLUtf16StringConvert;

#endif