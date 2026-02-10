# ⚔️ Battle Simulation Game 
A turn-based strategy game built in C++.
The project focuses on object-oriented programming, inheritance, and memory management.

🔹  **Core Features**

**Character Classes**:
Soldier, Medic, and Sniper — each with unique movement, attack, and reload behavior.

 **Game Board**:
A dynamic grid (Game class) where characters move, attack, and interact.

**Combat System**:
Each character can attack enemies based on range, direction, and special rules.

 **Game Logic**:
Win condition checks, turn management, and in-game error handling via custom exceptions.

🗂️ **Project Structure**

**Game.h / Game.cpp**
Core game logic and engine implementation.
Manages the board, turn flow, win conditions, and interaction between characters.

**Character.h / Character.cpp**
Abstract base class defining common behavior for all characters.

**Soldier.h / Soldier.cpp**
Implements soldier-specific movement, attack, and reload logic.

**Medic.h / Medic.cpp**
Implements healing mechanics and support behavior.

**Sniper.h / Sniper.cpp**
Implements long-range attack rules and special targeting logic.

**SortedList**
Custom module used for internal data handling.

💡 Entry point for understanding the game logic:
Start with Game.h and Game.cpp, which contain the main flow and rules of the game.

⚙️ **Technical Highlights**

Implemented full class hierarchy from a base Character class.

Used smart pointers (std::shared_ptr) for safe memory handling.

Designed a robust exception system (IllegalCell, OutOfRange, OutOfAmmo, etc.).

Clean and reusable OOP design following inheritance principles.

Integrated with an original SortedList module for internal data handling.

🧠 **Concepts Used**

OOP • Inheritance • Polymorphism • Exception Handling • Smart Pointers
