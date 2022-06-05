#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>
#include "../asset-loader.hpp"
#include <json/json.hpp>
#include <glm/mat4x4.hpp>

namespace our {

    // An enum that defines the type of the camera (ORTHOGRAPHIC or PERSPECTIVE) 
    enum class LightType {
        DIRECTIONAL,
        POINT,
        SPOT
    };

    // This component denotes that any renderer should draw the scene relative to this camera.
    // We do not define the eye, center or up here since they can be extracted from the entity local to world matrix
    class LightComponent : public Component {
    public:
        LightType lighttype; // The type of the camera
       
        //int type;              //USELESS
        glm :: vec3 position = {0.0, 0.0, 0.0};
        glm :: vec3 direction= glm :: vec3 (0.0, 0.0, 0.0);
        glm :: vec3 diffuse= glm :: vec3 (0.0, 0.0, 0.0);
        glm :: vec3 ambient= glm :: vec3 (0.2, 0.2, 0.2);
        glm :: vec4 color= glm :: vec4 (1.0, 1.0, 1.0, 1.0);
        glm :: vec3 specular= glm :: vec3 (0.0, 0.0, 0.0);
        glm :: vec3 attenuation= glm :: vec3 (0.0, 0.0, 0.0); // x*d^2 + y*d + z                        //should be calculated not read
        glm :: vec2 cone_angles= glm :: vec2 (0.0, 0.0); // x: inner_angle, y: outer_angle

        // The ID of this component type is "Camera"
        static std::string getID() { return "Light"; }

        // Reads camera parameters from the given json object
        void deserialize(const nlohmann::json& data) override;

    };

}