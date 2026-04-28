#ifndef TWENTYFOUR_CELL_H
#define TWENTYFOUR_CELL_H
#include "geometry.h"
class TwentyFourCell:public Geometry{
    vulkan::Primitive mGeometry;
    vulkan::Primitive mWireframe;
public:
    TwentyFourCell(/* args */);
    ~TwentyFourCell();
    virtual void Cleanup();

    virtual void Draw(vk::CommandBuffer command, vk::PipelineLayout layout);
    virtual void DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout);

    virtual void Update(const void *useData = nullptr);
};
#endif