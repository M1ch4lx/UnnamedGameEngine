workspace "UnnamedGameEngine"
	architecture "x64"
	startproject "UnnamedGameEngine"

	configurations
	{
		"Debug",
		"Release"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Dependencies:
include "UnnamedGameEngine/Vendor"

include "UnnamedGameEngine"