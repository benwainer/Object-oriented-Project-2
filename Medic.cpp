#include <string> 
#include <iostream>
#include <cstdio>
#include "Character.h"
#include "Medic.h"
#define MEDIC_STEPS 5
#define NEW_MEDIC_AMMO 5
#define MEDIC_MISSING_AMMO 1
using namespace mtm;
Medic :: Medic(CharacterType type, Team team,int health,int ammo,int range,int power):
Character(type,team,health,ammo,range,power,MEDIC_STEPS) {}
void Medic:: reload()
{
    this->ammo=this->ammo+NEW_MEDIC_AMMO;
} 
void Medic::attacked()
{
   this->ammo=this->ammo-MEDIC_MISSING_AMMO;
}
Character* Medic:: clone() const
{
    return new Medic(*this);
}
bool Medic:: inRange(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{
    if(GridPoint::distance(src_coordinates,dst_coordinates)>this->range)
    {
        return false;
    }
    return true;
}
bool Medic:: hasEnoughAmmo()
 {
     if(this->ammo<MEDIC_MISSING_AMMO)
     {
         return false;
     }
     return true;
 }
  int Medic:: getDemage(int row,int col, const GridPoint & dst_coordinates,Team team1)
  {
      if(team1==this->team)
      {
          return -(this->power);
      }
      return this->power;
  }

