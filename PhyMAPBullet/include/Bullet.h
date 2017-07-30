#pragma once

#if defined(WIN32) 
#if defined(BULLET_LIBRARY_EXPORTS)
#define BULLET_API __declspec(dllexport)
#elif defined(BULLET_LIBRARY_IMPORTS)
#define BULLET_API __declspec(dllimport)
#else
#define BULLET_API 
#endif
#else // WIN32
#define BULLET_API // LINUX
#endif // WIN32
