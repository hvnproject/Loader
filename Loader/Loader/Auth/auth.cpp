#include "auth.hpp"

std::string hwid[5] = {
	"{3a164f40-27c3-11ed-bec6-806e6f6e6963}", // Lamborghini#0660
	"{2ebf4d0a-1369-11ed-b50d-806e6f6e6963}", // .1#7161
	"{71d5df84-2096-11ed-b8e8-806e6f6e6963}", // Ouki76
	"{33619c15-691d-11ea-b2b0-806e6f6e6963}", // 978M02V34987M#1553
	"{8e076033-0397-11ed-a54b-806e6f6e6963}"
};

std::string auth::getHWID() {
	HW_PROFILE_INFOW pi;
	GetCurrentHwProfileW(&pi);

	auto data = std::string(pi.szHwProfileGuid, pi.szHwProfileGuid + 38);

	return data;
}

bool auth::GetAuth(std::string nowHWID)
{
	for (int i = 0; i < 5; i++)
	{
		if (nowHWID == hwid[i])
			return true;
	}
	return false;
}