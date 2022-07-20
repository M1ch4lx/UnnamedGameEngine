#pragma once

// ImGui
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

// Reduces redundant bindings
#define REMEMBER_BINDING() \
static void* bounded = nullptr; \
if (bounded == this) { return; } \
bounded = this