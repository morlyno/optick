project "OptickCore"
    uuid "830934D9-6F6C-C37D-18F2-FB3304348F00"
    kind "StaticLib"
    language "c++"
    cppdialect "c++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs
    {
        "src"
    }

    files
    {
        "src/**.cpp",
        "src/**.h", 
    }

    vpaths
    {
        ["api"] = { 
            "src/optick.h",
            "src/optick.config.h",
        },
    }

    defines
    {
        "USE_OPTICK=1",
        "OPTICK_ENABLE_GPU=0",
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"
        
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
        defines "NDEBUG"
        defines "_NDEBUG"