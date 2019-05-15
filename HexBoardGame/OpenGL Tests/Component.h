#pragma once
typedef unsigned long ComponentID;


//Component Masks
constexpr ComponentID ComponentTransform =      0b00000000000000000000000000000001;
constexpr ComponentID ComponentModel =          0b00000000000000000000000000000010;
constexpr ComponentID ComponentBoardPosition =  0b00000000000000000000000000000100;
constexpr ComponentID ComponentBoardPiece =     0b00000000000000000000000000001000;

class Component
{
protected:
    Component() = default;
    Component(ComponentID cid);
public:
    ComponentID compID;
    ~Component() = default;

};