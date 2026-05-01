#ifndef HYPER_SPHERE_H
#define HYPER_SPHERE_H
#include "geometry.h"
class Hypersphere:public Geometry{
    vulkan::Primitive mWireframe;
    vulkan::Primitive mHypersphere;
public:
    Hypersphere(/* args */);
    ~Hypersphere();
    virtual void Cleanup();

    virtual void Draw(vk::CommandBuffer command, vk::PipelineLayout layout);
    virtual void DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout);

    virtual void Update(const void *useData = nullptr);
};
class Sphere:public Geometry{
    vulkan::Primitive mSphere;
    vulkan::Primitive mWireframe;
public:
    Sphere(/* args */);
    ~Sphere();
    virtual void Cleanup();

    virtual void Draw(vk::CommandBuffer command, vk::PipelineLayout layout);
    virtual void DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout);

    virtual void Update(const void *useData = nullptr);
};
#endif