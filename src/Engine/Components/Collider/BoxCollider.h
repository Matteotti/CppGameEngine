#pragma once
#include "Collider.h"

#include <vector>

class BoxCollider : public Collider
{
private:
    glm::vec3 _center;
    glm::vec3 _horizontal;
    glm::vec3 _vertical;
    glm::vec3 _depth;

    std::vector<glm::vec3> _vertices;
    std::vector<glm::vec3> _axis;

    void UpdateVertices();
    void UpdateAxis();

public:
    BoxCollider();

    void SetSize(glm::vec3 size);
    void SetCenter(glm::vec3 center);

    std::vector<glm::vec3> GetVertices();
    std::vector<glm::vec3> GetAxis();

    glm::vec3 GetSize();
    glm::vec3 GetCenter();

    virtual bool CheckCollision(std::shared_ptr<Collider> other) override;
    virtual void Update() override;
};