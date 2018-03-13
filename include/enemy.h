#ifndef ENEMY_H
#define ENEMY_H

#include "moving_game_object.h"
#include "collidable.h"

#define BURWOR_SPRITE  "assets/Burwor.bmp"
#define GARWOR_SPRITE  "assets/Garwor.bmp"
#define THORWOR_SPRITE "assets/Thorwor.bmp"
#define WORLUK_SPRITE  "assets/Worluk.bmp"
#define WIZARD_SPRITE  "assets/Wizard.bmp"

enum EnemyType
{
    BURWOR,
    GARWOR,
    THORWOR,
    WORLUK,
    WIZARD
};

class EnemyBehaviourComponent : public Component
{
    public:
        void Create(AvancezLib* system,
                    MovingGameObject * mgo,
                    std::set<GameObject*> * game_objects,
                    Map * game_map);
        void Update(float dt) {};
};

class Enemy : public Collidable
{
    EnemyType et;
    public:
        void Create(EnemyType et);
        void SetEnemyType(EnemyType et);
        EnemyType GetEnemyType();
        void Receive(Message m);
        Message collide();
};

class EnemyRenderComponent : public RenderComponent
{
    public:
        void Create (
            AvancezLib* system,
            GameObject * go,
            std::set<GameObject*> * game_objects,
            EnemyType et
        );

        void Update(float dt);

};
#endif // ENEMY_H
