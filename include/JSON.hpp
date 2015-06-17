#ifndef JSON_HPP
#define JSON_HPP

#include <string>
#include <regex>
#include <unordered_map>
#include <experimental/any>
#include "debug.h"

struct Range {
    int begin;
    int end;
};

class JSON {
    private:
        std::unordered_map <std::string, std::experimental::any> deserialized;
        std::vector <std::string> inserted_indexes;
        std::vector <std::experimental::any> inserted_values;
        std::vector <Range> inserted_objects;
        std::experimental::any deserialize_value(std::string value);
        std::string get_representation(std::experimental::any value);

        /* This is probably slow as hell */
        template <typename T>
        T lexical_cast(const std::string& str) {
            T var;
            std::istringstream iss;
            iss.str(str);
            iss >> var;
            // Ignore any error bits that may have been set on the stream - YOLO
            return var;
        }
    public:
        JSON(std::string json_string);
        JSON() {};
        std::string serialize();
        template <typename T>
        T get(std::string index) {return std::experimental::any_cast<T>(deserialized[index]);};
        template <typename T>
        void add(std::string index, T value) {
            if (inserted_objects.size() == 0) {
                add_object();
            }
            inserted_indexes.push_back(index);
            inserted_values.emplace_back(std::experimental::any(value));
            inserted_objects.back().end++;
        }
        void add_object();
        bool is_empty() const {return deserialized.size() == 0;}
};

#endif // JSON_HPP
