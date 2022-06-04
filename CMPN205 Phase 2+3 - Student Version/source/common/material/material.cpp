#include "material.hpp"

#include "../asset-loader.hpp"
#include "deserialize-utils.hpp"

namespace our {


    // This function should setup the pipeline state and set the shader to be used
    void Material::setup() const {
        //TODO: (Req 6) Write this function
        pipelineState.setup();
        shader->use();
    }

    // This function read the material data from a json object
    void Material::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;

        if(data.contains("pipelineState")){
            pipelineState.deserialize(data["pipelineState"]);
        }
        shader = AssetLoader<ShaderProgram>::get(data["shader"].get<std::string>());
        transparent = data.value("transparent", false);
    }

    // This function should call the setup of its parent and
    // set the "tint" uniform to the value in the member variable tint 
    void TintedMaterial::setup() const {
        //TODO: (Req 6) Write this function
        Material::setup();
        shader->set("tint",tint);
    }

    // This function read the material data from a json object
    void TintedMaterial::deserialize(const nlohmann::json& data){
        Material::deserialize(data);
        if(!data.is_object()) return;
        tint = data.value("tint", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    // This function should call the setup of its parent and
    // set the "alphaThreshold" uniform to the value in the member variable alphaThreshold
    // Then it should bind the texture and sampler to a texture unit and send the unit number to the uniform variable "tex" 
    void TexturedMaterial::setup() const {
        //TODO: (Req 6) Write this function
        TintedMaterial::setup();

        shader->set("alphaThreshold",alphaThreshold);

        texture->bind();

        sampler->bind(0);
        
        shader->set("tex",0);
    }

    // This function read the material data from a json object
    void TexturedMaterial::deserialize(const nlohmann::json& data){
        TintedMaterial::deserialize(data);
        if(!data.is_object()) return;
        alphaThreshold = data.value("alphaThreshold", 0.0f);
        texture = AssetLoader<Texture2D>::get(data.value("texture", ""));
        sampler = AssetLoader<Sampler>::get(data.value("sampler", ""));
    }


    void LitMaterial::setup() const {
        
        TexturedMaterial::setup();
        
        shader->set("lit",0);                  //MISSING MUST BE SURE THAT WE WILL MAKE ANOTHER SHADER lit OR USE tex SHADER
    }

    // This function read the material data from a json object
    void LitMaterial::deserialize(const nlohmann::json& data){
        TexturedMaterial::deserialize(data);
        if(!data.is_object()) return;
        Albedo = AssetLoader<Texture2D>::get(data.value("Albedo", ""));
        Specular = AssetLoader<Texture2D>::get(data.value("Specular", ""));
        Diffuse = AssetLoader<Texture2D>::get(data.value("Diffuse", ""));
        Roughness = AssetLoader<Texture2D>::get(data.value("Roughness", ""));
        Ambient_Occlusion = AssetLoader<Texture2D>::get(data.value("Ambient_Occlusion", ""));
        Emission = AssetLoader<Texture2D>::get(data.value("Emission", ""));
        
        sampler = AssetLoader<Sampler>::get(data.value("sampler", ""));
    }


}