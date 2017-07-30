#pragma once

#if defined(WIN32) 
#if defined(COMMON_LIBRARY_EXPORTS)
#define COMMON_API __declspec(dllexport)
#elif defined(COMMON_LIBRARY_IMPORTS)
#define COMMON_API __declspec(dllimport)
#else
#define COMMONAPI 
#endif
#else // WIN32
#define COMMON_API // LINUX
#endif // WIN32
