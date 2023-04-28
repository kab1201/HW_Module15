#include "Chat.h"
#include <iostream>
using namespace std;

int main()
{
	Chat *myChat = new Chat();

	string userLogin = "Alla";
	char userPasswordReg[] = "test";
	int pswLenReg = strlen(userPasswordReg);
	char userPasswordLog[] = "test";
	int pswLenLog = strlen(userPasswordLog);

	myChat->reg(userLogin, userPasswordReg, pswLenReg);
	bool res = myChat->login(userLogin, userPasswordReg, pswLenLog);
	if (!res)
		cout << "The login is wrong!" << endl;
	else
		cout << "Hello, " << userLogin << "!" << endl;

	return 0;
}