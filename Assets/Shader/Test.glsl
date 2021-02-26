#vertex
#version 330

layout (location = 0) in vec2 inPosition;

out vec2 textureCoords;

void main() {
    gl_Position = vec4(inPosition, 0.0, 1.0);
    textureCoords = (inPosition + 1.0) / 2.0;
}

    #fragment

    #version 330

in vec2 textureCoords;

uniform sampler2D image;

out vec4 FragColor;

void main() {
    if(texture(image, textureCoords).a > 0.8)
    FragColor = vec4(1.0, 0.0, 1.0, 1.0 );
    else
    FragColor = vec4(1.0, 1.0, 1.0, 1.0 );
    FragColor = vec4(0.0, 0.0, 1.0, texture(image, textureCoords).a);
}