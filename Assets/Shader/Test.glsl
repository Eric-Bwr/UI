#vertex
#version 330 core

layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec2 inTexture;
layout (location = 2) in float inLevel;

uniform mat4 ortho;
uniform mat4 model;

out vec2 textureCoords;
out float level;

void main() {
    gl_Position = ortho * vec4(inPosition, 0.0, 1.0);
    textureCoords = inTexture;
    level = inLevel;
}

#fragment
#version 330 core

in vec2 textureCoords;
in float level;

uniform sampler2DArray image;
uniform vec3 color = vec3(1.0, 0.0, 1.0);

out vec4 FragColor;

void main() {
    FragColor = vec4(color, 1.0) * texture(image, vec3(textureCoords, level - 32)).r;
    //FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}