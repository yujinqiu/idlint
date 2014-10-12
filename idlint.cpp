#include <iostream>
#include <string>
#include "IDCard.h"

using namespace std;

int main(int argc, char *argv[])
{
	string id(argv[1]);
	int gender;
	int ret = IDCard::verify(id, gender);
	cout << ret << " " << gender << endl;
	return 0;
}
