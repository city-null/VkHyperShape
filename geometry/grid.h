#ifndef GRID_H
#define GRID_H
#include "geometry.h"
class Grid3D:public Geometry{
    vulkan::Primitive mGrid;
public:
    Grid3D(/* args */) = default;
    ~Grid3D() = default;

    virtual void Cleanup();

    virtual void Draw(vk::CommandBuffer command, vk::PipelineLayout layout);
    virtual void DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout);

    virtual void Update(const void *useData = nullptr);
};
class Grid4D:public Geometry{
    vulkan::Primitive mGrid;
public:
    Grid4D(/* args */) = default;
    ~Grid4D() = default;

    virtual void Cleanup();

    virtual void Draw(vk::CommandBuffer command, vk::PipelineLayout layout);
    virtual void DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout);

    virtual void Update(const void *useData = nullptr);
};
#endif