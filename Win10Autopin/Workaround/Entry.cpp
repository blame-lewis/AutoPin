#include "stdafx.h";
#include "InvokeShellVerb.h";
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include <locale>
#include <codecvt>
int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 3)
	{
		std::cout << "Autopin - pins a group of shortcuts to the taskbar." << std::endl;
		std::cout << "(Now with Windows 10 support!)" << std::endl;
		std::cout << "Usage: autopin.exe pinfile.txt unpinfile.txt" << std::endl;
		std::cout << "Usage: autopin.exe unpin program.lnk" << std::endl;
		std::cout << "Usage: autopin.exe pin program.lnk" << std::endl << std::endl;
		std::cout << "pinfile.txt must contain a list of .lnk files to pin to the taskbar." << std::endl;
		std::cout << "unpinfile.txt must contain a list of .lnk files to unpin from the taskbar." << std::endl;

		return 0;
	}
	std::wstring pinPath = argv[1];
	std::wstring unpinPath = argv[2];
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	if (pinPath == L"pin")
	{
		std::string z = converter.to_bytes(unpinPath);
		std::string path = z.substr(0, z.find_last_of("\\"));
		std::string exe = z.substr(z.find_last_of("\\") + 1, z.length() - z.find_last_of("\\") - 1);
		DWORD abc[] = { 5386 };
		MyInvokeShellVerb(converter.from_bytes(path).c_str(), converter.from_bytes(exe).c_str(), abc, true);
		return 0;
	}
	if (pinPath == L"unpin")
	{
		std::string z = converter.to_bytes(unpinPath);
		std::string path = z.substr(0, z.find_last_of("\\"));
		std::string exe = z.substr(z.find_last_of("\\") + 1, z.length() - z.find_last_of("\\") - 1);
		DWORD abc[] = { 5387 };
		MyInvokeShellVerb(converter.from_bytes(path).c_str(), converter.from_bytes(exe).c_str(), abc, true);

		return 0;
	}





	//std::wstring pinPath = L"Pin.txt";
	//std::wstring unpinPath = L"Unpin.txt";
	std::wifstream pinStream(pinPath);
	std::wifstream unpinStream(unpinPath);

	std::vector<std::wstring> pinList;
	std::vector<std::wstring> unpinList;

	if (!pinStream.is_open())
	{
		std::cout << "Error - could not open pin file " << pinPath.c_str() << std::endl;

		return 0;
	}
	if (!unpinStream.is_open())
	{
		std::cout << "Error - could not open unpin file " << unpinPath.c_str() << std::endl;

		return 0;
	}

	while (!pinStream.eof())
	{
		std::wstring line =L"";
		std::getline(pinStream, line);

		pinList.push_back(line);
	}

	while (!unpinStream.eof())
	{
		std::wstring line =L"";
		std::getline(unpinStream, line);

		unpinList.push_back(line);
	}
	for (std::vector<std::wstring>::iterator i = pinList.begin(); i != pinList.end(); ++i)
	{
		std::string z = converter.to_bytes(*i);
		std::string path = z.substr(0, z.find_last_of("\\"));
		std::string exe = z.substr(z.find_last_of("\\") + 1, z.length() - z.find_last_of("\\") - 1);

		DWORD abc[] = { 5386 };
		MyInvokeShellVerb(converter.from_bytes(path).c_str(), converter.from_bytes(exe).c_str(), abc, true);
	}
	for (std::vector<std::wstring>::iterator i = unpinList.begin(); i != unpinList.end(); ++i)
	{
		std::string z = converter.to_bytes(*i);
		std::string path = z.substr(0, z.find_last_of("\\"));
		std::string exe = z.substr(z.find_last_of("\\")+1, z.length() - z.find_last_of("\\") -1);
		DWORD abc[] = { 5387 };
		MyInvokeShellVerb(converter.from_bytes(path).c_str(), converter.from_bytes(exe).c_str(), abc, true);
	}

	pinStream.close();
	unpinStream.close();

	return 0;
}
