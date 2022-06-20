all: prevs search.o search.a main
prevs:
	mkdir -v -p build
search.o:
	g++ -std=c++20 -o3 -c search.cpp -o build/search.o
search.a:
	ar rvs build/search.a build/search.o
	rm build/search.o
main:
	g++ -std=c++20 -o3 main.cpp build/search.a -o main
clean:
	rm -r build
	rm -r main

