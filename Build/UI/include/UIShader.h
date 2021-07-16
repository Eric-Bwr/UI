#pragma once

const char* UIQuadShaderVertex = "#version 400 core\n"
                                 "\n"
                                 "layout (location = 0) in vec2 inPosition;\n"
                                 "layout (location = 1) in vec2 inTexture;\n"
                                 "layout (location = 2) in vec3 inRounding;\n"
                                 "layout (location = 3) in vec4 inInfo;\n"
                                 "\n"
                                 "out vec4 info;\n"
                                 "out vec2 textureCoords;\n"
                                 "out vec2 roundingCoords;\n"
                                 "out float corners;\n"
                                 "\n"
                                 "uniform mat4 ortho;\n"
                                 "\n"
                                 "void main() {\n"
                                 "    gl_Position = ortho * vec4(inPosition, 0.0, 1.0);\n"
                                 "    textureCoords = inTexture;\n"
                                 "    roundingCoords = inRounding.xy * inInfo.zw;\n"
                                 "    corners = inRounding.z;\n"
                                 "    info = inInfo;\n"
                                 "}";

const char* UIQuadShaderFragment = "#version 400 core\n"
                                   "\n"
                                   "in vec4 info;\n"
                                   "in vec2 textureCoords;\n"
                                   "in vec2 roundingCoords;\n"
                                   "in float corners;\n"
                                   "\n"
                                   "uniform float smoothness;\n"
                                   "uniform vec4 color;\n"
                                   "uniform sampler2D image;\n"
                                   "uniform vec2 resizeFactor;\n"
                                   "\n"
                                   "out vec4 FragColor;\n"
                                   "\n"
                                   "float roundCorners(float alpha){\n"
                                   "    vec4 radii = vec4(int(corners) >> 3 & 1, int(corners) >> 2 & 1, int(corners) & 1, int(corners) >> 1& 1) * info.y;\n"
                                   "    float yMaxY = info.w - radii.y * resizeFactor.x;\n"
                                   "    float xMaxZ = info.z - radii.z * resizeFactor.y;\n"
                                   "    float yMaxZ = info.w - radii.z * resizeFactor.x;\n"
                                   "    float xMaxW = info.z - radii.w * resizeFactor.y;\n"
                                   "    if (roundingCoords.x < radii.x && roundingCoords.y < radii.x)\n"
                                   "        alpha *= 1.0 - smoothstep(radii.x - smoothness, radii.x + smoothness, length(roundingCoords - vec2(radii.x)));\n"
                                   "    else if (roundingCoords.x < radii.y && roundingCoords.y > yMaxY)\n"
                                   "        alpha *= 1.0 - smoothstep(radii.y - smoothness, radii.y + smoothness, length(roundingCoords - vec2(radii.y, yMaxY)));\n"
                                   "    else if (roundingCoords.x > xMaxZ && roundingCoords.y > yMaxZ)\n"
                                   "        alpha *= 1.0 - smoothstep(radii.z - smoothness, radii.z + smoothness, length(roundingCoords - vec2(xMaxZ, yMaxZ)));\n"
                                   "    else if (roundingCoords.x > xMaxW && roundingCoords.y < radii.w)\n"
                                   "        alpha *= 1.0 - smoothstep(radii.w - smoothness, radii.w + smoothness, length(roundingCoords - vec2(xMaxW, radii.w)));\n"
                                   "    return alpha;\n"
                                   "}\n"
                                   "\n"
                                   "void main() {\n"
                                   "    if (info.x == 0 || info.x == 1)\n"
                                   "        FragColor = color;\n"
                                   "    else if (info.x == 2)\n"
                                   "        FragColor = texture(image, textureCoords);\n"
                                   "    else if (info.x == 3)\n"
                                   "        FragColor = texture(image, textureCoords) * color;\n"
                                   "    FragColor = vec4(FragColor.rgb, roundCorners(FragColor.a));\n"
                                   "}";

const char* UITextShaderVertex = "#version 330 core\n"
                                 "\n"
                                 "layout (location = 0) in vec2 inPosition;\n"
                                 "layout (location = 1) in vec2 inTexture;\n"
                                 "layout (location = 2) in float inLevel;\n"
                                 "\n"
                                 "uniform mat4 ortho;\n"
                                 "\n"
                                 "out vec2 textureCoords;\n"
                                 "out float level;\n"
                                 "\n"
                                 "void main() {\n"
                                 "    gl_Position = ortho * vec4(inPosition, 0.0, 1.0);\n"
                                 "    textureCoords = inTexture;\n"
                                 "    level = inLevel;\n"
                                 "}";

const char* UITextShaderFragment = "#version 330 core\n"
                                   "\n"
                                   "in vec2 textureCoords;\n"
                                   "in float level;\n"
                                   "\n"
                                   "uniform sampler2DArray image;\n"
                                   "uniform vec4 color;\n"
                                   "\n"
                                   "out vec4 FragColor;\n"
                                   "\n"
                                   "void main() {\n"
                                   "    FragColor = vec4(color.rgb, texture(image, vec3(textureCoords, level - 32)).r * color.a);\n"
                                   "}";