// 4900group43.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <vector>

typedef int32_t EntityID;
typedef uint8_t ComponentMask;

typedef struct { int x; int y; int z; } Vec3i;

Vec3i operator+(const Vec3i& left, const Vec3i& right) {
	Vec3i out = { 0,0,0 };
	out.x = left.x + right.x;
	out.x = left.y + right.y;
	out.x = left.z + right.z;
	return out;
}
Vec3i operator*(const Vec3i& left, const Vec3i& right) {
	Vec3i out = { 0,0,0 };
	out.x = left.x * right.x;
	out.x = left.y * right.y;
	out.x = left.z * right.z;
	return out;
}
Vec3i operator*(const Vec3i& left, const double right) {
	Vec3i out = { 0,0,0 };
	out.x = left.x * right;
	out.x = left.y * right;
	out.x = left.z * right;
	return out;
}

typedef union {
	int data[4 * 4];
	struct {
		int _xx;
		int _xy;
		int _xz;
		int _xp;
		int _yx;
		int _yy;
		int _yz;
		int _yp;
		int _zx;
		int _zy;
		int _zz;
		int _zp;
		int _px;
		int _py;
		int _pz;
		int _pp;
	};
	
} Mat4i;

typedef Vec3i Position;
typedef Vec3i Rotation;
typedef Vec3i Momentum;
typedef Vec3i Mass;
typedef char Visual;
typedef long double TimeStamp;
typedef Vec3i CollisionBody;

template <typename ComponentT>
class ComponentContainer {
private:
public:
	std::vector<ComponentT> Components;
	std::unordered_map<EntityID,int> EntityMap;
	ComponentT* getComponent(const EntityID&);
	void setComponent(const EntityID&, const ComponentT&);
};

template <typename ComponentT> 
ComponentT* ComponentContainer<ComponentT>::getComponent(const EntityID& id) {
	return &(Container.at(id));
}

template <typename ComponentT>
void ComponentContainer<ComponentT>::setComponent(const EntityID& id, const ComponentT& newElement) {
	Container.insert_or_assign(id, newElement);
}

struct WorldState {
	ComponentContainer<Position> Positions;
	ComponentContainer<Momentum> Momentums;
	ComponentContainer<Rotation> Rotations;
	ComponentContainer<Momentum> RotationalMomentums;
	ComponentContainer<Mass> Masses;
	ComponentContainer<Visual> Visuals;
	ComponentContainer<ComponentMask> Entities;
	ComponentContainer<CollisionBody> CollisionBodies;
	TimeStamp WorldTime;
};

class Entity {
	Position* position;
	Momentum* momentum;
	Rotation* rotation;
	Momentum* rotationalMomentum;
	Mass* mass;
	Visual* visual;
	CollisionBody* collisionBody;
	ComponentMask componentMask;
	EntityID id;
};


class WorldTime {
private:
	typedef struct { bool persistant; WorldState state; } keep;
	std::vector<keep> Moments;
	int CurrentMoment = 0;
public:
	WorldTime() {
		Moments.reserve(10);
	}
	WorldState& getCurrentMoment();
	WorldState& NextMoment();
};

class System {
	virtual void Run(const WorldState& lastState, WorldState& newState);
};

class Physics : System {
	static const int PerPass = 100;
	void ProcessMomentums(const WorldState& lastState, WorldState& newState) {
		newState.Momentums = lastState.Momentums;
	}
	void ProcessPositions(const WorldState& lastState, WorldState& newState) {
		double delta = newState.WorldTime - lastState.WorldTime;

		Momentum temp[PerPass];

		int length = newState.Positions.Components.size();

		auto posMapIter = newState.Positions.EntityMap.begin();

		Momentum* pTemp;

		Position* newPos = &newState.Positions.Components[0];
		const Position* oldPos = &lastState.Positions.Components[0];

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
	void ProcessRotations(const WorldState& lastState, WorldState& newState) {

	}
public:
	void Run(const WorldState& lastState, WorldState& newState) {
		
		ProcessMomentums(lastState, newState);
		ProcessPositions(lastState, newState);
		ProcessRotations(lastState, newState);
	}
};

class World {
	WorldTime TimeLine;
	std::vector<System> Systems;
};

int main()
{
	//testECS test1;
	//test1.
    std::cout << "Hello World!\n"; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
