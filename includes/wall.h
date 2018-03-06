#ifndef WALL_H
#define WALL_H

#include "game_object.h"
#include "component.h"

#define WALL_U_SPRITE   "assets/WallUp.bmp"
#define WALL_D_SPRITE   "assets/WallDown.bmp"
#define WALL_L_SPRITE   "assets/WallLeft.bmp"
#define WALL_R_SPRITE   "assets/WallRight.bmp"

#define WALL_BH_SPRITE  "assets/WallBoth-Hori.bmp"
#define WALL_BV_SPRITE  "assets/WallBoth-Vert.bmp"

#define WALL_CTL_SPRITE "assets/WallcornerTL.bmp"
#define WALL_CTR_SPRITE "assets/WallcornerTR.bmp"
#define WALL_CBL_SPRITE "assets/WallcornerBL.bmp"
#define WALL_CBR_SPRITE "assets/WallcornerBR.bmp"

enum class WallType
{
    UP,
    LEFT,
    DOWN,
    RIGHT,
    CORNER_TL, //corner top left
    CORNER_TR, //corner top right
    CORNER_BL, //corner bottom left
    CORNER_BR, //corner bottom right
    BOTH_H, // Walls on both sides, horizontal
    BOTH_V, // Walls on both sides, vertical
};

class Wall : public GameObject
{
    public:
        void Create(double x, double y);
        void Update(float dt);

    protected:

    private:
};

class WallRenderComponent : public RenderComponent
{
    public:
        void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, WallType wt);
};
#endif // WALL_H
