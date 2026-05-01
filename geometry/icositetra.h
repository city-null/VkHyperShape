#ifndef TWENTYFOUR_CELL_H
#define TWENTYFOUR_CELL_H
#include "geometry.h"
//-choron
class Icositetra:public Geometry{
    vulkan::Primitive mGeometry;
    vulkan::Primitive mWireframe;
public:
    Icositetra(/* args */);
    ~Icositetra();
    virtual void Cleanup();

    virtual void Draw(vk::CommandBuffer command, vk::PipelineLayout layout);
    virtual void DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout);

    virtual void Update(const void *useData = nullptr);
};
#endif