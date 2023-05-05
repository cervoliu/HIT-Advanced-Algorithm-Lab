gen : gen.cpp
	g++ gen.cpp -o gen -Ofast
input : gen
	./gen $(shell date "+%Y%m%d%H%M%S")
bloomFilter : main.cpp naive.cpp
	g++ main.cpp -o bloomFilter -Ofast
checker : checker.cpp
	g++ checker.cpp -o checker -Ofast
check : checker
	./checker

.PHONY:
clean :
	@rm -f *.out bloomFilter.in
	@rm -f gen bloomFilter checker