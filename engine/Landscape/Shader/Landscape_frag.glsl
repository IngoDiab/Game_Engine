#version 330 core

uniform sampler2D mGrassTex;
uniform sampler2D mRockTex;
uniform sampler2D mSnowrockTex;

in vec3 o_position;
in vec2 o_uv;
in float o_height_in_model;

out vec4 FragColor;

void main(){
        vec4 _texelGrass = texture(mGrassTex, o_uv);
        vec4 _texelRock = texture(mRockTex, o_uv);
        vec4 _texelSnowrock = texture(mSnowrockTex, o_uv);
        //vec3 albedoColor = texture(mGrassTex, o_uv).rgb;
        //FragColor = vec4(0.2, 0.2, 0.4, 1.0);
        
        
        // if(o_height_in_model<=65.) FragColor = vec4(0,1,0,1);
        // else if(o_height_in_model>65. && o_height_in_model<=90.) FragColor = vec4(1,1,0,1);
        // else if(o_height_in_model>=90.) FragColor = vec4(1,0,0,1);
        if(o_height_in_model<=65.) FragColor = mix(_texelGrass, _texelRock, o_height_in_model/65.);
        else if(o_height_in_model>65. && o_height_in_model<=90.) FragColor = mix(_texelRock, _texelSnowrock, (o_height_in_model-65.)/(90.-65.));
        else if(o_height_in_model>90.) FragColor = mix(_texelRock, _texelSnowrock, max(1,(o_height_in_model-90.)/(100.-90.)));
}