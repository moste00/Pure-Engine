#include "gravity.hpp"

namespace our {
    void GravityComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        
        g = data.value("g",g);
    }
}