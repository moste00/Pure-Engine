#pragma once 

#include "../ecs/component.hpp"
#include "glm/glm.hpp"
#include <iostream>
namespace our {
    enum class CollisionResult {
        NO_COLLISION, COLLISION_IN_POSITIVE_AXIS, COLLISION_IN_NEGATIVE_AXIS
    };
    class CollisionTargetGeometry {
        public: 
            virtual CollisionResult 
                    isCollidingX(glm::vec3 pos1,glm::vec3 pos2,float collision_threshold) = 0 ;
            virtual CollisionResult 
                    isCollidingY(glm::vec3 pos1,glm::vec3 pos2,float collision_threshold) = 0 ;
            virtual CollisionResult 
                    isCollidingZ(glm::vec3 pos1,glm::vec3 pos2,float collision_threshold) = 0 ;   
    };

    class RectangleGeometry : public CollisionTargetGeometry {
        //dimensions of the rectangle, measured from THE CENTER OF THE RECTANGLE
        float rx,rz ;
        public:
            RectangleGeometry(float l,float w) {
                rx = l ; rz = w ;
                std::cout<<"\nPlatform Dimensions:\n"<<rx<<"   "<<rz<<"\n";
            }
            CollisionResult 
            isCollidingX(glm::vec3 pos1,glm::vec3 pos2,float collision_threshold) override ;
            CollisionResult 
            isCollidingY(glm::vec3 pos1,glm::vec3 pos2,float collision_threshold) override ;
            CollisionResult 
            isCollidingZ(glm::vec3 pos1,glm::vec3 pos2,float collision_threshold) override ;
    };

    class CollisionTargetComponent : public Component {
        public:
            CollisionTargetGeometry* targetGeometry ;

            //ID is "Collision Target"
            static std::string getID() { return "Collision Target"; }

            void deserialize(const nlohmann::json& data) override;

            ~CollisionTargetComponent() override ;
    };
}