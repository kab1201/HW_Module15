#include "Chat.h"

void Chat::reg(const string& login, char pass[], int pass_length) {
	// Ваш код
	uint* sh1 = sha1(pass, pass_length);
	authData_.add(login, sh1);
}
bool Chat::login(const string& login, char pass[], int pass_length) {
	uint* res = authData_.find(login);
	if (res != nullptr) {
		uint* sh1 = sha1(pass, pass_length);
		if (*res == *sh1)
			return true;
	}
	return false;
}