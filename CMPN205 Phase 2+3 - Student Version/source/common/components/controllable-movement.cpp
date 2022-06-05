#include "../deserialize-utils.hpp"
#include "../ecs/entity.hpp"
#include "controllable-movement.hpp"
#include "imgui.h"
namespace our {
    void ControllableMovementComponent::deserialize(const nlohmann::json& data) {
        if(!data.is_object()) return ;

        linearVelocity = data.value("linearVelocity", linearVelocity);
        angularVelocity = glm::radians(data.value("angularVelocity", angularVelocity));

        //If the component specifies the control keys,
        //override the defaults with what you can find
        if(data.contains("controlKeys")) {
            auto controlKeys = data["controlKeys"];
            auto NONE = gl_enum_deserialize::keyboard_keys.end();
            //Not all control keys must be overriden           
            if(controlKeys.contains("x+")) {
                auto it = gl_enum_deserialize::keyboard_keys.find(controlKeys["x+"]);
                if(it != NONE) leftKey = it->second ; 
            }
            if(controlKeys.contains("x-")) {
                auto it = gl_enum_deserialize::keyboard_keys.find(controlKeys["x-"]);
                if(it != NONE) rightKey = it->second ; 
            }
            if(controlKeys.contains("z+")) {
                auto it = gl_enum_deserialize::keyboard_keys.find(controlKeys["z+"]);
                if(it != NONE) upKey = it->second ; 
            }
            if(controlKeys.contains("z-")) {
                auto it = gl_enum_deserialize::keyboard_keys.find(controlKeys["z-"]);
                if(it != NONE) downKey = it->second ; 
            }
            if(controlKeys.contains("y+")) {
                auto it = gl_enum_deserialize::keyboard_keys.find(controlKeys["y+"]);
                if(it != NONE) jumpKey = it->second ; 
            } 
        }
        winWhen.deserialize(data["winWhen"]);
        loseWhen.deserialize(data["loseWhen"]);
    }

    void CoordinateComparisonCondition::deserialize(const std::string& condition) {
        switch (condition[0]) {
        case 'x':
            coordinateToTest = Coordinate::X ;
            break;
        case 'y':
            coordinateToTest = Coordinate::Y ;
            break;
        case 'z':
            coordinateToTest = Coordinate::Z ;
            break;
        default: break ;
        }
        //skip spaces
        int i = 1;
        while(condition[i++] == ' ');
        i-- ;

        if(       condition[i] == '<' && condition[i+1] == '='){
            testOperator = ComparisonOperator::LTE ;
        } else if(condition[i] == '<' && condition[i+1] == ' '){
            testOperator = ComparisonOperator::LT ;
        } else if(condition[i] == '>' && condition[i+1] == '='){
            testOperator = ComparisonOperator::GTE ;
        } else if(condition[i] == '>' && condition[i+1] == ' '){
            testOperator = ComparisonOperator::GT ;
        } else if(condition[i] == '=' && condition[i+1] == '='){
            testOperator = ComparisonOperator::E ;
        } else if(condition[i] == '!' && condition[i+1] == '='){
            testOperator = ComparisonOperator::NE ;
        }

        threshold = std::stof(condition.substr(i+2,std::string::npos));
    }
}