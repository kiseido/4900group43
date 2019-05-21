#pragma once


typedef unsigned int EntityID;
typedef unsigned long ComponentID;


//Component Masks
constexpr ComponentID ComponentTransform =      0b00000000000000000000000000000001;
constexpr ComponentID ComponentModel =          0b00000000000000000000000000000010;
constexpr ComponentID ComponentBoardPosition =  0b00000000000000000000000000000100;
constexpr ComponentID ComponentBoardPiece =     0b00000000000000000000000000001000;


constexpr ComponentID ComponentOutline =        0b01000000000000000000000000000000;
constexpr ComponentID ComponentPick =           0b10000000000000000000000000000000;

struct Component
{
protected:
    Component() = default;
public:
    ~Component() = default;

};