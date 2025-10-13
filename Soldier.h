#ifndef SOLDIER_H 
#define SOLDIER_H
#include "Character.h"
namespace mtm{
class Soldier: public Character
{
public:
    explicit Soldier(CharacterType type, Team team,int health,int ammo,int range,int power); //constructor
    ~Soldier() = default;//distructor
    Soldier(const Soldier& soldier)=default;//copy constructor
    void reload() override;// relode weapon
    void attacked() override; // takes dowm ammo 
    Character* clone() const override;// returns new pointer with the same values
    //returns if the second character at the range of the first one
    bool inRange(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
     //returns if before attack there is ennough ammo
    bool hasEnoughAmmo();
    //return how much he hurts the ather charcter
    int getDemage(int row,int col, const GridPoint & dst_coordinates,Team team);
     
};
}
#endif

