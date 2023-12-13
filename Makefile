.DEFAULT_GOAL := standard

standard:
	g++ main.cpp mineMap.cpp solver.cpp probabilityFinder.cpp app.cpp -std=c++17 -O3

debugMac:
	lldb ./a.out