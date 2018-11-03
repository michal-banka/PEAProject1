#include "Libs.h"
#include "Matrix.h"
#include "Menu.h"

int main()
{
	srand(time(nullptr));

	menu().mainMenu();
	
	std::cin.get();
	return 0;
}
