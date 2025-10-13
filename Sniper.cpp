#include "Sniper.h" 
#define SNIPER_STEPS 4
#define NEW_SNIPER_AMMO 2
#define SNIPER_MISSING_AMMO 1
#define NO_DEMAGE 0
#define SNIPER_SEMI_RANGE 2
#define SNIPER_SPECIAL_ATTACK 3
#define EXTRA_SNIPER_POWER 2
#define FIRST_ATTACK 1
using namespace mtm;
Sniper :: Sniper(CharacterType type, Team team,int health,int ammo,int range,int power):
Character(type,team,health,ammo,range,power,SNIPER_STEPS) 
{}
void Sniper:: reload ()
{

 this->ammo=this->ammo+NEW_SNIPER_AMMO;
} 
void Sniper::attacked()
{
    this->ammo=this->ammo-SNIPER_MISSING_AMMO;
    (this->num_of_attack)++;
}
Character* Sniper:: clone() const
{
    return new Sniper(*this);
}
bool Sniper:: inRange(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{
    if(GridPoint::distance(src_coordinates,dst_coordinates)>this->range)
    {
        return false;
    }
   int new_range = ceil((double)this->range/(double)SNIPER_SEMI_RANGE);
    if(GridPoint::distance(src_coordinates,dst_coordinates)<new_range)
    {
        return false;
    }
    return true;
}
bool Sniper:: hasEnoughAmmo()
 {
     if(this->ammo<SNIPER_MISSING_AMMO)
     {
         return false;
     }
     return true;
 }
   int Sniper:: getDemage(int row,int col, const GridPoint & dst_coordinates,Team team)
   {
       if(!(this->num_of_attack%SNIPER_SPECIAL_ATTACK))
       {
           return EXTRA_SNIPER_POWER*this->power;
       }
       return this->power;
   }

