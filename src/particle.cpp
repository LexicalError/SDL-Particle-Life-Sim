#pragma once
#include <vector>
#include <math.h>
#include <iostream>
#include "particle.h"
#include "vector2d.h"
#include "color.h"


void Particle::setPos(Vec2 p_pos){
    pos = p_pos;
}
void Particle::setVelocity(Vec2 p_velocity){
    velocity = p_velocity;
}
Vec2 Particle::getPos(){
    return pos;
}
Vec2 Particle::getVelocity(){
    return velocity;
}
Color Particle::getColor(){
    return color;
}
int Particle::getId(){
    return id;
}
int Particle::setId(int p_id){
    id = p_id;
}
// L1: y / alpha + x / beta = 1; L2: y / A + x / B = 1
void Particle::update(Particle *P, double A, double B, double alpha, double beta, int sign, double deltaT){
    double dx = P->getPos().x - this->getPos().x;
    double dy = P->getPos().y - this->getPos().y;
    double distance = sqrt(dx * dx + dy * dy);
    if(distance > B || distance == 0)
        return;
    double force = sign * A * (1 - distance / B);
    if(distance <= beta)
        force -= alpha * ( 1 - distance / beta);
    if(distance < 1)
        force -= 60;
    velocity.add({(dx / distance) * force * deltaT, (dy / distance) * force * deltaT});
}

void Particle::move(int width, int height, double deltaT, double frictionConst){
    velocity.x *= frictionConst;
    velocity.y *= frictionConst;
    pos.add(velocity);
    if(pos.x < 0 || pos.x >= width){
        if(pos.x < 0)
            pos.x = 0;
        else
            pos.x = width;
        velocity.x *= -1;   
    }
    if(pos.y < 0 || pos.y >= height){
        if(pos.y < 0)
            pos.y = 0;
        else
            pos.y = height;
        velocity.y *= -1; 
    }
}