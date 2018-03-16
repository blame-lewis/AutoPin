// Autopin.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc != 3)
	{
		std::cout << "Autopin - pins a group of shortcuts to the taskbar." << std::endl;
		std::cout << "Usage: autopin.exe pinfile.txt unpinfile.txt" << std::endl << std::endl;
		std::cout << "pinfile.txt must contain a list of .lnk files to pin to the taskbar." << std::endl;
		std::cout << "unpinfile.txt must contain a list of .lnk files to unpin from the taskbar." << std::endl;

		return 0;
	}
	std::wstring pinPath = argv[1];
	std::wstring unpinPath = argv[2];

	std::wifstream pinStream(pinPath);
	std::wifstream unpinStream(unpinPath);

	std::vector<std::wstring> pinList;
	std::vector<std::wstring> unpinList;

	if(!pinStream.is_open())
	{
		std::wcout << "Error - could not open pin file " << pinPath.c_str() << std::endl;

		return 0;
	}
	if(!unpinStream.is_open())
	{
		std::wcout << "Error - could not open unpin file " << unpinPath.c_str() << std::endl;

		return 0;
	}

	while(!pinStream.eof())
	{
		std::wstring line = L"";
		std::getline(pinStream, line);

		pinList.push_back(line);
	}
	
	while(!unpinStream.eof())
	{
		std::wstring line = L"";
		std::getline(unpinStream, line);

		unpinList.push_back(line);
	}
	for(std::vector<std::wstring>::iterator i = pinList.begin(); i != pinList.end(); ++i)
	{
			ShellExecute(NULL, L"taskbarpin", (*i).c_str(), NULL, NULL, 0);
	}
	for(std::vector<std::wstring>::iterator i = unpinList.begin(); i != unpinList.end(); ++i)
	{
			ShellExecute(NULL, L"taskbarunpin", (*i).c_str(), NULL, NULL, 0);
	}

	pinStream.close();
	unpinStream.close();

	return 0;
}

