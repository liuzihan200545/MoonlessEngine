workspace "MoonlessEngine"
    startproject "SandBox"
    architecture "x64"

    configurations{
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "MoonlessEngine"
    location "MoonlessEngine"
    kind "SharedLib"
    language "C++"
    
    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

    pchheader "mlpch.h"
    pchsource "MoonlessEngine/src/mlpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{wks.location}/include",
        "MoonlessEngine/src/Moonless",
        "MoonlessEngine/src/"
    }

    libdirs {
        "%{wks.location}/lib"
    }

    links { "glfw3_mt" }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
        buildoptions { "/utf-8" }
        linkoptions { "/NODEFAULTLIB:LIBCMT" }

        defines{
            "ML_PLATFORM_WINDOWS",
            "ML_BUILD_DLL",
            "ML_ENABLE_ASSERTS"
        }

        postbuildcommands{
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir .. "/SandBox")
        }

    filter "configurations:Debug"
        defines "ML_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "ML_RELEASE"
        symbols "On"

    filter "configurations:Dist"
        defines "ML_DIST"
        symbols "On"

project "SandBox"
    location "SandBox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{wks.location}/include",
        "MoonlessEngine/src"
    }

    filter "system:windows"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"
    buildoptions { "/utf-8" }

    defines{
        "ML_PLATFORM_WINDOWS",
        "ML_ENABLE_ASSERTS"
    }

    links{
        "MoonlessEngine"
    }

    filter "configurations:Debug"
        defines "ML_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "ML_RELEASE"
        symbols "On"

    filter "configurations:Dist"
        defines "ML_DIST"
        symbols "On"