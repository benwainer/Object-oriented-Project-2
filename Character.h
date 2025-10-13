#ifndef CHARACTER_H 
#define CHARACTER_H
#include <string>
#include <iostream>
#include <cstdio>
#include "Auxiliaries.h"
namespace mtm{
class Character
{
    protected:
    Team team;
    CharacterType type_of_character;
    int health;
    int ammo;
    int range;
    int power;
    int num_of_steps;
    int num_of_attack;
    public:
    explicit Character(CharacterType type, Team team,int health,int ammo,int range,int power,int num_of_steps);//constructor
    ~Character()=default;//destructor
    Character(const Character& character);//copy constructor
    Character& operator=(const Character& character);
    bool operator==(const Character& character);
    bool operator!=(const Character& character);
    virtual void reload()=0;// a virtual function taht will reload differently each different 
    //character according to the rules of the game
    virtual Character* clone() const=0;// a virtual function that will clone an existin character
    void gotHit(int demage);//takes down health from a character which got hit
    int getPower();//Returns the power of a character
    int getHealth();//Returns the health of a character
    int getAmmo();//Returns the ammo of a character
    int getRange();//Returns the range of a character
    virtual void attacked()=0;// a virtual function which will take down ammo from each different character
    //according to the rules of th game 
    CharacterType getType();// Returns the type of the Character
    Team getTeam();//Returns the team of the character
    int getSteps();//Returns the number of steps a character have
    int getNumofAttack();//Returns the number of times a character has attacked
    virtual bool inRange(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)=0;
    // a virtual function that will check if a target is in range for each different character
    virtual bool hasEnoughAmmo()=0;// a virtual function that will chek if the character has enough ammo to attack
    //for each different character
    virtual int getDemage(int row,int col, const GridPoint & dst_coordinates,Team team)=0;
    /* a virtual function that will get the power of a character that attacks according to the rules of the game*/
     
};
}
#endif /*CHARACTAR_H*/

