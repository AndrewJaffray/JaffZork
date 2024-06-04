#ifndef GAMEENTITY_H
#define GAMEENTITY_H



class GameEntity { //abstract class for gameEntity
public:
    virtual ~GameEntity() = default;

    virtual void gameOver() = 0;
};

#endif // GAMEENTITY_H
