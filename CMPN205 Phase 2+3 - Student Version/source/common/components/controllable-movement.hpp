#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {

    //This is just like the movement component but it only moves in response to user input
    //The corresponding system is ControllableMovementSystem
    class ControllableMovementComponent : public Component {
    public:
        bool isJumping = true ;
        float jump_acceleration = 5.0 ;
        glm::vec3 linearVelocity = {0, 0, 0}; // Each frame, the entity should move as follows: position += linearVelocity * deltaTime 
        glm::vec3 angularVelocity = {0, 0, 0}; // Each frame, the entity should rotate as follows: rotation += angularVelocity * deltaTime
        int upKey  = GLFW_KEY_UP   ,
          downKey  = GLFW_KEY_DOWN ,
          leftKey  = GLFW_KEY_LEFT ,
          rightKey = GLFW_KEY_RIGHT,
           jumpKey = GLFW_KEY_SPACE;
        //ID is "Controllable Movement"
        static std::string getID() { return "Controllable Movement"; }

        // Reads controllable movement parameters from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}