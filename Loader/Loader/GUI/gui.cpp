#include "gui.hpp"

int my_image_width = 0;
int my_image_height = 0;
PDIRECT3DTEXTURE9 my_texture = NULL;

DWORD pid;
Injector inj;

ImFont* verdana;

bool Release = false;
bool Alpha = true;
 
void gui::gui_element()
{
	if (!VISIBLE)
		return;

	inj.hwndproc = FindWindowA(0, "Counter-Strike: Global Offensive - Direct3D 9");
	GetWindowThreadProcessId(inj.hwndproc, &pid);
	inj.process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	inj.clientDLL = inj.GetModule(pid, "client.dll");

	ImGui::SetNextWindowPos(ImVec2(settings::window_position.x, settings::window_position.y), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(settings::window_size.x, settings::window_size.y));
	ImGui::SetNextWindowBgAlpha(1.0f);

	ImGui::Begin(settings::title, &settings::visible, settings::window_flags);
	{
		// 400, 250
		settings::window_position = ImGui::GetWindowPos();
		ImDrawList* drawListR = ImGui::GetWindowDrawList();

		drawListR->AddRectFilled(ImVec2(settings::window_position.x + 5, settings::window_position.y + 5), ImVec2(settings::window_position.x + 145, settings::window_position.y + 245), IM_COL32(70, 70, 70, 255));

		ImGui::PushFont(verdana);
		
		{
			drawListR->AddRectFilled(ImVec2(settings::window_position.x + 170, settings::window_position.y + 25), ImVec2(settings::window_position.x + 390, settings::window_position.y + 75), IM_COL32(70, 70, 70, 255));
			ImGui::SetCursorPos(ImVec2(180, 30));
			ImGui::Image(my_texture, ImVec2(40, 40));

			ImGui::SetCursorPos(ImVec2(230, 42));
			ImGui::Text("CS:GO Release");

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(49.f / 255, 49.f / 255, 49.f / 255, 1.f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(49.f / 255, 49.f / 255, 49.f / 255, 1.f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(49.f / 255, 49.f / 255, 49.f / 255, 1.f));

			ImGui::SetCursorPos(ImVec2(330, 38));
			if (ImGui::Button("Select##1", ImVec2(50, 25))) {

			}
		}

		{
			drawListR->AddRectFilled(ImVec2(settings::window_position.x + 170, settings::window_position.y + 85), ImVec2(settings::window_position.x + 390, settings::window_position.y + 135), IM_COL32(70, 70, 70, 255));
			ImGui::SetCursorPos(ImVec2(180, 90));
			ImGui::Image(my_texture, ImVec2(40, 40));

			ImGui::SetCursorPos(ImVec2(230, 102));
			ImGui::Text("CS:GO Alpha");

			ImGui::SetCursorPos(ImVec2(330, 98));
			if (ImGui::Button("Select##2", ImVec2(50, 25))) {

			}

			ImGui::PopStyleColor(3);
		}

		{
			drawListR->AddRectFilled(ImVec2(settings::window_position.x + 170, settings::window_position.y + 145), ImVec2(settings::window_position.x + 390, settings::window_position.y + 195), IM_COL32(70, 70, 70, 255));
			ImGui::SetCursorPos(ImVec2(180, 152));
			ImGui::Text(std::string("Username: ").append(gui::username).c_str());
			ImGui::SetCursorPosX(180);
			ImGui::Text("Heaven with love <3!");
		}
		
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 33.f);
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.31f, 0.31f, 1.f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.f, 0.f, 0.f, 1.f));
			ImGui::SetCursorPos(ImVec2(377, 5));
			if (ImGui::Button("##Exit", ImVec2(12, 12))) {
				VISIBLE = false;
			}
			ImGui::PopStyleColor(3);
			ImGui::PopStyleVar();
		}

		ImGui::SetCursorPos(ImVec2(170, 205));
		if (pid > 0)
		{
			if (ImGui::Button("Inject", ImVec2(220, 40)))
			{
				LPVOID ntOpenFile = GetProcAddress(LoadLibraryW(L"ntdll"), "NtOpenFile");
				if (ntOpenFile) {
					char originalBytes[5];
					memcpy(originalBytes, ntOpenFile, 5);
					WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 5, NULL);
				}
				inj.inject(pid, "C:\\Heaven\\Oreo.dll");
			}
		}
		else
		{
			if (ImGui::Button("Run CS:GO", ImVec2(220, 40)))
			{
				ShellExecuteA(NULL, "open", "steam://rungameid/730", NULL, NULL, SW_SHOWNORMAL);
			}
		}
		ImGui::PopFont();
	}
	ImGui::End();
}

void gui::init(LPDIRECT3DDEVICE9 device)
{
	ImGui::StyleColorsDark();

	if (settings::window_position.x == 0) {
		RECT screen_rect{};
		GetWindowRect(GetDesktopWindow(), &screen_rect);
		settings::screen_res = ImVec2(float(screen_rect.right), float(screen_rect.bottom));
		settings::window_position = (settings::screen_res - settings::window_size) * 0.5f;
	}

	URLDownloadToFile(NULL, "https://github.com/OukiLove/oukilove.github.io/raw/main/assets/loader/Oreo.dll", "C:\\Heaven\\Loader\\Oreo.dll", 0, NULL);

	DWORD username_len = UNLEN + 1;
	GetUserName(gui::username, &username_len);
}

void gui::imageinizilizate()
{
	URLDownloadToFile(NULL, "https://hvnproject.github.io/assets/img/csgoico.png", "C:\\Heaven\\Loader\\csgoico.png", 0, NULL);
	bool ret = gui::LoadTextureFromFile("C:\\Heaven\\Loader\\csgoico.png", &my_texture, &my_image_width, &my_image_height);
	IM_ASSERT(ret);
}

void gui::fontinizilizate()
{
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();

	verdana = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 14.f);
}