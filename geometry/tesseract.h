#ifndef VULKAN_DEMO_H
#define VULKAN_DEMO_H
#include "geometry.h"
#define TESSERACT_POSITIVE .5f
#define TESSERACT_NEGATIVE -TESSERACT_POSITIVE
class Tesseract:public Geometry{
    vulkan::Primitive mTesseract;
    vulkan::Primitive mWireframe;

    void CreateTesseract();
    void CreateWireframe();
public:
    Tesseract(/* args */);
    ~Tesseract();

    virtual void Cleanup();

    virtual void Draw(vk::CommandBuffer command, vk::PipelineLayout layout);
    virtual void DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout);

    virtual void Update();
};
#endif