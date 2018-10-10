#include "Libs.h"
#include "MatrixRepresentation.h"

int main()
{
	matrix graph("data.txt");
	graph.show();

	std::cout << "IS SYMETRIC? : " << graph.isSymetric();
	std::cin.get();
	return 0;
}
