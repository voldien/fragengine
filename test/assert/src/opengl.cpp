#include<gtest/gtest.h>
#include <FragView.h>

TEST (OpenGL, FragmentShader) {
	const char* arg[] = {
			"--debug",
			"-f", "./samples/glsl/wave.frag"

	};
	const int nArg = sizeof(arg) / sizeof(arg[0]);

	try {
		FragView(nArg, arg).run();
	} catch (std::exception &ex) {
		std::cerr << ex.what() << std::endl;

	}
}

TEST (OpenGL, ComputeShader) {
	const char* arg[] = {
			"--debug",
			"-H", "./samples/glsl/compute.comp"
	};
	const int nArg = sizeof(arg) / sizeof(arg[0]);

	try {
		FragView(nArg, arg).run();
	} catch (std::exception &ex) {
		std::cerr << ex.what() << std::endl;

	}
}