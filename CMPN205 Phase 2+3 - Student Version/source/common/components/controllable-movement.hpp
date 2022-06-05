#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {
    enum class Coordinate {X,Y,Z};
    enum class ComparisonOperator {GT,GTE,E,LT,LTE,NE};
    //Represents a comparison condition on a spatial coordinate
    //Used to represent win conditions and lose conditions
    struct CoordinateComparisonCondition {
        Coordinate coordinateToTest ;
        ComparisonOperator testOperator ;
        float threshold ;

        bool eval(glm::vec3 pos) {
            float testCoordinate = (coordinateToTest == Coordinate::X)? pos.x :
                                   (coordinateToTest == Coordinate::Y)? pos.y : pos.z ;
            switch(testOperator){
                case ComparisonOperator::GT : return testCoordinate >  threshold ;
                case ComparisonOperator::GTE: return testCoordinate >= threshold ;
                case ComparisonOperator::E  : return testCoordinate == threshold ;
                case ComparisonOperator::LT : return testCoordinate <  threshold ;
                case ComparisonOperator::LTE: return testCoordinate <= threshold ;
                case ComparisonOperator::NE : return testCoordinate != threshold ;
            }
        }
        void deserialize(const std::string&);
    };
    //This is just like the movement component but it only moves in response to user input
    //The corresponding system is ControllableMovementSystem
    class ControllableMovementComponent : public Component {
    public:
        bool isJumping = false ;
        float jump_acceleration = 0.0 ;
        glm::vec3 linearVelocity = {0, 0, 0}; // Each frame, the entity should move as follows: position += linearVelocity * deltaTime 
        glm::vec3 angularVelocity = {0, 0, 0}; // Each frame, the entity should rotate as follows: rotation += angularVelocity * deltaTime
        int upKey  = GLFW_KEY_UP   ,
          downKey  = GLFW_KEY_DOWN ,
          leftKey  = GLFW_KEY_LEFT ,
          rightKey = GLFW_KEY_RIGHT,
           jumpKey = GLFW_KEY_SPACE;

        CoordinateComparisonCondition winWhen, loseWhen ;   
        //ID is "Controllable Movement"
        static std::string getID() { return "Controllable Movement"; }

        // Reads controllable movement parameters from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}