#ifndef CYLINDRICAL_H
#define CYLINDRICAL_H
#include <vector>
#include "geometry.h"
class Cylindrical:public Geometry{
    int circleSegments = 32;
    int heightSegments = 4;
    int wSegments = 4;
    float radius = 1;
    float height = 2;
    float wLength = 2;
    vulkan::Primitive mGeometry;
    vulkan::Primitive mWireframe;
public:
    Cylindrical(/* args */);
    ~Cylindrical();
    virtual void Cleanup();

    virtual void Draw(vk::CommandBuffer command, vk::PipelineLayout layout);
    virtual void DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout);

    virtual void Update();
};
#endif