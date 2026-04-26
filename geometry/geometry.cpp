#include "geometry.h"
Geometry::Geometry(/* args */){
}

Geometry::~Geometry(){
}

void Geometry::Setup(const vulkan::Device &device, vk::Queue graphics, const vulkan::Pool &pool){
    gpu.pool = &pool;
    gpu.device = &device;
    gpu.graphics = graphics;
}
