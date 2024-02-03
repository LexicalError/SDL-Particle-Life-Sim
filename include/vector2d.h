#pragma once
class Vec2{
    public:
        float x;
        float y;
        Vec2(float p_x, float p_y) : x(p_x), y(p_y){};
        void add(Vec2 vec){
            x += vec.x;
            y += vec.y;
        }
};