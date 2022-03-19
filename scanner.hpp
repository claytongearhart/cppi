#include <array>
#include <string>

class
{
  private:
    static inline const std::string boolTokens[] = {"true", "false"},
                                    delimiterTokens[] = {"(", ")", "{", "}", ";", ","},
                                    keywordTokens[] = {"auto", "do", "switch", "return", "class"},
                                    typeTokens[] = {"int", "float", "double"},
                                    operatorTokens[] = {"<",  ">",  "<=", ">=", "*",  "+",  "-",
                                                        "/",  "=",  "-=", "*=", "+=", "/=", "++",
                                                        "--", "==", "&&", "||", "^",  "%"};
} scanner;