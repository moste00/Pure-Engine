#version 330 core



struct DirectionalLight{
    vec3 Direction;
    vec3 Diffuse;
    vec3 Specular;
    vec3 Ambient;
}

struct Material{      //I THINK IT SHOULD BE IN TEXTURE
    vec3 Diffuse;
    vec3 Specular;
    vec3 Ambient;
    float Shininess;
}



in Varyings {
    vec3 position;
    vec4 color;
    vec2 tex_coord;
    vec3 normal;


    //AYMAN
    vec3 view;
} fs_in;

out vec4 frag_color;

uniform int output_type;



uniform DirectionalLight light;
uniform Material material;

void main(){
    // We select the fragment color based on output_type
    // 0 = Position, 1 = Color, 2 = Texture Coordinates, 3 = Normal
    switch(output_type){
        case 0:
        frag_color = vec4(0.5 * fs_in.position + 0.5, 1.0);
        break;

        case 1:
        vec3 View =  normalize(fs_in.view);
        vec3 ambient = light.Ambient * material.Ambient;
        vec3 diffuse = light.Diffuse * material.diffuse * max(0, dot(fs_in.normal, -light.Direction));
        //vec3 lighting = max(0, dot(fs_in.normal, light.Direction));
        vec3 reflected = reflect(light.Direction, fs_in.normal);
        vec3 specular = light.Specular * material.Specular * pow(max(0, dot(View, reflected)), material.Shininess);
        vec3 lighting = ambient + diffuse + specular;
        frag_color = max(0, dot(fs_in.color, lighting));
        break;
        
        case 2:
        frag_color = vec4(fs_in.tex_coord, 0.0, 1.0);
        break;
        
        default:
        frag_color = vec4(0.5 * fs_in.normal + 0.5, 1.0);
        break;
    }
}