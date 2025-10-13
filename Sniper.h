#ifndef SNIPER_H 
#define SNIPER_H
#include "Character.h"
namespace mtm{
class Sniper: public Character
{
    
public:
    explicit Sniper(CharacterType type, Team team,int health,int ammo,int range,int power); //constructor
    ~Sniper()=default; //distructor
    void reload()override; // relode weapon
    void attacked()override; // takes dowm ammo 
    Character* clone() const; // returns new pointer with the same values
    //returns if the second character at the range of the first one
    bool inRange(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
    //returns if before attack there is ennough ammo
    bool hasEnoughAmmo();
    //return how much he hurts the ather charcter
    int getDemage(int row,int col, const GridPoint & dst_coordinates,Team team);
 

};
}
#endif

