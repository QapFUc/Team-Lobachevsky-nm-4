#include <cstddef>
#include <iostream>
#include "nm/utils/profiler.hpp"
#include "nm/utils/logger.hpp"
#include "core/netProcess.hpp"

int main(int argc, char* argv[]) {
	NPTestFunc(argv[1]);
	return 0;
}
