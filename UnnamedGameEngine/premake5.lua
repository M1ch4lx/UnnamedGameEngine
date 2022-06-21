project "UnnamedGameEngine"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "Pch.h"
    pchsource "Src/Pch.cpp"

    files
    {
        "Src/**.h",
        "Src/**.cpp",

        -- Vendor files:
        "Vendor/glad/**.h",
        "Vendor/glad/**.cpp"
    }

    includedirs
    {
        ".",
        "Src",
        "Vendor",
        "Vendor/glfw/include",
        "Vendor/glad"
    }

    dependson
    {
        "GLFW"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    libdirs
    {
        "Vendor/mono"
    }

    defines
    {
        "ATRON_WINDOWS"
    }

    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

    --postbuildcommands
    --{
    --    "{COPY} %{prj.name}/Vendor/mono/mono-2.0-sgen.dll %{cfg.targetdir}"
    --}