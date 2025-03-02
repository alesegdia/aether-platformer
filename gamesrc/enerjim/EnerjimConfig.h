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

	int GetWindowWidth() const
	{
		return mWindowWidth;
	}

	int GetWindowHeight() const
	{
		return mWindowHeight;
	}

	int GetOrthoScale() const
	{
		return mOrthoScale;
	}
    
private:
    int mWindowWidth;
    int mWindowHeight;
    int mOrthoScale;
    
private:

    EnerjimConfig()
    {
        std::string error;
        
        std::ifstream t("assets/enerjim/configs.json");
        std::stringstream buffer;
        buffer << t.rdbuf();

        auto result = json11::Json::parse(buffer.str(), error);
        std::cout << error << std::endl;
        mWindowWidth = result["windowWidth"].int_value();
        mWindowHeight = result["windowHeight"].int_value();   
        mOrthoScale = result["orthoScale"].int_value();
        /*
        playerSpeed = result["playerHorizontalSpeed"].number_value();
        playerJumpForce = result["playerJumpForce"].number_value();
        playerGravityFactor = result["playerGravityFactor"].number_value();
        playerFallingCap = result["playerFallingCap"].number_value();
        */
    }

};


}
