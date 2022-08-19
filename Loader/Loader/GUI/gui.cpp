#include "gui.hpp"

int my_image_width = 0;
int my_image_height = 0;
PDIRECT3DTEXTURE9 my_texture = NULL;

bool Release = false;
bool Alpha = false;

bool AuthorizationSuccessful = false;

ImFont* SelectFont;
ImFont* CSFont;
ImFont* BackFont;

DWORD pid;
Injector inj;
 
void gui::gui_element()
{
	if (!VISIBLE)
		return;

	ImGui::SetNextWindowPos(ImVec2(settings::window_position.x, settings::window_position.y), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(settings::window_size.x, settings::window_size.y));
	ImGui::SetNextWindowBgAlpha(1.0f);

	ImGui::Begin(settings::title, &settings::visible, settings::window_flags);
	{
		inj.hwndproc = FindWindowA(0, "Counter-Strike: Global Offensive - Direct3D 9");
		GetWindowThreadProcessId(inj.hwndproc, &pid);
		inj.process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		inj.clientDLL = inj.GetModule(pid, "client.dll");

		settings::window_position = ImGui::GetWindowPos();
		ImDrawList* drawListR = ImGui::GetWindowDrawList();

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 20.f);
		drawListR->PushClipRectFullScreen();
		drawListR->AddRectFilled(ImVec2(settings::window_position.x, settings::window_position.y + 370), ImVec2(settings::window_position.x + 600, settings::window_position.y + 400), IM_COL32(70, 70, 70, 255), 4.f);
		ImGui::PopClipRect();
		ImGui::PopStyleVar();

		if (!Release && !Alpha && !AuthorizationSuccessful)
		{
			drawListR->AddRectFilled(ImVec2(settings::window_position.x + 15, settings::window_position.y + 40), ImVec2(settings::window_position.x + 585, settings::window_position.y + 130), IM_COL32(70, 70, 70, 255), 4.f);
			drawListR->AddRectFilled(ImVec2(settings::window_position.x + 15, settings::window_position.y + 140), ImVec2(settings::window_position.x + 585, settings::window_position.y + 230), IM_COL32(70, 70, 70, 255), 4.f);

			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.f);
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.192f, 0.192f, 0.192f, 1.f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.192f, 0.192f, 0.192f, 1.f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.192f, 0.192f, 0.192f, 1.f));

			ImGui::PushFont(SelectFont);
			ImGui::SetCursorPos(ImVec2(440, 65));
			if (ImGui::Button("Select##Release", ImVec2(120, 40)))
			{
				Release = true;
			}

			ImGui::SetCursorPos(ImVec2(440, 165));
			if (ImGui::Button("Select##Alpha", ImVec2(120, 40)))
			{
				Alpha = true;
			}
			ImGui::PopFont();
			ImGui::PopStyleColor(3);
			ImGui::PopStyleVar();

			ImGui::PushFont(CSFont);
			ImGui::SetCursorPos(ImVec2(100, 70));
			ImGui::Text("CS:GO Release");

			ImGui::SetCursorPos(ImVec2(100, 170));
			ImGui::Text("CS:GO Alpha");
			ImGui::PopFont();


			ImGui::SetCursorPos(ImVec2(30, 55));
			ImGui::Image((void*)my_texture, ImVec2(60, 60));

			ImGui::SetCursorPos(ImVec2(30, 155));
			ImGui::Image((void*)my_texture, ImVec2(60, 60));
		}

		if (Release == true)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.f);
			ImGui::PushFont(BackFont);
			ImGui::SetCursorPos(ImVec2(10, 10));
			if (ImGui::Button("<- Back", ImVec2(75, 20)))
			{
				Release = false;
			}
			ImGui::PopFont();

			
			ImGui::PushFont(SelectFont);
			ImGui::SetCursorPos(ImVec2(200, 300));
			if (pid > 0)
			{
				if (ImGui::Button("Inject", ImVec2(200, 50)))
				{
					LPVOID ntOpenFile = GetProcAddress(LoadLibraryW(L"ntdll"), "NtOpenFile");
					if (ntOpenFile) {
						char originalBytes[5];
						memcpy(originalBytes, ntOpenFile, 5);
						WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 5, NULL);
					}
					std::string dwnld_URL = "https://github.com/OukiLove/oukilove.github.io/raw/main/assets/loader/Oreo.dll";
					std::string savepath = "C:\\Oreo\\Oreo.dll";
					URLDownloadToFile(NULL, dwnld_URL.c_str(), savepath.c_str(), 0, NULL);
					inj.inject(pid, savepath.c_str());
				}
			}
			else
			{
				if (ImGui::Button("Run CS:GO", ImVec2(200, 50)))
				{
					ShellExecuteA(NULL, "open", "steam://rungameid/730", NULL, NULL, SW_SHOWNORMAL);
				}
			}
			ImGui::PopFont();
			ImGui::PopStyleVar();
			
			/*ImGui::PushFont(CSFont);
			ImGui::SetCursorPos(ImVec2(270, 180));
			ImGui::Text("Soon...");
			ImGui::PopFont();*/
		}

		if (Alpha == true)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.f);
			ImGui::PushFont(BackFont);
			ImGui::SetCursorPos(ImVec2(10, 10));
			if (ImGui::Button("<- Back", ImVec2(75, 20)))
			{
				Alpha = false;
			}
			ImGui::PopFont();

			ImGui::PushFont(SelectFont);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.275, 0.275, 0.275, 1.f));
			ImGui::SetCursorPos(ImVec2(60, 150));
			ImGui::InputText("##Key", gui::key, IM_ARRAYSIZE(gui::key));
			ImGui::PopStyleColor();
			ImGui::SetCursorPos(ImVec2(200, 300));
			if (ImGui::Button("Login", ImVec2(200, 50)))
			{

			}
			ImGui::PopFont();
			ImGui::PopStyleVar();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 30.f);
		ImGui::SetCursorPos(ImVec2(560, 10));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.31f, 0.31f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.f, 0.f, 0.f, 1.f));

		if (ImGui::Button("##Close", ImVec2(20, 20)))
		{
			exit(0);
		}
		ImGui::PopStyleColor(3);
		ImGui::SetCursorPos(ImVec2(530, 10));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 1.f, 1.f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.514f, 0.494f, 0.494f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.514f, 0.494f, 0.494f, 1.f));

		if (ImGui::Button("##Collapse", ImVec2(20, 20)))
		{
			exit(0);
		}
		ImGui::PopStyleColor(3);
		ImGui::PopStyleVar();
	}
	ImGui::End();
}

void gui::init(LPDIRECT3DDEVICE9 device)
{
	ImGui::StyleColorsDark();
	//не работает :( ImGui::GetStyle().WindowRounding = 20.f;

	if (settings::window_position.x == 0) {
		RECT screen_rect{};
		GetWindowRect(GetDesktopWindow(), &screen_rect);
		settings::screen_res = ImVec2(float(screen_rect.right), float(screen_rect.bottom));
		settings::window_position = (settings::screen_res - settings::window_size) * 0.5f;
	}
}

void gui::imageinizilizate()
{
	bool ret = gui::LoadTextureFromFile("C:\\Users\\ouki\\Desktop\\csgoico.png", &my_texture, &my_image_width, &my_image_height);
	IM_ASSERT(ret);
}

void gui::fontinizilizate()
{
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();
	CSFont = io.Fonts->AddFontFromFileTTF("C:\\Users\\ouki\\Desktop\\Poppins-Bold.ttf", 26.0f);
	SelectFont = io.Fonts->AddFontFromFileTTF("C:\\Users\\ouki\\Desktop\\Poppins-Bold.ttf", 20.0f);
	BackFont = io.Fonts->AddFontFromFileTTF("C:\\Users\\ouki\\Desktop\\Poppins-Bold.ttf", 16.0f);
}