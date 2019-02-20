#include"FragView.h"
#include <cstdlib>
#include <iostream>

int main(int argc, const char **argv) {
	try {
		FragView(argc, argv).run();
	} catch (std::exception &ex) {
		std::cerr << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
