#include "util.h"
#include <iostream>

int main()
{
    std::vector<int> input = {1, 2, 3, 4, 5, 6, 7};
    std::vector<std::vector<int>> output;

    combination(input, 3, output);

    for (std::vector<int> v : output)
    {
        for (int x : v)
            std::cout << x << " ";
        
        std::cout << std::endl;
    }

    print(output.size());
}