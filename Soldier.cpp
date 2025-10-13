#include <string> 
#include <iostream>
#include <cstdio>
#include "Character.h"
#include "Soldier.h"
#define SOLDIER_STEPS 3
#define NEW_SOLDIER_AMMO 3
#define SOLDIER_MISSING_AMMO 1
#define NO_DEMAGE 0
#define SEMI_SOLDIER_DEMAGE 2
using namespace mtm;
Soldier :: Soldier(CharacterType type,Team team,int health,int ammo,int range,int power):
Character(type,team,health,ammo,range,power,SOLDIER_STEPS) {}

Character* Soldier:: clone() const
{
    return new Soldier(*this);
}
void Soldier:: reload()
{
   this->ammo=this->ammo+NEW_SOLDIER_AMMO;

} 

void Soldier::attacked()
{
    this->ammo=this->ammo-SOLDIER_MISSING_AMMO;
}
 bool Soldier:: inRange(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
 {
    if(GridPoint::distance(src_coordinates,dst_coordinates)>this->range)
   {
        return false;
   }
   return true;
 }
 bool Soldier:: hasEnoughAmmo()
 {
     if(this->ammo<SOLDIER_MISSING_AMMO)
     {
         return false;
     }
     return true;
 }
 int Soldier:: getDemage(int row,int col, const GridPoint & dst_coordinates,Team team)
 {
     if(team==this->team)
     {
         return NO_DEMAGE;
     }
     if(row==dst_coordinates.row && col==dst_coordinates.col)
     {
         return this->power;
     }
     //ceil
     int new_power = ceil((double)this->power/(double)SEMI_SOLDIER_DEMAGE);
     return new_power;
 }

