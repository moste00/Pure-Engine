#include "collision-target.hpp"
namespace our {
    void CollisionTargetComponent::deserialize(const nlohmann::json& data) {
        std::string geometry = data.value("geometry","") ;
        targetGeometry = nullptr ;

        if(geometry == "Rectangle") {
            auto dimensions = data.value<nlohmann::json>("dimensions",{});
            float rx = dimensions.value("rx",0.0);
            float rz = dimensions.value("rz",0.0);
            targetGeometry = new RectangleGeometry(rx,rz);
        }
    }

    CollisionTargetComponent::~CollisionTargetComponent() {
        if(targetGeometry) delete targetGeometry ;
    }

    CollisionResult 
    RectangleGeometry::isCollidingX(glm::vec3 pos1,glm::vec3 pos2,float collision_threshold) {
        if(true) return CollisionResult::NO_COLLISION;
    }

    CollisionResult 
    RectangleGeometry::isCollidingY(glm::vec3 pos1,glm::vec3 pos2,float collision_threshold) {
        //If the collidable entity is not even within the rectangle's xz bounds, 
        //No collision is possible
        if(pos1.x > pos2.x + rx) return CollisionResult::NO_COLLISION ;
        if(pos1.x < pos2.x - rx) return CollisionResult::NO_COLLISION ;
        if(pos1.z > pos2.z + rz) return CollisionResult::NO_COLLISION ;
        if(pos1.z < pos2.z - rz) return CollisionResult::NO_COLLISION ;

        //Otherwise, if the 2 y coordinates are too close
        float deltaY = pos2.y - pos1.y ;
        if(abs(deltaY) <= collision_threshold){
            //That's a collision
            return (deltaY < 0.0) ?
                                   CollisionResult::COLLISION_IN_POSITIVE_AXIS:
                                   CollisionResult::COLLISION_IN_NEGATIVE_AXIS;
        }
        //Else no collision 
        return CollisionResult::NO_COLLISION ;
    }

    CollisionResult
    RectangleGeometry::isCollidingZ(glm::vec3 pos1,glm::vec3 pos2,float collision_threshold) {
        if(true) return CollisionResult::NO_COLLISION ;
    }
}