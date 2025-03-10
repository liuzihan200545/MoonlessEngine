workspace "MoonlessEngine"
    startproject "SandBox"
    architecture "x86_64"

    flags { "MultiProcessorCompile" }
        
    configurations{
        "Debug",
        "Release",
        "Dist"
    }

    defines{
        "_CRT_SECURE_NO_WARNINGS"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["Glad"] = "include/glad/include"
IncludeDirs["Imgui"] = "include/imgui"
IncludeDirs["stb_image"] = "include/stb_image/include"

group "dependencies"
    include "include/glad"
    include "include/imgui"
    include "include/stb_image"
group ""

project "MoonlessEngine"
    location "MoonlessEngine"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    cppdialect "C++20"
    
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
        "MoonlessEngine/src/",
        "%{IncludeDirs.Glad}",
        "%{IncludeDirs.Imgui}",
	"%{IncludeDirs.stb_image}"
    }

    libdirs {
        "%{wks.location}/lib"
    }

    links { "glfw3_mt.lib", "Glad", "Imgui", "stb_image" }

    filter "system:windows"
        systemversion "latest"
        buildoptions { "/utf-8" }

        defines{
            "ML_BUILD_DLL",
            "ML_ENABLE_ASSERTS",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "ML_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "ML_RELEASE"
        runtime "Release"
        symbols "off"
        optimize "on"   

    filter "configurations:Dist"
        defines "ML_DIST"
        runtime "Release"
        symbols "off"
        optimize "on"

    linkoptions { "/NODEFAULTLIB:LIBCMT" }

project "SandBox"
    location "SandBox"
    kind "ConsoleApp"
    language "C++"

    staticruntime "on"

    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{wks.location}/include",
        "MoonlessEngine/src",
        "include/glad/include",
        "MoonlessEngine/src/Moonless",
    }

    filter "system:windows"
    cppdialect "C++20"
    systemversion "latest"
    buildoptions { "/utf-8" }

    defines{
        "ML_ENABLE_ASSERTS"
    }

    links{
        "MoonlessEngine"
    }

    filter "configurations:Debug"
        defines "ML_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "ML_RELEASE"
        runtime "Release"
        symbols "off"
        optimize "on"
    
    filter "configurations:Dist"
        defines "ML_DIST"
        runtime "Release"
        symbols "off"
        optimize "on"
    linkoptions { "/NODEFAULTLIB:LIBCMT" }

project "Editor"
    location "Editor"
    kind "ConsoleApp"
    language "C++"

    staticruntime "on"

    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{wks.location}/include",
        "MoonlessEngine/src",
        "include/glad/include",
        "MoonlessEngine/src/Moonless",
    }

    filter "system:windows"
    cppdialect "C++20"
    systemversion "latest"
    buildoptions { "/utf-8" }

    defines{
        "ML_ENABLE_ASSERTS"
    }

    links{
        "MoonlessEngine"
    }

    filter "configurations:Debug"
        defines "ML_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "ML_RELEASE"
        runtime "Release"
        symbols "off"
        optimize "on"
    
    filter "configurations:Dist"
        defines "ML_DIST"
        runtime "Release"
        symbols "off"
        optimize "on"
    linkoptions { "/NODEFAULTLIB:LIBCMT" }

