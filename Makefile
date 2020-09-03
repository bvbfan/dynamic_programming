
all:
	g++ -std=c++14 -Wall -Wextra -O3 subset_sum.cpp -o subset_sum
	g++ -std=c++14 -Wall -Wextra -O3 bitwise_add.cpp -o bitwise_add

clean:
	rm -f ./subset_sum ./bitwise_add
