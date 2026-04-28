#ifndef KLEIN_BOTTLE_H
#define KLEIN_BOTTLE_H
#include "geometry.h"
class KleinBottle:public Geometry{
    vulkan::Primitive mKleinBottle;
public:
    KleinBottle(/* args */);
    ~KleinBottle();

    virtual void Cleanup();

    virtual void Draw(vk::CommandBuffer command, vk::PipelineLayout layout);
    virtual void DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout);

    virtual void Update(const void *useData = nullptr);
};
#endif