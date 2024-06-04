#ifndef GAMEEXCEPTIONS_H
#define GAMEEXCEPTIONS_H

#include <exception>
#include <string>

//This is the base class for all game exceptions
//inherits from std:exception
class GameException : public std::exception {
public:
    //this constructor takes an error message as a constructor
    explicit GameException(const std::string& message) : msg(message) {}
    virtual const char* what() const noexcept override {
        return msg.c_str();
    }
private:
    std::string msg;
};

//specific class for invalid move exceptions
//inherits from GameException
class InvalidMoveException : public GameException {
public:
    explicit InvalidMoveException(const std::string& message) : GameException(message) {}
};

#endif // GAMEEXCEPTIONS_H
