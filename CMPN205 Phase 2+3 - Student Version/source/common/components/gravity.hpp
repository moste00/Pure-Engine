#pragma once

#include "../ecs/component.hpp"

namespace our {

    //This is just like the movement component but moves owning entites
    //The corresponding system is GravitySystem
    class GravityComponent : public Component {
    public:
        float g = 1.0 ;
        static std::string getID() { return "Gravity"; }

        // Reads controllable movement parameters from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}