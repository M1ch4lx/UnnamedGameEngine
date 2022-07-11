project "GLFW"
	location "glfw"
	kind "StaticLib"
	language "C"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.location}/include/GLFW/glfw3.h",
		"%{prj.location}/include/GLFW/glfw3native.h",
		"%{prj.location}/src/glfw_config.h",
		"%{prj.location}/src/context.c",
		"%{prj.location}/src/init.c",
		"%{prj.location}/src/input.c",
		"%{prj.location}/src/monitor.c",
		"%{prj.location}/src/platform.c",
		"%{prj.location}/src/window.c",
		"%{prj.location}/src/vulkan.c",
		"%{prj.location}/src/null_init.c",
		"%{prj.location}/src/null_monitor.c",
		"%{prj.location}/src/null_window.c",
		"%{prj.location}/src/null_joystick.c"
	}

	--filter "system:linux"
	--	files
	--	{
	--		"%{prj.location}/src/x11_init.c",
	--		"%{prj.location}/src/x11_monitor.c",
	--		"%{prj.location}/src/x11_window.c",
	--		"%{prj.location}/src/xkb_unicode.c",
	--		"%{prj.location}/src/posix_time.c",
	--		"%{prj.location}/src/posix_thread.c",
	--		"%{prj.location}/src/glx_context.c",
	--		"%{prj.location}/src/egl_context.c",
	--		"%{prj.location}/src/osmesa_context.c",
	--		"%{prj.location}/src/linux_joystick.c"
	--	}
	--
	--	defines
	--	{
	--		"_GLFW_X11"
	--	}

	filter "system:windows"
        files
        {
            "%{prj.location}/src/win32_init.c",
            "%{prj.location}/src/win32_joystick.c",
            "%{prj.location}/src/win32_monitor.c",
			"%{prj.location}/src/win32_module.c",
            "%{prj.location}/src/win32_time.c",
            "%{prj.location}/src/win32_thread.c",
            "%{prj.location}/src/win32_window.c",
            "%{prj.location}/src/wgl_context.c",
            "%{prj.location}/src/egl_context.c",
            "%{prj.location}/src/osmesa_context.c"
        }

        defines 
        { 
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

project "ImGui"
	location "imgui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs
    {
        "imgui",
		"glfw/include"
    }

	files
	{
		"%{prj.location}/imconfig.h",
		"%{prj.location}/imgui.h",
		"%{prj.location}/imgui.cpp",
		"%{prj.location}/imgui_draw.cpp",
		"%{prj.location}/imgui_internal.h",
		"%{prj.location}/imgui_widgets.cpp",
		"%{prj.location}/imstb_rectpack.h",
		"%{prj.location}/imstb_textedit.h",
		"%{prj.location}/imstb_truetype.h",
		"%{prj.location}/imgui_tables.cpp",

		-- Backends
		"%{prj.location}/backends/imgui_impl_glfw.h",
		"%{prj.location}/backends/imgui_impl_glfw.cpp",

		"%{prj.location}/backends/imgui_impl_opengl3.h",
		"%{prj.location}/backends/imgui_impl_opengl3.cpp"
	}