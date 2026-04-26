#ifndef TEST_H
#define TEST_H
#include "geometry.h"
class GeometryTest:public Geometry{
    vulkan::Primitive mGeometry;
    vulkan::Primitive mWireframe;
public:
    GeometryTest(/* args */);
    ~GeometryTest();
    virtual void Cleanup();

    virtual void Draw(vk::CommandBuffer command, vk::PipelineLayout layout);
    virtual void DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout);

    virtual void Update();
};
#endif