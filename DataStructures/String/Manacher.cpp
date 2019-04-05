#include <iostream>
#include <string>

std::string pre_process(std::string str);
int* find_len(std::string str, int& index, int& Max);


int main()
{
    std::string str;

    std::cin >> str;

    std::string after_str = pre_process(str);

    int length = after_str.length();

    int index = 0, Max = -1;

    int* result = find_len(after_str, index, Max);

    for (int i = 0; i < length; ++ i)
    {
        std::cout << result[i] << std::endl;
    }

    std::cout << "index = " << index << std::endl;
    std::cout << "Max = " << Max << std::endl;

    std::cout << str.substr((index - Max) / 2, Max) << std::endl;

    return 0;
}

std::string pre_process(std::string str)
{
    std::string result = "";

    for (auto iter = str.begin(); iter != str.end(); ++ iter)
    {
        result += "#";
        result += *iter;
    }
    result += "#";

    return result;
}

int* find_len(std::string str, int& index, int& Max)
{
    int* Len = new int[str.length() + 1];

    Len[0] = 0;

    int right_bondary = 0;
    int right = 0;
    int left = 0;
    index = 0;
    Max = -1;

    for (int i = 0; i < str.length(); ++ i)
    {
        int mirror_i = 2 * index - i;
        if (i < right_bondary)
        {
            if (Len[mirror_i] < right_bondary - i)
            {
                Len[i] = Len[mirror_i];
                continue;
            }
            else
            {
                right = right_bondary;
                left  = 2 * i - right_bondary; 
            }
        }
        else
        {
            right = i;
            left  = i;
        }

        while (right < str.length() && left >= 0 && str[right] == str[left])
        {
            ++ right;
            -- left;
        }

        right = right > str.length() ? str.length() : right;

        Len[i] = right - i - 1;
        if (right - i - 1 >= Max)
        {
            Max = right - i - 1;
            index = i;
        }

        right_bondary = Max + index > str.length() ? str.length() : Max + index;
    }

    return Len;
}
