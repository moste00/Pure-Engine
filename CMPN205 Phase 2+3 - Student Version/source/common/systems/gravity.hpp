#pragma once

#include "../components/gravity.hpp"
#include "../components/collision.hpp"
#include "../ecs/world.hpp"

namespace our {
    class GravitySystem {
        public:
            void update(World* world, float deltatime) {
                for(auto entity : world->getEntities()) {
                    auto gravComp = entity->getComponent<GravityComponent>() ;
                    //Is the enity affected by gravity ?
                    if(gravComp) {
                        //Is the enity collidable ?
                        auto colComp = entity->getComponent<CollisionComponent>();
                        //If it is collidable, check if it's colliding with the ground (i.e. resting),
                        //If it is, Don't pull it down any further
                        bool pullDown =!(colComp 
                                      && colComp->collision_state[CollisionComponent::_Y_AXIS]) ;
                        //Otherwise, if it's not collidable or not currently colliding with the ground
                        //pull it down by g 
                        if(pullDown) entity->localTransform.position.y -= 0.5f * gravComp->g * deltatime ;
                    }
                }
            }
    };
}
