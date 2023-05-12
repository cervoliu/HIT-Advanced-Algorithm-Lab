main : main.cpp
	g++ main.cpp -o main -O2
test : main
	for n in 16 32 64 128 256 512 1024; do \
        ./main -n $$n $(shell date "+%Y%m%d%H%M%S"); \
    done
