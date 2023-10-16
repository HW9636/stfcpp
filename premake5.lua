workspace "STFCPP"
    configurations {
        "Debug",
        "Release"
    }

project "STFCPP"
    language "C++"
    cppdialect "C++17"
    kind "ConsoleApp"

    targetdir ("bin/%{cfg.architecture}/%{prj.name}")
    objdir ("obj/%{cfg.architecture}/%{prj.name}")

    includedirs {
        "include"
    }


    files {
        "include/**.h",
        "examples/**.cpp",
        "examples/**.hpp"
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

    filter "configurations:Debug"
        symbols "On"
        optimize "Off"

        defines {
            "STFCPP_BUILD_EXAMPLES"
        }

    filter "configurations:Release"
        optimize "On"
        symbols "Off"

        defines {
            "STFCPP_BUILD_EXAMPLES"
        }