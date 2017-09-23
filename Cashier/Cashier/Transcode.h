#pragma once
#include <windows.h> 

class Transcode
{
public:
	Transcode();
	~Transcode();

public:
	char* U2G(const char* utf8);
	char* G2U(const char* gb2312);
};