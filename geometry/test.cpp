#include "test.h"
GeometryTest::GeometryTest(/* args */){
}

GeometryTest::~GeometryTest(){
}
void GeometryTest::Cleanup(){
    mGeometry.Destroy(*gpu.device);
    mWireframe.Destroy(*gpu.device);
}

void GeometryTest::Draw(vk::CommandBuffer command, vk::PipelineLayout layout){
    mGeometry.Bind(command);
    mGeometry.Draw(command);
}

void GeometryTest::DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout){
    mWireframe.Bind(command);
    mWireframe.Draw(command);
}

void GeometryTest::Update(){
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;
    Vertex v;
    v.color = glm::vec3(0, 1, 0);
    v.pos = glm::vec4(0);
    vertices.push_back(v);
    v.pos = glm::vec4(0, 1, 0, 0);
    vertices.push_back(v);

    v.color = glm::vec3(1, 0, 0);
    v.pos = glm::vec4(0);
    vertices.push_back(v);
    v.pos = glm::vec4(1, 0, 0, 0);
    vertices.push_back(v);

    v.color = glm::vec4(0, 0, 1, 0);
    v.pos = glm::vec4(0);
    vertices.push_back(v);
    v.pos = glm::vec4(0, 0, 1, 0);
    vertices.push_back(v);

    v.color = glm::vec3(1);
    v.pos = glm::vec4(0);//w轴必须在某种视角下才能看到
    vertices.push_back(v);
    v.pos = glm::vec4(0, 0, 0, 1);
    vertices.push_back(v);
    if(!mGeometry.IsVaildIndex() || !mGeometry.IsVaildVertex()){
        // mGeometry.CreateIndexBuffer(*gpu.device, indices.data(), sizeof(uint16_t) * indices.size(), gpu.graphics, *gpu.pool);
        mGeometry.CreateVertexBuffer(*gpu.device, vertices.data(), sizeof(Vertex) * vertices.size(), vertices.size(), gpu.graphics, *gpu.pool);
    }
    else{
        // mGeometry.UpdateIndexData(*gpu.device, indices.data(), gpu.graphics, *gpu.pool);
        mGeometry.UpdateVertexData(*gpu.device, vertices.data(), gpu.graphics, *gpu.pool);
    }
    // indices = generatePentatopeEdges();
    if(!mWireframe.IsVaildIndex() || !mWireframe.IsVaildVertex()){
        // mWireframe.CreateIndexBuffer(*gpu.device, indices.data(), sizeof(uint16_t) * indices.size(), gpu.graphics, *gpu.pool);
        mWireframe.CreateVertexBuffer(*gpu.device, vertices.data(), sizeof(Vertex) * vertices.size(), vertices.size(), gpu.graphics, *gpu.pool);
    }
    else{
        // mWireframe.UpdateIndexData(*gpu.device, indices.data(), gpu.graphics, *gpu.pool);
        mWireframe.UpdateVertexData(*gpu.device, vertices.data(), gpu.graphics, *gpu.pool);
    }
}