#pragma once

//Force to disable RTTI because we have our own system
#ifdef _CPPRTTI
#error RTTI is enabled. Disable using "/GR-"
#endif

#if !defined(_MBCS)
#error Character set must be MBCS
#endif

#pragma region
//Standard Library
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <sstream>
#include <memory>
#include <iomanip>
#include <queue>
#include <limits>
#pragma endregion STL

#ifdef MODULE_SDL2
#include <SDL.h>
#endif

#ifdef MODULE_PHYSX
#include <PxPhysicsAPI.h>
#endif

#pragma region
#include "External/Imgui/imgui.h"
#pragma endregion IMGUI

#ifdef MODULE_D3D11
//DirectXMath
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <dxgi.h>
#include <d3d11.h>
#include <DirectXColors.h>
using namespace DirectX;
#include "External/SimpleMath/SimpleMath.h"
using namespace DirectX::SimpleMath;
#endif

#ifdef MODULE_FMOD
#include "fmod.hpp"
#pragma warning(push)
#pragma warning(disable: 4505) //Unreferenced local function removed (FMOD_ErrorString)
#include "fmod_errors.h"
#pragma warning(pop)
#endif

#pragma region
//Engine core include
#include "Core/Types.h"
#include "Misc/Misc.h"
#include "Helpers/Paths.h"
#include "Helpers/SmartInterface.h"
#include "Helpers/LogMacros.h"
#include "Helpers/AssertMacros.h"
#include "Helpers/Utility.h"
#include "Misc/TimeSpan.h"
#include "Misc/DateTime.h"

#include "Diagnostics/Console.h"
#include "Diagnostics/Profiler.h"

#include "Core/TypeInfo.h"
#include "Core/Context.h"
#include "Core/Object.h"
#include "Core/Delegates.h"
#include "Core/GameTimer.h"

#include "Audio/AudioEngine.h"

#include "Math/MathHelp.h"
#include "Math/MathTypes.h"

#include "FileSystem/FileSystem.h"
#include "FileSystem/File/File.h"

#include "Content/ResourceManager.h"
#pragma endregion ENGINE INCLUDES