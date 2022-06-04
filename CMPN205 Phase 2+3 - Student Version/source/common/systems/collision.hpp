#pragma once

#include "../components/collision.hpp"
#include "../components/collision-target.hpp"
#include "../ecs/world.hpp"


namespace our{
    class CollisionSystem {
        float collision_threshold ;
        public:
            CollisionSystem(float col_thres = 0.1) {
                this->collision_threshold = col_thres;
            }
            void update(World* world,float deltatime) {
                for(auto entity : world->getEntities()) {
                    //Hopefully, not many entities in the world has a collision component
                    //Becasue in the worst case, when all entities in the world has a collision component,
                    //The collision detection algorithm runs in (Number_Of_Entities)^2
                    //The more entities in the world can collide, the more we approach this worst case
                    auto colComp = entity->getComponent<CollisionComponent>() ;
                    
                    if(colComp) {
                        auto pos1 = entity->localTransform.position ;

                        for(int i=0; i<6; i++) colComp->collision_state[i] = false ;

                        for(auto entity2 : world->getEntities()) {
                            auto colGeoComp = entity2->getComponent<CollisionTargetComponent>();
                            if(colGeoComp) {
                                auto colGeometry = colGeoComp->targetGeometry ;
                                if(colGeometry) {
                                    auto pos2 = entity2->localTransform.position ;
                                    CollisionResult collisionX 
                                    = colGeometry->isCollidingX(pos1,pos2,collision_threshold);
                                    CollisionResult collisionY 
                                    = colGeometry->isCollidingY(pos1,pos2,collision_threshold);
                                    CollisionResult collisionZ
                                     = colGeometry->isCollidingZ(pos1,pos2,collision_threshold);

                                    switch (collisionX) {
                                    case CollisionResult::COLLISION_IN_POSITIVE_AXIS:
                                        colComp->collision_state[CollisionComponent::X_AXIS] = true ;
                                        break ;
                                    case CollisionResult::COLLISION_IN_NEGATIVE_AXIS:
                                        colComp->collision_state[CollisionComponent::_X_AXIS] = true ;
                                        break ;
                                    case CollisionResult::NO_COLLISION:
                                    default:
                                        break;
                                    }
                                    switch (collisionY) {
                                    case CollisionResult::COLLISION_IN_POSITIVE_AXIS:
                                        colComp->collision_state[CollisionComponent::Y_AXIS] = true ;
                                        break ;
                                    case CollisionResult::COLLISION_IN_NEGATIVE_AXIS:
                                        colComp->collision_state[CollisionComponent::_Y_AXIS] = true ;
                                        break ;
                                    case CollisionResult::NO_COLLISION:
                                    default:
                                        break;
                                    }
                                    switch (collisionZ) {
                                    case CollisionResult::COLLISION_IN_POSITIVE_AXIS:
                                        colComp->collision_state[CollisionComponent::Z_AXIS] = true ;
                                        break ;
                                    case CollisionResult::COLLISION_IN_NEGATIVE_AXIS:
                                        colComp->collision_state[CollisionComponent::_Z_AXIS] = true ;
                                        break ;
                                    case CollisionResult::NO_COLLISION:
                                    default:
                                        break;
                                    }
                                }   
                            }
                        }
                    } 
                }
            }
    };
} 
