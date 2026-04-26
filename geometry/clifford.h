#ifndef CLIFFORD_H
#define CLIFFORD_H
#include "geometry.h"
class Clifford:public Geometry{
    vulkan::Primitive mGeometry;
    vulkan::Primitive mWireframe;
public:
    Clifford(/* args */);
    ~Clifford();
    virtual void Cleanup();

    virtual void Draw(vk::CommandBuffer command, vk::PipelineLayout layout);
    virtual void DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout);

    virtual void Update();
};
#endif