game: main.cpp
	clang++ -std=c++17 -Wall -Wextra $(shell pkg-config --libs raylib) main.cpp -o game $(shell pkg-config --cflags --libs raylib)

clean:
	rm -f game