#include <iostream>
#include <string>

int* get_next(std::string pattern);

int KMP_algorithm(std::string pattern, std::string str);

int main()
{
    std::string str = "cabscababhh";
    std::string pat = "caba";

    std::cout << KMP_algorithm(pat, str) << std::endl;

    return 0;
}

int KMP_algorithm(std::string pattern, std::string str)
{
    int* next = get_next(pattern);

    int i = 0, j = -1;
    int len_pat = pattern.size();
    int len_str = str.size();

    while (i < len_str && j < len_pat)
    {
        if (j == -1 || pattern[j] == str[i])
        {
            ++ j;
            ++ i;
        }
        else 
            j = next[j];
    }

    if (j == len_pat)
        return i - j;
    
    return -1;
}

int* get_next(std::string pattern)
{
    int len_pat = pattern.size();

    if (len_pat < 0)
        return nullptr;
    
    // std::cout << len_pat << std::endl;

    int* result = new int[len_pat];

	result[0] = -1;
    int i = 0, j = -1;

    while (j < len_pat)
    {
        if (j == -1 || pattern[i] == pattern[j])
        {
            result[i] = j;
            ++ i; 
            ++ j; 
        }
        else
            j = result[j];
    }

    return result;
}
