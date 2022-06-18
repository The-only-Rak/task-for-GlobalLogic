all: prevs search.o search.a main
prevs:
	mkdir -v -p build
search.o:
	g++ -std=c++20 -c search.cpp -o build/search.o
search.a:
	ar rvs build/search.a build/search.o
	rm build/search.o
main:
	g++ -std=c++20 main.cpp build/search.a -o main
clean:
	rmdir -r build

