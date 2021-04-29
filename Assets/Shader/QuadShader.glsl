#vertex
#version 330 core

layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec2 inTexture;
layout (location = 2) in float inInfo;

out float info;
out vec2 textureCoords;

uniform mat4 ortho;

void main() {
    gl_Position = ortho * vec4(inPosition, 0.0, 1.0);
    textureCoords = inTexture;
    info = inInfo;
}

#fragment
#version 330 core

in float info;
in vec2 textureCoords;

uniform vec4 color;
uniform sampler2D image;

out vec4 FragColor;

void main() {
    if(info == 0)
        FragColor = color;
    else if(info == 1)
        FragColor = texture(image, textureCoords);
}