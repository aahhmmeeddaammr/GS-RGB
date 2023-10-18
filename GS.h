#include<bits/stdc++.h>
#include "bmplib.h"
class GS{
private:
    bool save = true, exit = false;
    unsigned char image[SIZE][SIZE]{}, image2[SIZE][SIZE]{}, image3[SIZE][SIZE]{}, temp[SIZE][SIZE]{};
    bool valid(int i, int j);
    void equal();
public:
    void saveImage();
    void loadImage();
    void Menu();
    void Black_White();
    void Invert();
    void Merge();
    void Flip();
    void Rotate();
    void Darken_Lighten();
    void Detect_Edge();
    void Enlarge();
    void Shrink();
    void Mirror();
    void Shuffle();
    void Blur();
    void Crop();
    void Skew_Right();
    void Skew_Up();
    void Exit();
};
