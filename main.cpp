#include "search.hpp"

int main(int argc, char* argv[])
{
    if(argc > 1)
    {
    task::Finder f(argv[1]);
    f.GetPath();
    }
}