#vertex
#version 430 core

layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec2 inTexture;
layout (location = 2) in vec3 inRounding;
layout (location = 3) in vec4 inInfo;

out vec4 info;
out vec2 textureCoords;
out vec2 roundingCoords;
out float corners;

uniform mat4 ortho;

void main() {
    gl_Position = ortho * vec4(inPosition, 0.0, 1.0);
    textureCoords = inTexture;
    roundingCoords = inRounding.xy * inInfo.zw;
    corners = inRounding.z;
    info = inInfo;
};

#fragment
#version 430 core

#define PI 3.1415926538

in vec4 info;
in vec2 textureCoords;
in vec2 roundingCoords;
in float corners;

uniform float smoothness;
uniform vec4 color;
uniform sampler2D image;

out vec4 FragColor;

float mask (vec2 size, vec2 pos, vec2 radius) {
    float dz = 10.0/min(size.x,size.y);
    float r = length(pos);
    float d = smoothstep(radius.y-dz,radius.y,r) + smoothstep(radius.x+dz,radius.x,r);
    return (1.0-d) * step(radius.x,r) * step(r,radius.y);
}

vec2 plot (vec2 position, vec2 theta) {
    float th = min(theta.y,max(theta.x,position.x));
    vec2 pos = vec2(cos(th),sin(th)) * 2.0 * position.y;
    float x = max(abs(pos.x),abs(pos.y))-0.001;
return pos/x;
}

void main() {
        vec2 uv = textureCoords * 2.0 - 1.0;

        float R = 1.0;
        float R2 = 0.5;
        float dist = sqrt(dot(uv,uv));
        float sm = smoothstep(R,R-0.01,dist);
        float sm2 = smoothstep(R2,R2+0.01,dist);
        float alpha = sm*sm2;


        float g = uv.y / dist;
        float sector = 0.5 + g / 2.0;
        bool s = 0.25 > sector && 0.75 < sector;
        FragColor = vec4(0.5, 0.5, 0.5, alpha * float(s));
        FragColor = vec4(0.5, 0.5, 0.5, alpha * sector);
};
