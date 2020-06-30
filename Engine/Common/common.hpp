#pragma once

#ifdef NOVA_BUILD_DLL
	#define NOVA_API __declspec(dllexport)
#else
	#define NOVA_API __declspec(dllimport)
#endif

// Disable warning for STL using in private data member
#pragma warning(disable:4251)


#include "Engine/Types/base_types.hpp"


namespace nova
{
	constexpr const char* k_engine_channel = "Engine";
}