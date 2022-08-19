#include "..\settings.hpp"
#include "..\Injector\memory.hpp"

#pragma comment(lib, "urlmon.lib")

namespace gui
{
	void gui_element();
	void init(LPDIRECT3DDEVICE9 device);
	void imageinizilizate();
	void fontinizilizate();
	bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height);

	inline static char key[24] = { 0 };
}