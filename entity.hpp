#pragma once
class Entity {
    public:
        int getX();
        int getY();
        int getW();
        int getH();
        Entity(int x, int y, int w, int h);
    protected:
        int x;
        int y;
        int w;
        int h;
};