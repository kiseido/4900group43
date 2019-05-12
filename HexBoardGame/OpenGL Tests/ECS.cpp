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

#define TODO throw new std::logic_error("TODO");

namespace ECS {
	constexpr inline ComponentMask operator | (ComponentMask lhs, ComponentMask rhs)
	{
		using T = std::underlying_type_t <ComponentMask>;
		return static_cast<ComponentMask>(static_cast<T>(lhs) | static_cast<T>(rhs));
	}

	constexpr inline ComponentMask& operator |= (ComponentMask& lhs, const ComponentMask rhs)
	{
		lhs = lhs | rhs;
		return lhs;
	}

	EntityID Entity::NEXTID = 1;

	const int RTPhysics::PerPass = 100;

	void RTPhysics::ProcessMomentums(const WorldState& lastState, WorldState& newState) {
		newState.Momentums = lastState.Momentums;
	}

	void RTPhysics::ProcessPositions(const WorldState& lastState, WorldState& newState) {
		TimeStamp delta = newState.WorldTime - lastState.WorldTime;

		Momentum temp[PerPass];

		int length = newState.RealTimePositions.Components.size();

		auto posMapIter = newState.RealTimePositions.EntityMap.begin();

		Momentum* pTemp;

		Position* newPos = &newState.RealTimePositions.Components[0];
		const Position* oldPos = &lastState.RealTimePositions.Components[0];

		for (int start = 0; start < length; start += PerPass) {
			int end = start + PerPass;
			if (end > length)
				end = length;

			pTemp = temp;

			for (int i = start; i < end; ++i) {
				Momentum* p = newState.Momentums.getComponent(posMapIter->first);

				if (p == nullptr) {
					*pTemp = { 0,0,0 };
				}
				else {
					*pTemp = *p * delta;
				}
				++posMapIter;
				++pTemp;
			}

			pTemp = temp;

			for (int i = start; i < end; ++i) {
				*newPos = *pTemp + *oldPos;
				++newPos;
				++pTemp;
				++oldPos;
			}
		}
	}
	void RTPhysics::ProcessRotations(const WorldState& lastState, WorldState& newState) {

	}

	void RTPhysics::Run(const WorldState& lastState, WorldState& newState) {

		ProcessMomentums(lastState, newState);
		ProcessPositions(lastState, newState);
		ProcessRotations(lastState, newState);
	}

	WorldState::WorldState()
	{
		
	}
	WorldState & WorldState::getCurrentMoment()
	{
		TODO
	}
	const WorldState & WorldState::getLastMoment() const
	{
		TODO
	}
	WorldState & WorldState::NextMoment()
	{
		TODO
	}
	TimeStamp Board::advanceTime(TimeStamp)
	{
		TODO
	}
	Entity Board::NewEntity(ComponentMask)
	{
		TODO
	}

	bool EntityMask::hasMask(TypeMask check)
	{
		return mask & check != 0;
	}

	void EntityMask::addMask(TypeMask addition)
	{
		mask |= addition;
	}

}


int main() {

}

