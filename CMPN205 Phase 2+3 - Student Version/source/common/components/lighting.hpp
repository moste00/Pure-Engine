#pragma once

#include "../ecs/component.hpp"

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
       
        int type;
        vec3 position;
        vec3 direction;
        vec3 diffuse;
        vec3 specular;
        vec3 attenuation; // x*d^2 + y*d + z
        vec2 cone_angles; // x: inner_angle, y: outer_angle

        // The ID of this component type is "Camera"
        static std::string getID() { return "Light"; }

        // Reads camera parameters from the given json object
        void deserialize(const nlohmann::json& data) override;

        // Creates and returns the camera view matrix
        glm::mat4 getViewMatrix() const;
        
        // Creates and returns the camera projection matrix
        // "viewportSize" is used to compute the aspect ratio
        glm::mat4 getProjectionMatrix(glm::ivec2 viewportSize) const;
    };

}