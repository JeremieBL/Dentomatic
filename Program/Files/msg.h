#pragma once

#include <string>
#include <iostream>

using namespace std;

class msg
{
public:
	string m_content;

	msg(string);
	msg();
	~msg();
public:
	void changeTo(string);
};