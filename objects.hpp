#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <memory>
#include <array>
#include <variant>
#include <functional>

enum accessSpecifier
{
    priv,
    protect,
    pub
};

class generic;

struct classMember
{
    accessSpecifier access;
    generic member;
};

template <class T>
struct opearator
{
    std::string operatorSymbol;
    std::function<T()>;
};

class userType
{
    public:
        std::vector<classMember> members;
        std::string name;
        bool init;

        userType()
        {
            init = false;
        }

        userType(std::string className)
        {
            init = true;
            name = className;
        }

        void addMember(classMember input)
        {
            members.push_back(input);
        }

        void addMember(generic member, accessSpecifier access)
        {
            members.push_back(classMember{access=access, member=member});
        }
};

class type
{
    public:
        bool ict;
        std::string tn;
        std::vector<std::string> mods;
        type(std::string typeName, bool isCType, std::vector<std::string> modifiers, userType definition())
        {
            tn = typeName;
            ict = isCType;
            mods = modifiers;
        }
};

class function
{
    public:
        std::string n;
        function(){}
        function(std::string name, std::string returnType)
        {
            n = name;
        }
};

class object
{
    public:
        std::string n;
        object(){}
        object(std::string name, std::string value, std::string type)
        {
            n = name;
        }
};

class generic : std::variant<object, function>
{
    
};


class
{
    public:
        void addUserType(type input)
        {
            userTypes.push_back(input);
        }
        void updateVar(object input)
        {
            variables[input.n] = input;
        }
        void updateFunc(function input)
        {
            functions[input.n] = input;
        }
        object var(std::string varName)
        {
            if (variables.count(varName) > 0)
            {
                return variables.at(varName);
            }
            else
            {
                return object();
            }
        }
        function func(std::string funcName)
        {
            if (functions.count(funcName) > 0)
            {
                return functions.at(funcName);
            }
            else
            {
                return function();
            }
        }

        
    private:
        std::map<std::string, object> variables;
        std::map<std::string, function> functions;
        std::vector<type> userTypes;

} objectManager;