#pragma once 

#include "../ecs/world.hpp"
#include "../components/controllable-movement.hpp"

#include "../application.hpp"

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
                        
                        if(app->getKeyboard().isPressed(conMovComp->upKey)) {
                             entity->localTransform.position.z -= deltaTime * velocity.z ;
                        }
                        if(app->getKeyboard().isPressed(conMovComp->downKey)) {
                             entity->localTransform.position.z += deltaTime * velocity.z ;
                        }
                        if(app->getKeyboard().isPressed(conMovComp->leftKey)) {
                             entity->localTransform.position.x -= deltaTime * velocity.x ;
                        }
                        if(app->getKeyboard().isPressed(conMovComp->rightKey)) {
                             entity->localTransform.position.x += deltaTime * velocity.x ;
                        }
                    }                   
                }
            }
    };
}