#pragma once 

#include "../ecs/world.hpp"
#include "../components/controllable-movement.hpp"

#include "../application.hpp"
#include <iostream>
namespace our {
    //This system is responsible for moving all entities who have a 
    //ControllableMovementComponent by the velocities described in the component
    class ControllableMovementSystem {
        Application* app ;

        public:
            void enter(Application* app) {
                this->app = app ;
            }
            void update(World* world, float deltaTime) {
                for(auto entity : world->getEntities()) {
                    auto conMovComp = entity->getComponent<ControllableMovementComponent>() ;
                    
                    if(conMovComp) {
                        auto velocity = conMovComp->linearVelocity ;
                        auto keyboard = app->getKeyboard();
                        if(keyboard.isPressed(conMovComp->upKey)) {
                             entity->localTransform.position.z -= deltaTime * velocity.z ;
                        }
                        if(keyboard.isPressed(conMovComp->downKey)) {
                             entity->localTransform.position.z += deltaTime * velocity.z ;
                        }
                        if(keyboard.isPressed(conMovComp->leftKey)) {
                             entity->localTransform.position.x -= deltaTime * velocity.x ;
                        }
                        if(keyboard.isPressed(conMovComp->rightKey)) {
                             entity->localTransform.position.x += deltaTime * velocity.x ;
                        }

                        if(!conMovComp->isJumping) {
                            if(keyboard.isPressed(conMovComp->jumpKey)) {
                                conMovComp->isJumping = true ;
                                conMovComp->jump_acceleration = 5.0 ;
                            }
                        }
                        if(conMovComp->isJumping) {
                            conMovComp->jump_acceleration -= 0.1 ;
                            if(conMovComp->jump_acceleration <= 0.0) {
                                conMovComp->jump_acceleration = 0.0 ;
                            }
                        }
                        conMovComp->linearVelocity.y += conMovComp->jump_acceleration*deltaTime;
                        entity->localTransform.position.y += conMovComp->linearVelocity.y*deltaTime;
                    }                   
                }
            }
    };
}