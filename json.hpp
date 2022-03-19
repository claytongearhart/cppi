#include <string>
#include <map>
#include <variant>

class jsonNumber
{

};


class jsonType
{
    public:
        std::variant<std::string, jsonNumber, bool> data;

        jsonType(std::variant<std::string, jsonNumber, bool> input)
        {
            data = input;
        }

        template <class T>
        T getData()
        {
            return std::get<T>(data);
        }
};

class json
{
    public:
        auto operator [] (std::string key)
        {
            if (data.count(key) > 0)
            {
                return data[key];
            }
            else
            {
                throw std::out_of_range("Key not found");
                //return "KYS u jew";
            }
        }

    private:
        std::map<std::string, std::variant<json, jsonType>> data;

};