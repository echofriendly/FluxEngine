workspace "FluxEngine"
	filename "FluxEngine_%{_ACTION}"
	basedir "../"
	configurations { "Debug", "Release" }
    platforms {"x86", "x64"}
    warnings "Extra"
    rtti "Off"
	characterset ("MBCS")
	defines { "_CONSOLE", "D3D11" }
	--flags {"FatalWarnings"}
	language "C++"

    filter { "platforms:x64" }
		architecture "x64"
		defines {"x64", "PLATFORM_WINDOWS"}

	filter { "platforms:x86" }
		architecture "x32"
		defines {"x86", "PLATFORM_WINDOWS"}	

	filter { "configurations:Debug" }
			runtime "Debug"
		 	defines { "_DEBUG" }
		 	flags {  }
		 	symbols "On"
		 	optimize "Off"

	filter { "configurations:Release" }
		 	runtime "Release"
			defines { "NDEBUG" }
		 	flags {  }
		 	symbols "Off"
		 	optimize "Full"

	project "FluxEngine"
		filename "FluxEngine_%{_ACTION}"
		location "../FluxEngine"
		targetdir "../Build/$(ProjectName)_$(Platform)_$(Configuration)"
		objdir "!../Build/Intermediate/$(ProjectName)_$(Platform)_$(Configuration)"

		pchheader "FluxEngine.h"
		pchsource "../FluxEngine/FluxEngine.cpp"
		kind "StaticLib"

		files
		{ 
			"../FluxEngine/**.h",
			"../FluxEngine/**.hpp",
			"../FluxEngine/**.cpp",
			"../FluxEngine/**.inl"
		}

		includedirs 
		{ 
			"$(ProjectDir)",
			"../Libraries/ImgUI/include",
			"../Libraries/Fmod/inc",
			"../Libraries/Zlib/include",
			"../Libraries/PhysX 3.4/PhysX_3.4/include",
			"../Libraries/PhysX 3.4/PxShared/include",
		}

		libdirs
		{
			"../Libraries/Imgui/lib/%{cfg.platform}",
			"../Libraries/Fmod/lib/%{cfg.platform}",
			"../Libraries/Zlib/lib/%{cfg.platform}",
		}

		filter { "platforms:x64" }
			libdirs
			{
				"../Libraries/PhysX 3.4/PhysX_3.4/lib/vc14win64",
				"../Libraries/PhysX 3.4/PxShared/lib/vc14win64",
			}

		filter { "platforms:x86" }
			libdirs
			{
				"../Libraries/PhysX 3.4/PhysX_3.4/lib/vc14win32",
				"../Libraries/PhysX 3.4/PxShared/lib/vc14win32",
			}

	project "FluxGame"
		filename "FluxGame_%{_ACTION}"
		location "../FluxGame"
		targetdir "../Build/$(ProjectName)_$(Platform)_$(Configuration)"
		objdir "!../Build/Intermediate/$(ProjectName)_$(Platform)_$(Configuration)"

		pchheader "FluxGame.h"
		pchsource "../FluxGame/FluxGame.cpp"
		kind "WindowedApp"

		links {"FluxEngine"}

		files
		{ 
			"../FluxGame/**.h",
			"../FluxGame/**.hpp",
			"../FluxGame/**.cpp",
			"../FluxGame/**.inl"
		}

		includedirs 
		{ 
			"$(ProjectDir)/../FluxEngine",
			"$(ProjectDir)",
			"../Libraries/ImgUI/include",
			"../Libraries/Fmod/inc",
			"../Libraries/Zlib/include",
			"../Libraries/PhysX 3.4/PhysX_3.4/include",
			"../Libraries/PhysX 3.4/PxShared/include",
		}

		libdirs
		{
			"../Libraries/Imgui/lib/%{cfg.platform}",
			"../Libraries/Fmod/lib/%{cfg.platform}",
			"../Libraries/Zlib/lib/%{cfg.platform}",
		}

		filter { "configurations:Debug" }
		 	postbuildcommands
			{ 
				"xcopy \"..\\Libraries\\Zlib\\bin\\%{cfg.platform}\\Zlib_DEBUG.dll\" \"$(OutDir)\" /Y /F /D",
			}

		filter { "configurations:Release" }
		 	postbuildcommands
			{ 
				"xcopy \"..\\Libraries\\Zlib\\bin\\%{cfg.platform}\\Zlib.dll\" \"$(OutDir)\" /Y /F /D",
				"dir \"$(SolutionDir)FluxGame\\Resources\\\" /s /b /a-d > \"$(SolutionDir)\\FluxPak\\ResponseFile.txt\"",
				"\"$(SolutionDir)FluxPak\\PakFileCompression.exe\" -r \"$(SolutionDir)\\FluxPak\\ResponseFile.txt\" -p \"$(SolutionDir)FluxGame\\Resources.pak\" -b \"$(SolutionDir)FluxGame/Resources/",
			}

		filter { "platforms:x64" }
			libdirs
			{
				"../Libraries/PhysX 3.4/PhysX_3.4/lib/vc14win64",
				"../Libraries/PhysX 3.4/PxShared/lib/vc14win64",
			}
			postbuildcommands
			{ 
				"xcopy \"..\\Libraries\\Fmod\\bin\\x64\\fmod64.dll\" \"$(OutDir)\" /F /Y /D",
				"xcopy \"..\\Libraries\\PhysX 3.4\\PhysX_3.4\\bin\\vc14win64\\nvToolsExt64_1.dll\" \"$(OutDir)\" /F /Y /D",
			}

		filter { "platforms:x86" }
			libdirs
			{
				"../Libraries/PhysX 3.4/PhysX_3.4/lib/vc14win32",
				"../Libraries/PhysX 3.4/PxShared/lib/vc14win32",
			}
			postbuildcommands
			{ 
				"xcopy \"..\\Libraries\\Fmod\\bin\\x86\\fmod.dll\" \"$(OutDir)\" /F /Y /D",
				"xcopy \"..\\Libraries\\PhysX 3.4\\PhysX_3.4\\bin\\vc14win32\\nvToolsExt86_1.dll\" \"$(OutDir)\" /F /Y /D",
			}

		filter { "configurations:Debug", "platforms:x86" }
			postbuildcommands
			{ 
				"xcopy \"..\\Libraries\\PhysX 3.4\\PhysX_3.4\\bin\\vc14win32\\PhysX3CommonDEBUG_x86.dll\" \"$(OutDir)\" /F /Y /D",
				"xcopy \"..\\Libraries\\PhysX 3.4\\PhysX_3.4\\bin\\vc14win32\\PhysX3DEBUG_x86.dll\" \"$(OutDir)\" /F /Y /D",
				"xcopy \"..\\Libraries\\PhysX 3.4\\PxShared\\bin\\vc14win32\\PxFoundationDEBUG_x86.dll\" \"$(OutDir)\" /F /Y /D",
				"xcopy \"..\\Libraries\\PhysX 3.4\\PxShared\\bin\\vc14win32\\PxPvdSDKDEBUG_x86.dll\" \"$(OutDir)\" /F /Y /D",
			}

		filter { "configurations:Release", "platforms:x86" }
			postbuildcommands
			{ 
				"xcopy \"..\\Libraries\\PhysX 3.4\\PhysX_3.4\\bin\\vc14win32\\PhysX3Common_x86.dll\" \"$(OutDir)\" /F /Y /D",
				"xcopy \"..\\Libraries\\PhysX 3.4\\PhysX_3.4\\bin\\vc14win32\\PhysX3_x86.dll\" \"$(OutDir)\" /F /Y /D",
				"xcopy \"..\\Libraries\\PhysX 3.4\\PxShared\\bin\\vc14win32\\PxFoundation_x86.dll\" \"$(OutDir)\" /F /Y /D",
				"xcopy \"..\\Libraries\\PhysX 3.4\\PxShared\\bin\\vc14win32\\PxPvdSDK_x86.dll\" \"$(OutDir)\" /F /Y /D",
			}

		filter { "configurations:Debug", "platforms:x64" }
			postbuildcommands
			{ 
				"xcopy \"..\\Libraries\\PhysX 3.4\\PhysX_3.4\\bin\\vc14win64\\PhysX3CommonDEBUG_x64.dll\" \"$(OutDir)\" /F /Y /D",
				"xcopy \"..\\Libraries\\PhysX 3.4\\PhysX_3.4\\bin\\vc14win64\\PhysX3DEBUG_x64.dll\" \"$(OutDir)\" /F /Y /D",
				"xcopy \"..\\Libraries\\PhysX 3.4\\PxShared\\bin\\vc14win64\\PxFoundationDEBUG_x64.dll\" \"$(OutDir)\" /F /Y /D",
				"xcopy \"..\\Libraries\\PhysX 3.4\\PxShared\\bin\\vc14win64\\PxPvdSDKDEBUG_x64.dll\" \"$(OutDir)\" /F /Y /D",
			}

		filter { "configurations:Release", "platforms:x64" }
			postbuildcommands
			{ 
				"xcopy \"..\\Libraries\\PhysX 3.4\\PhysX_3.4\\bin\\vc14win64\\PhysX3Common_x64.dll\" \"$(OutDir)\" /F /Y /D",
				"xcopy \"..\\Libraries\\PhysX 3.4\\PhysX_3.4\\bin\\vc14win64\\PhysX3_x64.dll\" \"$(OutDir)\" /F /Y /D",
				"xcopy \"..\\Libraries\\PhysX 3.4\\PxShared\\bin\\vc14win64\\PxFoundation_x64.dll\" \"$(OutDir)\" /F /Y /D",
				"xcopy \"..\\Libraries\\PhysX 3.4\\PxShared\\bin\\vc14win64\\PxPvdSDK_x64.dll\" \"$(OutDir)\" /F /Y /D",
			}

newaction {
		trigger     = "clean",
		description = "Remove all binaries and generated files",

		execute = function()
			os.rmdir("../Build")
			os.rmdir("../ipch")
		end
	}