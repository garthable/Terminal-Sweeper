#include "util.h"

int main()
{
    std::string va = "";
    std::vector<std::vector<int>> indexes = {
        {0},
        {0, 1},
        {0, 1, 2},
        {0, 1, 2, 3},
        {0, 1, 2, 3, 4},
        {0, 1, 2, 3, 4, 5},
        {0, 1, 2, 3, 4, 5, 6},
        {0, 1, 2, 3, 4, 5, 6, 7}
        };
    std::vector<std::vector<int>> results;

    for (std::vector<int> v : indexes)
    for (int i = 1; i <= v.size(); i++)
    {
        results.clear();
        combination(v, i, results);

        va += "case " + std::to_string((i-1)+(v.size()-1)*8) + ":" + '\n';
        va += (char)9;
        va += "subsets = {";

        for (int j = 0; j < results.size(); j++)
        {
            std::vector<int> a = results[j];
            va += "{";
            for (int k = 0; k < a.size(); k++)
            {
                int b = a[k];
                va += "arr[";
                va += '0' + b;
                va += "]";
                if (k != a.size() - 1)
                    va += ", ";
            }
            va += "}";
            if (j != results.size() - 1)
                va += ", ";
        }
        va += "};";
        va += '\n';
        va += "break;";
        va += '\n';
        va += '\n';
    }

    std::cout << va << std::endl;
}