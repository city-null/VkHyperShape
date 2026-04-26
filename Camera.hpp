#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "vulkan/buffer.hpp"

class Camera {
public:
    Camera(float distance = 1.0f) : m_distance(distance), m_center(0.0f), m_rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)){
        UpdatePosition();
    }

    void CreateUniform(const vulkan::Device& device) {
        m_uniform.Create(device, sizeof(glm::mat4), vk::BufferUsageFlagBits::eUniformBuffer, vma::MemoryUsage::eCpuOnly, true);
    }

    void DestroyUniform(const vulkan::Device& device) {
        m_uniform.Destroy(device);
    }

    void ProcessMouseMovement(float deltaX, float deltaY, float sensitivity = 0.005f) {
        if (deltaX == 0.0f && deltaY == 0.0f) return;

        glm::quat pitchQuat = glm::angleAxis(-deltaY * sensitivity, glm::vec3(1, 0, 0));
        glm::quat yawQuat = glm::angleAxis(-deltaX * sensitivity, glm::vec3(0, 1, 0));

        glm::quat deltaRot = yawQuat * pitchQuat;

        m_rotation = m_rotation * deltaRot;

        m_rotation = glm::normalize(m_rotation);
        UpdatePosition();
    }

    void ProcessRoll(float deltaRoll, float sensitivity = 0.005f) {
        if (deltaRoll == 0.0f) return;

        const glm::vec3 forward = m_rotation * glm::vec3(0.0f, 0.0f, -1.0f);
        const glm::quat rollRot = glm::angleAxis(deltaRoll * sensitivity, forward);

        m_rotation = rollRot * m_rotation;
        m_rotation = glm::normalize(m_rotation);

        UpdatePosition();
    }

    void ProcessMouseScroll(float yoffset, float minDist = 0.1f, float maxDist = 100.0f) {
        m_distance = glm::clamp(m_distance - yoffset * 0.1f, minDist, maxDist);
        UpdatePosition();
    }

    void Pan(const glm::vec2& delta, float sensitivity = 0.01f) {
        const glm::vec3 right = m_rotation * glm::vec3(1.0f, 0.0f, 0.0f);
        const glm::vec3 up = m_rotation * glm::vec3(0.0f, 1.0f, 0.0f);

        m_center += right * delta.x * sensitivity * m_distance;
        m_center -= up * delta.y * sensitivity * m_distance;

        UpdatePosition();
    }

    void MoveCenter(const glm::vec3& offset) {
        m_center += offset;
        UpdatePosition();
    }

    void SetCenter(const glm::vec3& center) {
        m_center = center;
        UpdatePosition();
    }

    void SetDistance(float distance) {
        m_distance = distance;
        UpdatePosition();
    }

    void SetRotation(const glm::quat& rotation) {
        m_rotation = glm::normalize(rotation);
        UpdatePosition();
    }

    glm::mat4 GetView() const {
        return m_view;
    }

    glm::vec3 GetPosition() const {
        return m_position;
    }

    glm::vec3 GetCenter() const {
        return m_center;
    }

    glm::quat GetRotation() const {
        return m_rotation;
    }

    float GetDistance() const {
        return m_distance;
    }

    glm::vec3 GetRight() const { return m_rotation * glm::vec3(1.0f, 0.0f, 0.0f); }
    glm::vec3 GetUp() const { return m_rotation * glm::vec3(0.0f, 1.0f, 0.0f); }
    glm::vec3 GetForward() const { return m_rotation * glm::vec3(0.0f, 0.0f, -1.0f); }

    const auto& GetUniform() const noexcept {
        return m_uniform;
    }

    void UpdateUniform(const vulkan::Device& device) {
        m_uniform.UpdateData(device, &m_view);
    }

private:
    glm::quat m_rotation;// 摄像机朝向
    glm::vec3 m_center;
    float m_distance;

    glm::vec3 m_position;
    glm::mat4 m_view;

    vulkan::Buffer m_uniform;

    void UpdatePosition() {
        // 从四元数计算"后"方向（摄像机在中心后方）
        // m_rotation * (0,0,-1) 表示旋转后的"前"方向，取反得到从center到position的方向
        const glm::vec3 back = m_rotation * glm::vec3(0.0f, 0.0f, 1.0f);
        m_position = m_center + back * m_distance;

        UpdateViewMatrix();
    }

    void UpdateViewMatrix() {
        const glm::vec3 up = m_rotation * glm::vec3(0.0f, 1.0f, 0.0f);
        m_view = glm::lookAt(m_position, m_center, up);
    }
};
// class Camera4D {
// public:
//     Camera4D(float distance = 2.0f)
//         : m_distance(distance)
//         , m_center(0.0f, 0.0f, 0.0f, 0.0f)
//         , m_rotation(mglm::mat5(1.0f))
//     {
//         UpdatePosition();
//     }

//     void DestroyUniform(const vulkan::Device& device) {
//         m_uniform.Destroy(device);
//     }

//     // 鼠标X：在当前局部XY平面旋转（水平观察）
//     // 鼠标Y：在当前局部ZW平面旋转（垂直观察）
//     // 鼠标Z：在当前局部XW平面旋转（深度旋转）
//     void ProcessMouse3D(float deltaX, float deltaY, float deltaZ, float sensitivity = 0.01f) {
//         if (deltaX == 0 && deltaY == 0 && deltaZ == 0) return;

//         mglm::vec4 localX = GetLocalAxis(0);
//         mglm::vec4 localY = GetLocalAxis(1);
//         mglm::vec4 localZ = GetLocalAxis(2);
//         mglm::vec4 localW = GetLocalAxis(3);

//         // 构造局部旋转平面
//         mglm::Plane planeXY(localX, localY);
//         mglm::Plane planeZW(localZ, localW);
//         mglm::Plane planeXW(localX, localW);

//         float angleXY = -deltaX * sensitivity;
//         float angleZW = -deltaY * sensitivity;
//         float angleXW = deltaZ * sensitivity;

//         mglm::mat5 rotXY = mglm::rotate(planeXY, angleXY);
//         mglm::mat5 rotZW = mglm::rotate(planeZW, angleZW);
//         mglm::mat5 rotXW = mglm::rotate(planeXW, angleXW);

//         // 顺序:先XW，再ZW，最后XY
//         m_rotation = m_rotation * rotXW * rotZW * rotXY;

//         OrthogonalizeRotation();

//         UpdatePosition();
//     }

//     void ProcessMouseMovement(float deltaX, float deltaY, float sensitivity = 0.01f) {
//         if (deltaX == 0 && deltaY == 0) return;

//         mglm::vec4 localX = GetLocalAxis(0);
//         mglm::vec4 localY = GetLocalAxis(1);
//         mglm::vec4 localZ = GetLocalAxis(2);
//         mglm::vec4 localW = GetLocalAxis(3);

//         // X在XY平面旋转，Y在ZW平面旋转
//         mglm::Plane planeXY(localX, localY);
//         mglm::Plane planeZW(localZ, localW);

//         float angleXY = -deltaX * sensitivity;
//         float angleZW = -deltaY * sensitivity;

//         mglm::mat5 rotXY = mglm::rotate(planeXY, angleXY);
//         mglm::mat5 rotZW = mglm::rotate(planeZW, angleZW);

//         // 局部旋转：右乘
//         m_rotation = m_rotation * rotZW * rotXY;

//         OrthogonalizeRotation();
//         UpdatePosition();
//     }

//     // 在指定局部平面上旋转（用于键盘控制）
//     void RotateInPlane(int axis1, int axis2, float angle) {
//         // axis1, axis2: 0=X, 1=Y, 2=Z, 3=W
//         mglm::vec4 a1 = GetLocalAxis(axis1);
//         mglm::vec4 a2 = GetLocalAxis(axis2);

//         mglm::Plane plane(a1, a2);
//         mglm::mat5 rot = mglm::rotate(plane, angle);

//         // 局部旋转
//         m_rotation = m_rotation * rot;
//         OrthogonalizeRotation();
//         UpdatePosition();
//     }

//     // 全局平面旋转（绕世界坐标轴）
//     void RotateInWorldPlane(int planeIndex, float angle) {
//         // 使用预定义的平面
//         const mglm::Plane* planes[] = {
//             &mglm::planes::XY,
//             &mglm::planes::XZ,
//             &mglm::planes::XW,
//             &mglm::planes::YZ,
//             &mglm::planes::YW,
//             &mglm::planes::ZW
//         };

//         if (planeIndex >= 0 && planeIndex < 6) {
//             mglm::mat5 rot = mglm::rotate(*planes[planeIndex], angle);
//             // 全局旋转：左乘
//             m_rotation = rot * m_rotation;
//             OrthogonalizeRotation();
//             UpdatePosition();
//         }
//     }

//     void ProcessMouseScroll(float yoffset, float minDist = 0.1f, float maxDist = 50.0f) {
//         m_distance = std::clamp(m_distance - yoffset * 0.1f, minDist, maxDist);
//         UpdatePosition();
//     }

//     // 在局部坐标系中平移
//     void Pan(float right, float up, float forward, float ana, float sensitivity = 0.01f) {
//         m_center += GetLocalAxis(0) * right * sensitivity;
//         m_center += GetLocalAxis(1) * up * sensitivity;
//         m_center += GetLocalAxis(2) * forward * sensitivity;
//         m_center += GetLocalAxis(3) * ana * sensitivity;
//         UpdatePosition();
//     }

//     void SetCenter(const mglm::vec4& center) {
//         m_center = center;
//         UpdatePosition();
//     }

//     void SetDistance(float distance) {
//         m_distance = distance;
//         UpdatePosition();
//     }

//     // 直接设置旋转（用于初始化或动画）
//     void SetRotation(const mglm::mat5& rotation) {
//         m_rotation = rotation;
//         OrthogonalizeRotation();
//         UpdatePosition();
//     }

//     mglm::mat5 GetView() const { return m_view; }
//     mglm::mat5 GetRotation() const { return m_rotation; }
//     mglm::vec4 GetPosition() const { return m_position; }
//     mglm::vec4 GetCenter() const { return m_center; }

// private:
//     float m_distance;
//     mglm::vec4 m_center;
//     mglm::vec4 m_position;
//     mglm::mat5 m_rotation;  // 核心：直接使用5x5旋转矩阵
//     mglm::mat5 m_view;
//     vulkan::Buffer m_uniform;

//     mglm::vec4 GetLocalAxis(int index) const {
//         // 旋转矩阵的列就是局部基向量
//         return mglm::vec4(
//             m_rotation[index][0],
//             m_rotation[index][1],
//             m_rotation[index][2],
//             m_rotation[index][3]
//         );
//     }

//     void UpdatePosition() {
//         // 默认朝向：-W方向（第四维）
//         mglm::vec5 offset(0.0f, 0.0f, 0.0f, m_distance, 0.0f);
//         mglm::vec5 rotated = m_rotation * offset;
//         m_position = m_center - mglm::vec4(rotated.x, rotated.y, rotated.z, rotated.w);
//         UpdateViewMatrix();
//     }

//     void UpdateViewMatrix() {
//         // 提取局部轴用于lookAt
//         mglm::vec4 forward = GetLocalAxis(3);
//         forward = mglm::vec4(-forward.x, -forward.y, -forward.z, -forward.w);
//         mglm::vec4 up = GetLocalAxis(1);
//         mglm::vec4 over = GetLocalAxis(2);

//         m_view = mglm::lookAt(m_position, m_center, up, over);
//     }

//     void OrthogonalizeRotation() {
//         mglm::vec4 c0 = GetLocalAxis(0);
//         mglm::vec4 c1 = GetLocalAxis(1);
//         mglm::vec4 c2 = GetLocalAxis(2);
//         mglm::vec4 c3 = GetLocalAxis(3);

//         // 正交化
//         c0 = mglm::normalize(c0);

//         c1 = c1 - c0 * mglm::dot(c0, c1);
//         c1 = mglm::normalize(c1);

//         c2 = c2 - c0 * mglm::dot(c0, c2) - c1 * mglm::dot(c1, c2);
//         c2 = mglm::normalize(c2);

//         c3 = c3 - c0 * mglm::dot(c0, c3) - c1 * mglm::dot(c1, c3) - c2 * mglm::dot(c2, c3);
//         c3 = mglm::normalize(c3);

//         // 写回矩阵
//         for (int i = 0; i < 4; ++i) {
//             m_rotation[0][i] = c0[i];
//             m_rotation[1][i] = c1[i];
//             m_rotation[2][i] = c2[i];
//             m_rotation[3][i] = c3[i];
//         }
//     }
// };
#endif