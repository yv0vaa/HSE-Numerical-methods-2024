make exp:
	g++ -std=c++20 L2_approx.cpp analytical.cpp numerical.cpp -o exp
make run:
	./test 100
make test:
	g++-12 -std=c++20 analytical.cpp numerical.cpp L2_approx.cpp test.cpp -o test -lgsl -lgslcblas -lm