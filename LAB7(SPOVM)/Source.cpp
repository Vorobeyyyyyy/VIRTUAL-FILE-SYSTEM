#include <iostream>
#include <conio.h>
#include "VirtualFS.h"
using namespace std;

string editString(string);

int main()
{
	//VirtualFS::createVirtualFs("virtualFs.fs");
	VirtualFS fs("virtualFs.fs");
	//fs.createDir("New folder");


	unsigned short currrentChoice = 0;
	unsigned short maxChoice = 0;
	while (true)
	{
		vector<string> dirNames = fs.getCurrentDirNames();
		vector<string> fileNames = fs.getCurrentFileNames();
		maxChoice = dirNames.size() + fileNames.size() - 1;

		cout << "N - create dir | F - create file | D - delete | R - rename | E - exit\n";
		cout << "Total memory usage: " << fs.getUsedMemory() * BLOCK_SIZE << " (" << fs.getUsedMemory() << " blocks)\n\n";

		for (auto it : fs.getCurrentPath())
			cout << it << '/';
		cout << '\n';

		for (unsigned short i = 0; i < dirNames.size(); i++)
			cout << (i == currrentChoice ? " > " : "   ") << dirNames[i] << '/' << (i == currrentChoice ? " < " : "   ") << '\n';

		for (unsigned short i = 0; i < fileNames.size(); i++)
			cout << (i + dirNames.size() == currrentChoice ? " > " : "   ") << fileNames[i] << (i + dirNames.size() == currrentChoice ? " < " : "   ") << '\n';

		switch (_getch())
		{
		case 0:case 224:
		{
			switch (_getch())
			{
			case 72:
				if (currrentChoice)
					currrentChoice--;
				break;
			case 80:
				if (currrentChoice < maxChoice)
					currrentChoice++;
				break;
			}
			break;
		}
		case 'n':
		{
			system("cls");
			cout << "Enter name for new folder: ";
			string name;
			cin >> name;
			fs.createDir(name);
			break;
		}
		case 'f':
		{
			system("cls");
			cout << "Enter name for new file: ";
			string name;
			cin >> name;
			fs.createFile(name);
			break;
		}
		case 'd':
		{
			if (currrentChoice < dirNames.size())
				fs.deleteDir(dirNames[currrentChoice]);
			else
				fs.deleteFile(fileNames[currrentChoice - dirNames.size()]);
			currrentChoice = 0;
			break;
		}
		case 'r':
		{
			system("cls");
			cout << "Enter new name: ";
			string newName;
			cin >> newName;
			if (currrentChoice < dirNames.size())
				fs.renameDir(dirNames[currrentChoice], newName);
			else
				fs.renameFile(fileNames[currrentChoice - dirNames.size()], newName);
			break;
		}
		case 'e':
		{
			return 0;
		}
		case 13:
		{
			if (currrentChoice < dirNames.size())
			{
				fs.enterDir(dirNames[currrentChoice]);
				currrentChoice = 0;
			}
			else
				fs.editFile(fileNames[currrentChoice - dirNames.size()], editString(fs.readFile(fileNames[currrentChoice - dirNames.size()] )));
			break;
		}
		}
		system("cls");
	}
	return 0;
}



string editString(string str)
{
	unsigned long pos = 0;
	bool end = false;
	while (!end)
	{
		system("cls");
		cout << "Size: " << str.size() << " Pos: " << pos <<'\n';
		cout << str.substr(0, pos) << '|' << str.substr(pos) << '\n';
		unsigned char c = _getch();
		switch (c)
		{
		case 0:case 224:
		{
			switch (_getch())
			{
			case 77:
			{
				if (pos < str.size())
					pos++;
				break;
			}
			case 75:
			{
				if (pos > 0)
					pos--;
				break;
			}
			}
			break;
		}
		case 13:
		{
			system("cls");
			return str;
			break;
		}
		case '\b':
		{
			if (pos)
				str.erase(--pos, 1);
			break;
		}
		default:
		{
			str.insert(pos++, 1, c);
		}
		}
	}
}