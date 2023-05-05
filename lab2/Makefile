sorter : main.cpp sort.cpp
	g++ main.cpp sort.cpp -o sorter -Ofast
gen : gen.cpp
	g++ gen.cpp -o gen -Ofast

input := $(wildcard ./input/*.in)
output := $(wildcard ./output/*.out)

input : gen
	./gen $(shell date "+%Y%m%d%H%M%S")

test1 : input sorter
	@rm -f ./output/runtime_1.out
	for rate in 0 1 2 3 4 5 6 7 8 9 10; do \
        ./sorter -M 1 -R $$rate $(shell date "+%Y%m%d%H%M%S"); \
		echo $$rate done; \
    done
test2 : input sorter
	@rm -f ./output/runtime_2.out
	for rate in 0 1 2 3 4 5 6 7 8 9 10; do \
        ./sorter -M 2 -R $$rate $(shell date "+%Y%m%d%H%M%S"); \
		echo $$rate done; \
    done
test3 : input sorter
	@rm -f ./output/runtime_3.out
	for rate in 0 1 2 3 4 5 6 7 8 9 10; do \
        ./sorter -M 3 -R $$rate $(shell date "+%Y%m%d%H%M%S"); \
		echo $$rate done; \
    done

.PHONY:
clean : 
	@rm -f $(input)
	@rm -f $(output)
	@rm -f gen
	@rm -f sorter