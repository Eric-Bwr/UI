#vertex
#version 330 core

layout (location = 0) in vec2 inPosition;
layout (location = 1) in int inLevel;

uniform mat4 ortho;
uniform mat4 model;

out vec2 textureCoords;
out int level;

void main() {
   //ENTIRE SCREEN
    gl_Position = vec4(inPosition, 0.0, 1.0);
   //DEFINED BY MODEL MATRIX IN MAIN
   // gl_Position = ortho * model * vec4(inPosition, 0.0, 1.0);
    textureCoords = (inPosition + 1.0) / 2.0;
    textureCoords.y = 1 - textureCoords.y;
    level = inLevel;
}

    #fragment

    #version 330 core

in vec2 textureCoords;
in flat int level;

uniform sampler2DArray image;

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.0, 1.0, 1.0) * texture(image, vec3(textureCoords, level - 32)).r;
   //if (texture(image, textureCoords).a > 0.7)
   //    FragColor = vec4(1.0, 0.0, 1.0, 1.0);
   //else
   //    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}