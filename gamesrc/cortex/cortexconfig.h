#pragma once

#include <aether/aether.h>

#include <fstream>

namespace cortex {


class CortexConfig
{
public:
    
    static const CortexConfig& instance()
    {
        static CortexConfig config;
        return config;
    }
    
    double windowWidth;
    double windowHeight;
    double playerSpeed;
    double playerJumpForce;
    double playerGravityFactor;
    double playerFallingCap;
    
private:

    CortexConfig()
    {
        std::string error;
        
        std::ifstream t("assets/cortex/configs.json");
        std::stringstream buffer;
        buffer << t.rdbuf();

        auto result = json11::Json::parse(buffer.str(), error);
        std::cout << error << std::endl;
        windowWidth = result["windowWidth"].number_value();
        windowHeight = result["windowHeight"].number_value();
        playerSpeed = result["playerHorizontalSpeed"].number_value();
        playerJumpForce = result["playerJumpForce"].number_value();
        playerGravityFactor = result["playerGravityFactor"].number_value();
        playerFallingCap = result["playerFallingCap"].number_value();
    }

};


}
