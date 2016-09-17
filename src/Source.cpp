#include <iostream>

#include "./dic/DIC.h"

using namespace std;

int main(int argc, char *argv[])
{
	auto parser = DICParameters(argc, argv);
	auto parameters = parser.GetParameters();
	auto executor = Executor(&parameters);
	executor.FindResult();

	return EXIT_SUCCESS;
}
