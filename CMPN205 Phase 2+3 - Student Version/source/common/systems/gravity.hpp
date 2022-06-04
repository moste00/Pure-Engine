#pragma once

#include "../components/gravity.hpp"
#include "../components/collision.hpp"
#include "../components/movement.hpp"
#include "../components/controllable-movement.hpp"
#include "../ecs/world.hpp"

namespace our {
    class GravitySystem {
        public:
            void update(World* world, float deltatime) {
                for(auto entity : world->getEntities()) {
                    auto gravComp = entity->getComponent<GravityComponent>() ;
                    auto movComp = entity->getComponent<MovementComponent>() ;
                    auto conMovComp = entity->getComponent<ControllableMovementComponent>() ;
                    //Is the enity affected by gravity ?
                    if(gravComp && (movComp || conMovComp)) {
                        //Is the enity collidable ?
                        auto colComp = entity->getComponent<CollisionComponent>();
                        //If it is collidable, check if it's colliding with the ground (i.e. resting),
                        //If it is, Don't pull it down any further
                        bool collision = (colComp 
                                      && colComp->collision_state[CollisionComponent::_Y_AXIS]) ;
                        if(collision) {
                            if(movComp) {
                                movComp->linearVelocity.y = 0.0 ;
                            }
                            if(conMovComp) {
                                conMovComp->linearVelocity.y = 0.0 ;
                                conMovComp->isJumping = false ;
                            } 
                        } else {
                            //Otherwise, if it's not collidable or not currently colliding with the ground
                            //pull it down by g 
                            if(movComp) {
                                movComp->linearVelocity.y -= gravComp->g * deltatime ;
                            }
                            if(conMovComp) {
                                conMovComp->linearVelocity.y -= gravComp->g * deltatime ;
                            }
                        }
                    }
                }
            }
    };
}
