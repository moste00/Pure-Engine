#pragma once

#include "../ecs/component.hpp"

namespace our {
    class CollisionComponent: public Component {
        public:
            //Is there a collision in any of the 6 directions?
            bool collision_state[6] = {false};
            //Index of positive x-axis collision flag
            const static int  X_AXIS = 0 ;
            //Index of negative x-axis collision flag
            const static int _X_AXIS = 1 ;
            //Index of positive y-axis collision flag
            const static int  Y_AXIS = 2 ;
            //Index of negative y-axis collision flag
            const static int _Y_AXIS = 3 ;
            //Index of positive z-axis collision flag
            const static int  Z_AXIS = 4 ;
            //Index of negative z-axis collision flag
            const static int _Z_AXIS = 5 ;

            //ID is "Collision"
            static std::string getID() { return "Collision"; }
            //Empty, as collision has no .json parameters
            void deserialize(const nlohmann::json& data) override;
    };
}
