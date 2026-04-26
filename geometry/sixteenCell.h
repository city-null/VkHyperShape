#ifndef SIXTEEN_CELL_H
#define SIXTEEN_CELL_H
#include "geometry.h"
class SixteenCell:public Geometry{
    vulkan::Primitive mGeometry;
    vulkan::Primitive mWireframe;
public:
    SixteenCell(/* args */);
    ~SixteenCell();
    virtual void Cleanup();

    virtual void Draw(vk::CommandBuffer command, vk::PipelineLayout layout);
    virtual void DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout);

    virtual void Update();
};
#endif