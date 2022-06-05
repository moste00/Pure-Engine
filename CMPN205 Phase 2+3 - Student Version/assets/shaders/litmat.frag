#version 330 core

in Varyings {
    vec4 color;
    vec2 tex_coord;
    vec3 position;
    vec3 normal;
    vec3 view;
    vec3 world;
} fs_in;

out vec4 frag_color;
out vec4 frag_color_light;



struct Light {
    int type;                     //0 -> Directional , 1 -> POINT, 2 -> SPOT
    vec3 position;
    vec3 ambient;
    vec3 direction;
    vec3 diffuse;
    vec3 specular;
    vec3 attenuation; // x*d^2 + y*d + z
    vec2 cone_angles; // x: inner_angle, y: outer_angle
};

struct Material{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    float shininess;
};

uniform vec4 tint;
uniform sampler2D tex;

uniform int lightType;                     //0 -> Directional , 1 -> POINT, 2 -> SPOT
uniform vec3 lightPosition;
uniform vec3 lightAmbient;
uniform vec3 lightDirection;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;
uniform vec3 lightAttenuation; // x*d^2 + y*d + z
uniform vec2 lightConeAngles; // x: inner_angle, y: outer_angle



void main(){
    Light light;
    Material material;

    float ATTENUATION = 1;

       
    light.type = 1;
    light.position =  vec3(0,1,9);
    light.direction = vec3(0,-1,1);
    light.diffuse = vec3(0.1,0.1,0.2);
    light.specular = vec3(1.0,0.9,0.7);
    light.ambient = vec3(0.4,0.4,0.4);
    light.attenuation = vec3(0.5,0.0,0.0);


    material.diffuse = vec3(0.1,0.1,0.2);
    material.specular = vec3(1.0,0.9,0.7);
    material.ambient = vec3(0.4,0.4,0.4);
    material.shininess = 20.0f;


    vec3 view = normalize(fs_in.view);
    vec3 normal = normalize(fs_in.normal);
  

    vec3 direction_to_light = - light.direction;

    if(light.type != 0)
    {
        direction_to_light = normalize(light.position - fs_in.world);
        float d = distance(light.position, fs_in.world);
        ATTENUATION /= dot(light.attenuation, vec3(d*d, d, 1));
        if(light.type == 2)
        {
            float angle = acos(dot(-direction_to_light, light.direction));
            ATTENUATION *= smoothstep(light.cone_angles.y, light.cone_angles.x, angle);
        }
    }


  
    vec3 reflected = reflect( - direction_to_light, normal);
    vec3 AMBIENT = light.ambient * material.ambient;
    vec3 DIFFUSE = light.diffuse * material.diffuse * max(0, dot(normal, direction_to_light));
    vec3 SPECULAR = light.specular * material.specular * pow(max(0, dot(view, reflected)), material.shininess);

    vec4 LIGHTING = vec4((AMBIENT + DIFFUSE + SPECULAR) * ATTENUATION, 1.0);

    //TODO: (Req 6) Modify the following line to compute the fragment color
    // by multiplying the tint with the vertex color and with the texture color    
    frag_color = tint *  fs_in.color * LIGHTING; //* texture(tex,fs_in.tex_coord);//
}