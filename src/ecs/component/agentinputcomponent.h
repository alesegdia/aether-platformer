#pragma once

struct AgentInputComponent
{
    int x_axis = 0;
    int y_axis = 0;
    bool attack_requested = false;
    bool jump_requested = false;
    bool jump_just_requested = false;
    float horizontal_speed = 0;
    float jump_force = 0;
};
