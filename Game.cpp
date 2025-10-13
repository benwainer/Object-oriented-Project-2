#include "Soldier.h"  
#include "Medic.h"
#include "Sniper.h"
#include "Character.h"
#include "Game.h"
#include "Exceptions.h"
#include "Auxiliaries.h"
#include <assert.h>
#define S_LITTLE 's'
#define S_BIG 'S'
#define N_LITTLE 'n'
#define N_BIG 'N'
#define M_LITTLE 'm'
#define M_BIG 'M'
#define NO_CHARACTER ' '
#define SOLDIER_SEMI_RANGE 3
#define NO_HEALTH 0
using namespace std;
using namespace mtm;

int Game::place(int row,int col)
{
    return (row)*(this->width)+col;
}

Game::Game(int height,int width):height(height),width(width)
{
    this->board_chars.resize(height*width,NO_CHARACTER);
    this->board=std::vector<std::vector<std::shared_ptr<Character>>>(height,std::vector<std::shared_ptr<Character>>(width,nullptr));
}

 char Game::getCharType(std::shared_ptr<Character> character)
{
    Team team=character->getTeam();
    CharacterType type=character->getType();
    if(team==POWERLIFTERS)
    {
        if(type==SOLDIER)
        {
            return S_BIG;
        }
        if(type==SNIPER)
        {
            return N_BIG;
        }
        if(type==MEDIC)
        {
            return M_BIG;
        }
    }
    if(team==CROSSFITTERS)
    {
        if(type==SOLDIER)
        {
            return S_LITTLE;
        }
        if(type==SNIPER)
        {
            return N_LITTLE;
        }
        if(type==MEDIC)
        {
            return M_LITTLE;
        } 
    }
    return NO_CHARACTER;
}
 shared_ptr<Character> Game:: makeCharacter(CharacterType type, Team team,
                units_t health, units_t ammo, units_t range, units_t power)
{
    if(health<=0 || ammo<0 || range<0 || power<0)
    {
     throw IllegalArgument();
    }
    if(type==SOLDIER)
    {
       return std::shared_ptr<Character>(new Soldier(type,team,health,ammo,range,power));
    }
    if(type==SNIPER)
    {
        return std::shared_ptr<Character>(new Sniper(type,team,health,ammo,range,power));
    }
    return std::shared_ptr<Character>(new Medic(type,team,health,ammo,range,power));
}
void Game:: copyandAllocate(const Game&game_to_copy,Game& new_game)
{
    if(new_game==game_to_copy)
    {
        return;
    }
    new_game.height=game_to_copy.height;
    new_game.width=game_to_copy.width;
    new_game.board_chars=game_to_copy.board_chars;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(game_to_copy.board.at(i).at(j)!=nullptr)
            {
              Character* temp=game_to_copy.board.at(i).at(j)->clone();
               new_game.board.at(i).at(j)=shared_ptr<Character> (temp);
            }
        }
    }
}
bool  Game:: operator== (const Game& game)
{
if(game.height!=this->height || game.width!=this->width || game.board_chars!=this->board_chars
|| game.board!=this->board )
{
    return false;
}
return true;
}
 
Game& Game :: operator=(const Game& game)
{
    copyandAllocate(game,*this);
    return *this;
}
 
void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character)
{
    if(!onBoard(coordinates,coordinates))
    {
        throw IllegalCell();
    }
    if(this->board.at(coordinates.row).at(coordinates.col)!=nullptr)
    {
        throw CellOccupied();
    }
    int location=this->place(coordinates.row,coordinates.col);
    board.at(coordinates.row).at(coordinates.col)=character;
     board_chars.at(location)=this->getCharType(character);
}
Game:: Game(const Game& other) : Game(other.height,other.width)
 {
    copyandAllocate(other,*this);
 }
 
 void Game:: reload(const GridPoint & coordinates)
 {
     if(!onBoard(coordinates,coordinates))
     {
         throw IllegalCell();
     }
      if(this->board.at(coordinates.row).at(coordinates.col)==nullptr)
    {
        throw CellEmpty();
    }
    this->board.at(coordinates.row).at(coordinates.col)->reload();
 }
  bool Game:: isOver(Team* winningTeam) const
  {
      bool found_character=false;
      Team team;
      for(int i=0;i<height;i++)
      {
          for(int j=0;j<width;j++)
          {
              if(this->board.at(i).at(j)!=nullptr && !found_character)
              {
                  found_character=true;
                  team=this->board.at(i).at(j)->getTeam();
                  continue;
              }
              if(found_character && board.at(i).at(j)!=nullptr)
              {
                  if(team!=board.at(i).at(j)->getTeam())
                  {
                      return false;
                  }
              }
          }
      }
      if(found_character && winningTeam!=NULL)
      {
            *winningTeam=team;
      }
      return true;
  }

bool Game:: onBoard(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{
    if(src_coordinates.col>=width || src_coordinates.col<0  || src_coordinates.row>=height
     || src_coordinates.row<0 || dst_coordinates.col>=width || dst_coordinates.col<0  || 
     dst_coordinates.row>=height || dst_coordinates.row<0)
     {
         return false;
     }
     return true;
}
 void Game:: move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
 {
    if(!onBoard(src_coordinates,dst_coordinates))
    {
        throw IllegalCell();
    }
    if(this->board.at(src_coordinates.row).at(src_coordinates.col)==nullptr)
    {
        throw CellEmpty();
    }
    if(GridPoint::distance(src_coordinates,dst_coordinates)>
      this->board.at(src_coordinates.row).at(src_coordinates.col)->getSteps())
    {
        throw MoveTooFar();
    }
    if(this->board.at(dst_coordinates.row).at(dst_coordinates.col)

       ==this->board.at(src_coordinates.row).at(src_coordinates.col))
       {
           return;
       }
    if(this->board.at(dst_coordinates.row).at(dst_coordinates.col)!=nullptr)
    {
        throw CellOccupied();
    }
    this->board.at(dst_coordinates.row).at(dst_coordinates.col)=
    this->board.at(src_coordinates.row).at(src_coordinates.col);
    this->board.at(src_coordinates.row).at(src_coordinates.col)=nullptr;
    this->board_chars.at(place(dst_coordinates.row,dst_coordinates.col))=
    getCharType(this->board.at(dst_coordinates.row).at(dst_coordinates.col));
    this->board_chars.at(place(src_coordinates.row,src_coordinates.col))=NO_CHARACTER;
 }
void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{    
   attackTests(src_coordinates,dst_coordinates);
   Team team_src=this->board.at(src_coordinates.row).at(src_coordinates.col)->getTeam();
   CharacterType type_src=this->board.at(src_coordinates.row).at(src_coordinates.col)->getType();
   if(type_src==SOLDIER)
   {
      soldierAttack(src_coordinates,dst_coordinates,team_src);
   }
   else
   {
       if(!(team_src==this->board.at(dst_coordinates.row).at(dst_coordinates.col)->getTeam() && 
                type_src==MEDIC))
                {
                    this->board.at(src_coordinates.row).at(src_coordinates.col)->attacked();
                }    
       hit(src_coordinates,dst_coordinates,dst_coordinates.row,dst_coordinates.col,
       this->board.at(dst_coordinates.row).at(dst_coordinates.col)->getTeam());
   }
}

void Game:: attackTests(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{
    if(!onBoard(src_coordinates,dst_coordinates))
    {
        throw IllegalCell();
    }
    if(this->board.at(src_coordinates.row).at(src_coordinates.col)==nullptr)
    {
        throw CellEmpty();
    }
    Team team=this->board.at(src_coordinates.row).at(src_coordinates.col)->getTeam();
   CharacterType character_type=this->board.at(src_coordinates.row).at(src_coordinates.col)->getType();
    if(!this->board.at(src_coordinates.row).at(src_coordinates.col)->
    inRange(src_coordinates,dst_coordinates))
    {
        throw OutOfRange();
    }
    if(!this->board.at(src_coordinates.row).at(src_coordinates.col)->hasEnoughAmmo())
    {
        throw OutOfAmmo();
    }
    if(character_type==SOLDIER && dst_coordinates.row!= src_coordinates.row && dst_coordinates.col!=src_coordinates.col)
    {
       throw IllegalTarget();
    }
    if(character_type==MEDIC && (dst_coordinates==src_coordinates ||
   this->board.at(dst_coordinates.row).at(dst_coordinates.col)==nullptr))
   {
       throw IllegalTarget();
   }
   if(character_type==SNIPER && (this->board.at(dst_coordinates.row).at(dst_coordinates.col)==nullptr ||
   this->board.at(dst_coordinates.row).at(dst_coordinates.col)->getTeam()==team))
   {
       throw IllegalTarget();
   }
}
 void Game:: soldierAttack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates,Team team)
 {
    bool already_attacked=false;
    int new_range = ceil((double)(this->board.at(src_coordinates.row).at(src_coordinates.col)->getRange())/(double)SOLDIER_SEMI_RANGE);
    for(int i=dst_coordinates.row-new_range;i<=dst_coordinates.row+new_range && i<height;i++)
    {
        if(i<0)
        {
            continue;
        }
        for(int j=dst_coordinates.col-new_range;j<=dst_coordinates.col+new_range && j<width;j++)
        {
            GridPoint point(i,j);
            if(j<0 ||GridPoint::distance(point,dst_coordinates) >new_range)
            {
                continue;
            }
              if(this->board.at(i).at(j)!=nullptr)
            {
                if(!already_attacked)
                {
                    already_attacked=true;
                    this->board.at(src_coordinates.row).at(src_coordinates.col)->attacked();
               }
                hit(src_coordinates,dst_coordinates,i,j,this->board.at(i).at(j)->getTeam());
            }
        }

    }

}

void Game:: hit(const GridPoint & src_coordinates,const GridPoint & dst_coordinates,int row,int col,Team team)
{
                this->board.at(row).at(col)->gotHit(this->board.at(src_coordinates.row).at(src_coordinates.col)
                ->getDemage(row,col,dst_coordinates,team));
                if(this->board.at(row).at(col)->getHealth()<=NO_HEALTH)
                {
                    this->board.at(row).at(col)=nullptr;
                    this->board_chars.at(place(row,col))=NO_CHARACTER;
                }
}

namespace mtm
{
  ostream&  operator<<(std::ostream& os,const Game& game)
 {
    const char * begin= &(game.board_chars.at(0));
    const char * end= &(game.board_chars[game.board_chars.size()]);
    return printGameBoard(os,begin,end,game.width);
 }
}

