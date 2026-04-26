#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 inColor;  // 四维顶点坐标

layout(location = 0) out vec4 outColor;

void main() {
    // outColor = texture(inTex, inColor);
    outColor = vec4(inColor, 1.0);
}