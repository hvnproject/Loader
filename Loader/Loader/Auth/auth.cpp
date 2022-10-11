#include "auth.hpp"

std::string hwid[5] = {
	"",
	"",
	"",
	"",
	""
};

std::string auth::getHWID() {
	HW_PROFILE_INFOW pi;
	GetCurrentHwProfileW(&pi);

	auto data = std::string(pi.szHwProfileGuid, pi.szHwProfileGuid + 38);

	return data;
}

bool auth::GetAuth(std::string nowHWID)
{
	for (int i = 0; i < hwid->length(); i++)
	{
		if (nowHWID == hwid[i])
			return true;
	}
	return false;
}