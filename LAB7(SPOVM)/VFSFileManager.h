#pragma once
#include <iostream>
#include <conio.h>
#include "VirtualFS.h"
using namespace std;

class VFSFileManager
{
private:
	unsigned short currrentChoice = 0;
	unsigned short maxChoice = 0;
	VirtualFS fs;
public:
	VFSFileManager(VirtualFS*);

	void menu();
};