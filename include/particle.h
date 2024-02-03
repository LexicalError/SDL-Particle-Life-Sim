#pragma once
#include <vector>
#include "vector2d.h"
#include "color.h"

class Particle{
    private:
        Vec2 pos;
        Vec2 velocity;
        Color color;
        int id;
    public:
        Particle(Vec2 p_pos, Vec2 p_velocity, Color p_color, int p_id) : pos(p_pos), velocity(p_velocity), color(p_color), id(p_id){};
        void setPos(Vec2 p_pos);
        void setVelocity(Vec2 p_velocity);
        Vec2 getPos();
        Vec2 getVelocity();
        Color getColor();
        int getId();
        int setId(int p_id);
        void update(Particle *P, double A, double B, double alpha, double beta, int sign, double deltaT);
        void move(int width, int height, double deltaT, double frictionConst);
};