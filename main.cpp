#include<iostream>
#include<time.h>
#include<string>
#include<stdlib.h>
#include "Helper.h"

#include <iostream>
using std::cout;

class Test {
public:
	int x;
	mutable int y;
	Test() { x = 4; y = 10; }
};
/*int main()
{
	const Test t1;
	t1.y = 8;
	cout << t1.x;
	return 0;
}*/

int main() {

	std::cout << "Start with TicTacToe" << std::endl;
	Helper helper;
	helper.menu();
	return 0;
}