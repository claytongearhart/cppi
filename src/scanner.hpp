#include "utils.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class scanner
{
  private:
    std::vector<std::pair<int, int>> stringLocations;
    std::vector<std::string>
        boolTokens = {"true", "false"},

        delimiterTokens = {"(", ")", "{", "}", ";", ","},

        keywordTokens = {"int", "float",  "auto",  "double",
                         "do",  "switch", "return"},

        operatorTokens = {"<", ">",  "<=", ">=", "*",  "+",  "-",  "/",
                          "=", "-=", "*=", "+=", "/=", "++", "--", "=="};
    std::vector<std::pair<std::string, int>> tokenValues;
    bool isDigit(const std::string &input)
    {
        return std::all_of(input.begin(), input.end(), ::isdigit);
    }

    bool isString(const std::string &input)
    {
        return input[0] == '\"' && input[input.size() - 1] == '\"';
    }
    void findStrings(std::string input)
    {
        std::vector<int> quoteLocations;

        for (int i = 0; i < input.size(); i++)
        {
            if (input[i] == '\"' ||
                input[i] == '\'' && input[i - 1] != '\\')
            {
                std::cout << "Quote locations has been pushed back\n";
                quoteLocations.push_back(i);
            }
        }
        for (int i = 0; i < quoteLocations.size(); i += 2)
        {
            stringLocations.emplace_back(
                std::make_pair(quoteLocations[i], quoteLocations[i + 1]));
        }
        for (int i = 0; i < stringLocations.size(); i++)
        {
            std::cout << "String at " << stringLocations[i].first << ", "
                      << stringLocations[i].second << "\n";
        }
    }

    bool isInString(int location)
    {

        for (int i = 0; i < stringLocations.size(); i++)
        {
            // std::cout << "Called to check if : " << location << " is
            // between " << stringLocations[i].first << " and " <<
            // stringLocations[i].second << "\n";
            if ((stringLocations[i].first + 1 < location) &&
                (location < stringLocations[i].second - 1))
            {
                return true;
            }
        }
        return false;
    }

    size_t find_first_of_delim(std::string input, std::string delims,
                               size_t lastPos)
    {

        for (int i = lastPos; i < input.size(); i++)
        {
            if ((delims.find(input[i]) != std::string::npos) &&
                !isInString(i))
            {
                return i;
            }
        }

        return std::string::npos;
    }
    squid::tokenTypes tokenType(std::string token)
    {

        return squid::utils::isInStringVec(operatorTokens, token)
                   ? squid::boolToken
               : squid::utils::isInStringVec(delimiterTokens, token)
                   ? squid::delimiterToken
               : squid::utils::isInStringVec(keywordTokens, token)
                   ? squid::keywordToken
               : squid::utils::isInStringVec(boolTokens, token)
                   ? squid::operatorToken
               : isString(token) ? squid::stringToken
               : isDigit(token)  ? squid::digitToken
                                 : squid::other;
    }

    void refineTokens()
    {
        std::vector<squid::token> tempFullTokens;
        for (int i = 0; i < fullTokens.size(); i++)
        {
            if (!(fullTokens[i].value.length() == 1))
            {
                auto beginTokenValue = fullTokens[i].value.substr(
                    0, fullTokens[i].value.size() - 1);
                std::string lastTokenValue(1, fullTokens[i].value.back());

                tempFullTokens.push_back({tokenType(beginTokenValue),
                                          beginTokenValue,
                                          fullTokens[i].location});
                tempFullTokens.push_back({tokenType(lastTokenValue),
                                          lastTokenValue,
                                          fullTokens[i].location});
            }
            else
            {
                tempFullTokens.push_back(fullTokens[i]);
            }
        }
        fullTokens = tempFullTokens;
    }

  public:
    std::vector<squid::token> fullTokens;

    void split(std::string s)
    {
        size_t pos = 0, lastPos = 0;
        while ((pos = find_first_of_delim(
                    s, " []{}()<>+-*/&:.\n\"",
                    lastPos)) != // Make wrapper function of find_first_of
                                 // to check if is in string or not
               std::string::npos)
        {
            std::string token = s.substr(lastPos, pos - lastPos + 1);
            fullTokens.push_back({tokenType(token), token, pos});
            lastPos = pos + 1;
        }

    }
    void analyze(std::string input)
    {
        findStrings(input);
        split(input);
        refineTokens();
        // sanatizeTokens();
        // findStrings();
    }

    void calcTypes()
    {
        for (int i = 0; i < tokenValues.size(); i++)
        {
            fullTokens.push_back({tokenType(tokenValues[i].first),
                                  tokenValues[i].first, 1});
        }
    }

    void sanatizeTokens()
    {
        for (int i = 0; i < fullTokens.size(); i++)
        {
            for (int j = 0; j < fullTokens[i].value.size(); j++)
            {
                if (squid::utils::isSpace(fullTokens[i].value[j])) //
                {
                    fullTokens[i].value.erase(j, 1);
                }
            }
            if (fullTokens[i].value == "")
            {
                fullTokens.erase(fullTokens.begin() + i);
            }
        }
    }
};
