#pragma once
class Movable {
    public:           
        int getX();
        int getY();
        int getW();
        int getH();
        void moveLeft();
        void moveRight();
        void moveDown();
        void moveUp();
        Movable(int x, int y, int w, int h);
    private:
        int x;      
        int y;
        int w;
        int h;
};
