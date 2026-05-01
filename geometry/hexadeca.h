#ifndef SIXTEEN_CELL_H
#define SIXTEEN_CELL_H
#include "geometry.h"
//-choron
class Hexadeca:public Geometry{
    vulkan::Primitive mGeometry;
    vulkan::Primitive mWireframe;
public:
    Hexadeca(/* args */);
    ~Hexadeca();
    virtual void Cleanup();

    virtual void Draw(vk::CommandBuffer command, vk::PipelineLayout layout);
    virtual void DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout);

    virtual void Update(const void *useData = nullptr);
};
#endif