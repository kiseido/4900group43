#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective


class Transform
{
public:
    Transform();
    ~Transform();

    bool change = true;

    Transform *parent = 0;

    glm::mat4 tNet;
    glm::vec3 position = glm::vec3(0.0);
    glm::vec3 scale = glm::vec3(1.0);
    glm::vec3 rotation = glm::vec3(0.0);

private:
};
