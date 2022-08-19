#pragma once
#include <Windows.h>
#include <string>
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")

#include "..\Library\ImGui\imgui.h"
#include "..\Library\ImGui\imgui_impl_dx9.h"
#include "..\Library\ImGui\imgui_impl_win32.h"
#include "..\Library\ImGui\imgui_internal.h"

#define VISIBLE settings::visible

namespace settings
{
	inline bool visible = true;
	inline const char* title = "Heaven";
	inline ImVec2 window_size = { 600, 400 };
	inline ImVec2 window_position = { 0, 0 };
	inline ImVec2 screen_res = { 0, 0 };
	inline DWORD window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
}