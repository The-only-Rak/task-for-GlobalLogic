#include "search.hpp"
#include <chrono>
int main(int argc, char* argv[])
{
    if(argc > 1)
    {
        task::Finder f(argv[1]);
        f.GetPath();
        ///also can use the second method 
        //find(argv[1])
    }
}
