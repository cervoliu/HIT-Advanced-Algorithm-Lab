gen : gen.cpp
	g++ gen.cpp -o gen -Ofast
bloomFilter : main.cpp naive.cpp
	g++ main.cpp naive.cpp -o bloomFilter -Ofast

.PHONY:
clean :
	@rm -f *.out
	@rm -f gen
	@rm -f bloomFilter