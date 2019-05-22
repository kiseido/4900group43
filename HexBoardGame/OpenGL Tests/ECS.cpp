#include "ECS.h"

#include "glm/gtc/matrix_transform.hpp"

//glm::vec3 operator+(const glm::vec3& left, const glm::vec3& right) {
//	glm::vec3 out = { 0,0,0 };
//	out.x = left.x + right.x;
//	out.x = left.y + right.y;
//	out.x = left.z + right.z;
//	return out;
//}
//glm::vec3 operator*(const glm::vec3& left, const glm::vec3& right) {
//	glm::vec3 out = { 0,0,0 };
//	out.x = left.x * right.x;
//	out.x = left.y * right.y;
//	out.x = left.z * right.z;
//	return out;
//}

glm::vec3 operator*(const glm::vec3& left, const float right) {
	glm::vec3 out = { 0,0,0 };
	out.x = left.x * right;
	out.x = left.y * right;
	out.x = left.z * right;
	return out;
}

namespace ECS {



	EntityID Entity::NEXTID = 1;

	
	void Random::setSeed(int newSeed)
	{
		srand(newSeed);
	}
	int Random::getInt()
	{
		return rand();
	}
	TimeStamp getTime()
	{
		return TimeStamp();
	}
}




