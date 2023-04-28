#pragma once

#include "HashTable.h"

class Chat {
public:
	void reg(const string& login, char pass[], int pass_length);
	bool login(const string& login, char pass[], int pass_length);

private:
	HashTable authData_;
};