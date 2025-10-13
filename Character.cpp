#include <string> 
#include <iostream>
#include <cstdio>
#include "Character.h"
#include <assert.h>
#include <cmath>
#define NOT_ON_BOARD -1
#define FIRST_ATTACK 0
using namespace mtm;
Character:: Character(CharacterType type, Team team,int health,int ammo,int range,int power,int num_of_steps): 
    team(team),
    type_of_character(type),
    health(health),
    ammo(ammo),
    range(range),
    power(power),
    num_of_steps(num_of_steps),
    num_of_attack(FIRST_ATTACK)
{}

void Character:: gotHit(int demage)
{
    
    this->health=(this->health)-demage;
}
int Character:: getPower()
{
    return this->power;
}

int Character ::getHealth()
{
    return this->health;
}
Character& Character:: operator=(const Character& character)
{
    this->team=character.team;
    this->type_of_character=character.type_of_character;
    this->health=character.health;
    this->ammo=character.ammo;
    this->range=character.range;
    this->power=character.power;
    this->num_of_steps=character.num_of_steps;
    this->num_of_attack=character.num_of_attack;
    return *this;
}
Character:: Character(const Character& character)
{
    *this=character;
}
CharacterType Character::getType()
{
    return this->type_of_character;
}
Team Character::getTeam()
{
    return this->team;
}
int Character:: getAmmo()
{
    return this->ammo;
}
int Character:: getRange()
{
    return this->range;
}
bool Character:: operator==(const Character& character)
{
    if(this->team!=character.team || this->type_of_character!=character.type_of_character
        || this->health!=character.health || this->ammo!=character.ammo || this->range!=character.range
        || this->power!=character.power || this->num_of_steps!=character.num_of_steps 
         || this->num_of_attack!=character.num_of_attack)
        {
            return false;
        }
        return true;
}

bool Character::operator!=(const Character& character)
{
    if(*this==character)
    {
        return false;
    }
    return true;
}

int Character:: getSteps()
{
    return this->num_of_steps;
}
int Character:: getNumofAttack()
{
    return this->num_of_attack;
}

