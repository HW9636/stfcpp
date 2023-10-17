workspace "STFCPP"
    configurations {
        "BuildExamples",
        "BuildTests"
    }

project "STFCPP"
    language "C++"
    cppdialect "C++14"
    kind "ConsoleApp"

    targetdir ("bin/%{cfg.architecture}/%{prj.name}")
    objdir ("obj/%{cfg.architecture}/%{prj.name}")

    includedirs {
        "include"
    }


    files {
        "include/**.h",
        "examples/**.cpp",
        "examples/**.hpp",
        "examples/**.h",
    }

    filter "system:windows"
        architecture "x86_64"
        systemversion "latest"

    filter "system:macosx"
        architecture "x86_64"
        systemversion "10.15"

    filter "system:linux"
        architecture "x86_64"
        systemversion "latest"

    symbols "On"
    optimize "Off"

    filter "configurations:BuildTests"
        defines {
			"STFCPP_BUILD_TESTS"        
		}

    filter "configurations:BuildExamples"
        defines {
            "STFCPP_BUILD_EXAMPLES"
        }
