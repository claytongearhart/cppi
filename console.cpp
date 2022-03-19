#include "objects.hpp"
#include <iostream>
#include <sstream>

std::string handler(std::string input)
{
    std::stringstream ss(input);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> tokens(begin, end);
    //std::copy(tokens.begin(), tokens.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    return tokens[0];
    if (tokens[0] == "new")
    {
        if (tokens[1] == "obj")
        {
            //objectManager.updateVar(object()) // Add object 
        }
        else if (tokens[1] == "type")
        {

        }
    }
}

int main()
{
    std::cout << "Test console\n";
    while (true)
    {
        std::cout << ">";
        std::string input;
        std::cin >> input;
        std::cout << handler(input) << "\n";
    }
}