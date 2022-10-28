#pragma once

struct AgentInputComponent
{
    float x_axis = 0;
    float y_axis = 0;
    bool attack_requested = false;
    bool jump_requested = false;
	bool jump_just_requested = false;
	bool running = false;
	bool slowing_down = false;
    float horizontal_speed = 0;
    float jump_force = 0;
};
