#version 330 core
//#define MAX_LIGHTS 16


in Varyings {
    vec4 color;
    vec2 tex_coord;
    vec3 position;
    vec3 normal;
    vec3 view;
    vec3 world;
} fs_in;

out vec4 frag_color;

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
    float albedo;
    float ambient_occlusion;
    float specular;
    float roughness;
    float emissive;
};



//uniform Light light;
//uniform Material material;


uniform vec4 tint;
uniform sampler2D tex;

void main(){

    Light light;
    Material material;
    float ATTENUATION = 1;


    
    light.type = 1;
    light.position =  vec3(5,5,-7);
    light.direction = vec3(-1,0,0);
    light.diffuse = vec3(0.1,0.1,0.2);
    light.specular = vec3(1.0,0.9,0.7);
    light.ambient = vec3(0.1,0.1,0.1);
    light.attenuation = vec3(1.0,0.0,0.0);


    material.specular = 0.7f; //vec3(0.7,0.7,0.7);
    material.albedo = 0.2f; //vec3(0.2, 0.2, 0.2);
    material.ambient_occlusion = 0.99f; //vec3(0.99, 0.99, 0.99);
    material.roughness = 0.12f; //vec3(0.12, 0.12, 0.12);
    material.emissive = 0.2f; //vec3(0.02, 0.02, 0.02);

    vec3 material_diffuse = texture(material.albedo, fs_in.tex_coord).rgb;
    vec3 material_specular = texture(material.specular, fs_in.tex_coord).rgb;
    vec3 material_ambient = material_diffuse * texture(material.ambient_occlusion, fs_in.tex_coord).r;

   
    float material_roughness = texture(material.roughness, fs_in.tex_coord).r;
    float material_shininess = 2.0 / pow(clamp(material_roughness, 0.001, 0.999), 4.0) - 2.0;

    vec3 material_emissive = texture(material.emissive, fs_in.tex_coord).rgb;

   
    frag_color = vec4(material_emissive + material_ambient, 1.0);

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

    vec3 view = normalize(fs_in.view);
    vec3 normal = normalize(fs_in.normal);
    vec3 reflected = reflect(- direction_to_light, normal);
    vec3 AMBIENT = light.ambient * material_ambient;
    vec3 DIFFUSE = light.diffuse * material_diffuse * max(0, dot(normal, direction_to_light));
    vec3 SPECULAR = light.specular * material_specular * pow(max(0, dot(view, reflected)),material_shininess);

    //frag_color.rgb = AMBIENT + DIFFUSE + SPECULAR;
 //   frag_color.a = 1.0;
    //TODO: (Req 6) Modify the following line to compute the fragment color
    // by multiplying the tint with the vertex color and with the texture color 
    frag_color = tint * fs_in.color  * texture(tex,fs_in.tex_coord) + vec4(AMBIENT + (DIFFUSE + SPECULAR) * ATTENUATION, 1.0);
//    frag_color = fs_in.color + vec4(AMBIENT + (DIFFUSE + SPECULAR) * ATTENUATION, 1.0);
    frag_color.rgb += (DIFFUSE + SPECULAR) * ATTENUATION;
//    frag_color = tint * fs_in.color * texture(tex,fs_in.tex_coord);
}
