#include <string>
#include <Windows.h>

namespace auth
{
	std::string getHWID();
	bool GetAuth(std::string nowHWID);
}