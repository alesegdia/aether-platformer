#pragma once

#include <aether/aether.h>

#include <fstream>


namespace enerjim {


class EnerjimConfig
{
public:
    
    static const EnerjimConfig& instance()
    {
        static EnerjimConfig config;
        return config;
    }
    
    double windowWidth;
    double windowHeight;
    
private:

    EnerjimConfig()
    {
        std::string error;
        
        std::ifstream t("assets/jojo/configs.json");
        std::stringstream buffer;
        buffer << t.rdbuf();
                        
        auto result = json11::Json::parse(buffer.str(), error);
        std::cout << error << std::endl;
        windowWidth = result["windowWidth"].number_value();
        windowHeight = result["windowHeight"].number_value();   

        /*
        playerSpeed = result["playerHorizontalSpeed"].number_value();
        playerJumpForce = result["playerJumpForce"].number_value();
        playerGravityFactor = result["playerGravityFactor"].number_value();
        playerFallingCap = result["playerFallingCap"].number_value();
        */
    }

};


}
