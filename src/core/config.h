#pragma once

#include <aether/aether.h>

#include <fstream>

template <typename ConfigSub>
class Config
{
public:
    
    static const ConfigSub& instance()
    {
        static ConfigSub config;
        return config;
    }
    
protected:

    Config(std::string configPath)
    {
        std::string error;
        
        std::ifstream t(configPath);
        std::stringstream buffer;
        buffer << t.rdbuf();
                        
        auto result = json11::Json::parse(buffer.str(), error);
        std::cout << error << std::endl;

        for( const auto& object : result.object_items() ) {
            auto key = object.first;
            auto value = object.second;
            if( value.is_number() ) {
                m_numbers[key] = value.number_value();
            } else if( value.is_string() ) {
                m_strings[key] = value.string_value();
            }
        }
    }

    double getNumber(std::string key)
    {
        return m_numbers[key];
    }

    const std::string& getString(std::string key)
    {
        return m_strings[key];
    }


private:
    std::unordered_map<std::string, double> m_numbers;
    std::unordered_map<std::string, std::string> m_strings;


};
