#include <Windows.h>
#include <string>
#include <iostream>
#include <Wininet.h>
#include <string>
#include "update.hpp"
#include <random>
#pragma comment(lib, "wininet.lib")

std::string replaceAll(std::string subject, const std::string& search,
	const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

std::string DownloadString(std::string URL) {
	HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HINTERNET urlFile;
	std::string rtn;
	if (interwebs) {
		urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
		if (urlFile) {
			char buffer[2000];
			DWORD bytesRead;
			do {
				InternetReadFile(urlFile, buffer, 2000, &bytesRead);
				rtn.append(buffer, bytesRead);
				memset(buffer, 0, 2000);
			} while (bytesRead);
			InternetCloseHandle(interwebs);
			InternetCloseHandle(urlFile);
			std::string p = replaceAll(rtn, "|n", "\r\n");
			return p;
		}
	}
	InternetCloseHandle(interwebs);
	std::string p = replaceAll(rtn, "|n", "\r\n");
	return p;
}

BOOL SelfDelete()
{
	TCHAR szFile[MAX_PATH], szCmd[MAX_PATH];

	if ((GetModuleFileName(0, szFile, MAX_PATH) != 0) &&
		(GetShortPathName(szFile, szFile, MAX_PATH) != 0))
	{
		lstrcpy(szCmd, "/c del ");
		lstrcat(szCmd, szFile);
		lstrcat(szCmd, " >> NUL");

		if ((GetEnvironmentVariable("ComSpec", szFile, MAX_PATH) != 0) &&
			((INT)ShellExecute(0, 0, szFile, szCmd, 0, SW_HIDE) > 32))
			return TRUE;
	}

	return FALSE;
}

std::string RandomizeStr()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> distr(0, 51);
	std::string name = "";
	char alphabet[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	for (int i = 0; i < 15; ++i)
	{
		name = name + alphabet[distr(mt)];
	}
	return name.append(".exe");
}

void update::InitUpdate() {
	std::string str = DownloadString("https://hvnproject.github.io/assets/loader/version.txt");

	std::string version = "0.0.2";

	if (str != version) {
		URLDownloadToFileA(NULL, "https://hvnproject.github.io/assets/loader/Loader.exe", RandomizeStr().c_str(), 0, NULL);
		Sleep(3000);
		MessageBox(0, "Relaunch me", "Loader updated", MB_OK);
		SelfDelete();
		exit(0);
	}
}