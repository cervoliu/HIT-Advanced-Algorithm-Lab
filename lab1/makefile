a : main.o naive.o minhash.o lsh.o mix.o
	g++ main.o naive.o minhash.o lsh.o mix.o -o a -Ofast

main.o : main.cpp
	g++ main.cpp -c -o main.o

naive.o : naive.cpp
	g++ naive.cpp -c -o naive.o

minhash.o : minhash.cpp
	g++ minhash.cpp -c -o minhash.o

lsh.o : lsh.cpp
	g++ lsh.cpp -c -o lsh.o

mix.o : mix.cpp
	g++ mix.cpp -c -o mix.o


.PHONY: clean
clean:
	@rm -f *.o
	@rm -f a
	@rm -f ./data/*.ans
