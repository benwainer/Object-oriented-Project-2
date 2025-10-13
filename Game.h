#ifndef GAME_H 
#define GAME_H
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include <memory>
#include <vector>
#include <iostream>

namespace mtm
{
    class Game
    {
        int height;
        int width;
        std::vector<char> board_chars;// a board of chars to print the game
        std::vector<std::vector<std::shared_ptr<Character>>> board; // a board ofshared pointers that point on the 
        //characters on the board
        int place(int row,int col);//Returns the place of the character in the board of chars according to its row and column
        void copyandAllocate(const Game& game_to_copy,Game& new_game);//Copies the data of an existing game to an empty game
        bool operator==(const Game& game);
        char getCharType(std::shared_ptr<Character> character);//Returns the char that should be on the board of the game accordign
        //to the character
        bool onBoard(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);//Returns true 
        // if the coordinates are on the board and false if they are not.
        void attackTests(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        /*
        Checks if the attack is legal. throws IllegalTarget exception if character in the source coordinates
        can't attack the destination coordinates. throws IllegalCell if on of the coordinates are not on board.
        throws OutOfAmmo exception if the attacking character doesn't have enough ammo to attack.
        throws OutOfRange exception if the exception if the target is not in the range of the attacking character.
        throws CellEMpty if there is no character in the source coordniates.
        */
        void soldierAttack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates,Team team);
        // the function is used when the attacking character is a soldier
        void hit(const GridPoint & src_coordinates,const GridPoint & dst_coordinates,int row,int col,Team team);
        /* this functions is calling to the charater functions that takes down the health from the attacked character.
           Also removes from the board the character if it died*/
        public:
        Game(int height,int width);
        ~Game()=default;
        Game(const Game& other);
        Game& operator=(const Game& other);
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        //Adds a character to the game board.Throws IllegalCell exception if the coordinates are not on board.
        //Throws CellOccupied if theres is already a character on this coordinates on board.
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                units_t health, units_t ammo, units_t range, units_t power);
        // makes a new character.Throws IllegalArgument exception if one of the arguments is illegal.
        //Creates a new character with given arguments otherwise.
        void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        /*Moves a character on the board. Throws a IllegalCell exception if one of the coordinates
         is not on board. Throws a CellEmpty exception if there isn't a character in the source coordinates.
         Throws MoveTooFar exception if the destination coordinates are too far for the character in the 
         source coordinates. Throws CellOccupied exception if there is already a character in the destination 
         coordinates. Moves the charater in the source destination to the destination coordinates otherwise.
         */
        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        /*The function that used when one character attacks another. Throws IllegalTarget exception if character in the source coordinates
        can't attack the destination coordinates. throws IllegalCell if on of the coordinates are not on board.
        throws OutOfAmmo exception if the attacking character doesn't have enough ammo to attack.
        throws OutOfRange exception if the exception if the target is not in the range of the attacking character.
        throws CellEMpty if there is no character in the source coordniates. Attacks otherwise*/
        void reload(const GridPoint & coordinates);
        /* reloads a character at the coordinates.  Throws a IllegalCell exception if one of the coordinates
         is not on board. Throws a CellEmpty exception if there isn't a character in the source coordinates.
         Reloades the character at the coordinates otherwise.*/
        bool isOver(Team* winningTeam=NULL) const;//Checks whether the game was over.
        friend std::ostream& operator<<(std::ostream& os,const Game& game);
    };
   
}
#endif /*GAME_H*/

