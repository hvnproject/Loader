#include "gui.hpp"

int csgo_image_width = 0;
int csgo_image_height = 0;
PDIRECT3DTEXTURE9 csgo_texture = NULL;

int heaven_image_width = 0;
int heaven_image_height = 0;
PDIRECT3DTEXTURE9 heaven_texture = NULL;

DWORD pid;
Injector inj;

ImFont* verdana;

bool Release = true;
bool Alpha = false;

std::string nowHwid = auth::getHWID();

bool Auth = auth::GetAuth(nowHwid);

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

		ImGui::PushFont(verdana);

		{
			ImGui::SetCursorPos(ImVec2(-5, -5));
			ImGui::Image(heaven_texture, ImVec2(50, 50));

			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 33.f);
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.31f, 0.31f, 1.f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.f, 0.f, 0.f, 1.f));
			ImGui::SetCursorPos(ImVec2(377, 10));
			if (ImGui::Button("##Exit", ImVec2(12, 12))) {
				VISIBLE = false;
			}
			ImGui::PopStyleColor(3);
			ImGui::PopStyleVar();
		}

		{
			drawListR->AddRectFilled(ImVec2(settings::window_position.x + 5, settings::window_position.y + 35), ImVec2(settings::window_position.x + 190, settings::window_position.y + 245), IM_COL32(70, 70, 70, 255), 4.f);
			drawListR->AddRectFilled(ImVec2(settings::window_position.x + 210, settings::window_position.y + 35), ImVec2(settings::window_position.x + 395, settings::window_position.y + 245), IM_COL32(70, 70, 70, 255), 4.f);
		}

		{
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.f);
			ImGui::SetCursorPos(ImVec2(10, 45));
			if (ImGui::Button("##CS:GO Release", ImVec2(175, 30))) {
				Release = true;

				if (Alpha == true) {
					Alpha = false;
				}
			}
			if (Auth) {
				ImGui::SetCursorPos(ImVec2(10, 85));
				if (ImGui::Button("##CS:GO Alpha", ImVec2(175, 30))) {
					Alpha = true;

					if (Release == true) {
						Release = false;
					}
				}
			}
			ImGui::PopStyleVar();

			ImGui::SetCursorPos(ImVec2(20, 50));
			ImGui::Image(csgo_texture, ImVec2(20, 20));
			ImGui::SetCursorPos(ImVec2(50, 50));
			ImGui::Text("CS:GO Release");

			if (Auth) {
				ImGui::SetCursorPos(ImVec2(20, 90));
				ImGui::Image(csgo_texture, ImVec2(20, 20));
				ImGui::SetCursorPos(ImVec2(50, 90));
				ImGui::Text("CS:GO Alpha");
			}
		}

		{
			std::string selected_version;
			if (Alpha == true) {
				selected_version = "Alpha";
			}
			else if (Release == true) {
				selected_version = "Release";
			}
			ImGui::SetCursorPos(ImVec2(215, 40));
			ImGui::Text(std::string("Username: ").append(gui::username).c_str());
			ImGui::SetCursorPosX(215);
			ImGui::Text(std::string("Selected version: ").append(selected_version).c_str());
			ImGui::SetCursorPosX(215);
			ImGui::Text("Heaven with love <3!");
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.f);
			ImGui::SetCursorPos(ImVec2(243, 200));
			if (pid > 0) {
				if (Alpha) {
					if (ImGui::Button("Inject", ImVec2(120, 25))) {
						inj.inject(pid, "C:\\Heaven\\Loader\\csgo.dll");
					}
				}
				else if (Release) {
					if (ImGui::Button("Inject", ImVec2(120, 25))) {
					}
				}
			}
			else {
				if (ImGui::Button("Run CS:GO", ImVec2(120, 25))) {
					ShellExecuteA(NULL, "open", "steam://rungameid/730", NULL, NULL, SW_SHOWNORMAL);
				}
			}
			ImGui::PopStyleVar();
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

	URLDownloadToFile(NULL, "https://github.com/hvnproject/hvnproject.github.io/raw/main/assets/loader/csgo.dll", "C:\\Heaven\\Loader\\csgo.dll", 0, NULL);

	DWORD username_len = UNLEN + 1;
	GetUserName(gui::username, &username_len);
}

void gui::imageinizilizate()
{
	URLDownloadToFile(NULL, "https://hvnproject.github.io/assets/img/csgoico.png", "C:\\Heaven\\Loader\\csgoico.png", 0, NULL);
	bool ret = gui::LoadTextureFromFile("C:\\Heaven\\Loader\\csgoico.png", &csgo_texture, &csgo_image_width, &csgo_image_height);
	IM_ASSERT(ret);

	URLDownloadToFile(NULL, "https://hvnproject.github.io/assets/img/heaven.png", "C:\\Heaven\\Loader\\heaven.png", 0, NULL);
	bool ret2 = gui::LoadTextureFromFile("C:\\Heaven\\Loader\\heaven.png", &heaven_texture, &heaven_image_width, &heaven_image_height);
	IM_ASSERT(ret2);
}

void gui::fontinizilizate()
{
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();

	verdana = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 16.f);
}