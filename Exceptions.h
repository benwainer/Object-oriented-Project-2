#ifndef EXCEPTIONS_H 
#define EXCEPTIONS_H
#include <stdexcept>
namespace mtm
{
    class Exceptions : public std::exception{};
    class IllegalArgument : public Exceptions
    {
        public:
        const char* what() const noexcept override;

    };
 class IllegalCell : public Exceptions
    {
        public:
        const char* what() const noexcept override;

    };
    class CellEmpty : public Exceptions
    {
        public:
        const char* what() const noexcept override;

    };
    class MoveTooFar : public Exceptions
    {
        public:
        const char* what() const noexcept override;

    };    
    class CellOccupied : public Exceptions
    {
        public:
        const char* what() const noexcept override;

    };
     class OutOfRange : public Exceptions
    {
        public:
        const char* what() const noexcept override;

    };
    class OutOfAmmo : public Exceptions
    {
        public:
        const char* what() const noexcept override;

    };
   class IllegalTarget : public Exceptions
    {
        public:
        const char* what() const noexcept override;

    };


}


#endif

