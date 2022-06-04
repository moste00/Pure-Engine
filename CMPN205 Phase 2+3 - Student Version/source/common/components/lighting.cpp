#include "lighting.hpp"
#include "../ecs/entity.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include "glm/gtx/string_cast.hpp"
#include "../deserialize-utils.hpp"
#include <iostream>



namespace our {
    // Reads camera parameters from the given json object
    void LightComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        std::string LightTypestr = data.value("lightType", LightTypestr);
        if(LightTypestr == "DIRECTIONAL"){
            lighttype = LightType::DIRECTIONAL;
        } else if (LightTypestr == "POINT") {
            lighttype = LightType::POINT;
        } else if (LightTypestr == "SPOT") {
            lighttype = LightType::SPOT;
        }

        position = data.value("linearVelocity", position);
        direction = data.value("direction", direction);
        diffuse = glm::vec3(data.value("diffuse", diffuse));
        specular = glm::vec3(data.value("specular", specular));
        cone_angles = glm::vec2(data.value("cone_angles", cone_angles));
        // TODO CALCULATE ATTENUATION IN SHADER
    }

}
