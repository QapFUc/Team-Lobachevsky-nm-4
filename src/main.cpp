#include <cstddef>
#include <iostream>
#include "nm/utils/profiler.hpp"
#include "nm/utils/logger.hpp"

double testKernel(const double& a, nm::Timer& t, nm::Profiler& prof) {
	nm::Timer f{ nm::Timer::scopeTimer(&t)};
	nm::Profiler p{ prof.nest(nm::GET_CURRENT_SCOPE())};
	volatile double res = 0.l;
	std::cout << "kernel calc" << '\n';

	for (size_t i = 0; i < 1; i++) {
		for(size_t j = 0; j < 100; j++) {
			for(size_t k = 0; k < 100; k++) {
				res += a*a*0.5 + a;
			}
		}
	}

	return res;
}

int main(int argc, char* argv[]) {
	nm::Profiler prof;
	nm::Timer t;

	std::cout << "got prof" << '\n';
	double res = testKernel(1.05l, t, prof);
	std::cout << "kernel passed" << '\n';
	auto profdata = prof.getAllData();
	std::cout << "Profiling data" << '\n';
	for (auto& d : profdata) {
		std::cout << d;
	}

	std::cout << t.getClocks() << '\n';
	std::cout << t.getDuration() << '\n';
	return 0;
}
