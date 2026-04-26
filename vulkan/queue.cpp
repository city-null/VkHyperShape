#include "queue.hpp"
namespace vulkan{
    void Queue::CreateQueue(const Device&device){
        // queueFamilies[3] = device.GetVideoQueueFamiliesIndex();
        queueFamilies[0] = device.GetQueueFamiliesIndex(vk::QueueFlagBits::eGraphics);
        queueFamilies[1] = device.GetQueueFamiliesIndex(vk::QueueFlagBits::eCompute);

        // if(queueFamilies[3] != -1)video = device.device.getQueue(queueFamilies[3], 1);
        vk::Device dev = device;
        if(queueFamilies[0] != -1)present = dev.getQueue(queueFamilies[0], 0);
        if(queueFamilies[1] != -1)graphics = dev.getQueue(queueFamilies[1], 0);
        if(queueFamilies[2] != -1)compute = dev.getQueue(queueFamilies[2], 0);
    }
    void Queue::CreateQueue(const Device&device, vk::SurfaceKHR surface){
        queueFamilies[2] = device.GetQueueFamiliesIndex(surface);
        CreateQueue(device);
    }
}