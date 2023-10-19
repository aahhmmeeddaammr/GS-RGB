#include<bits/stdc++.h>
#include "bmplib.h"
class RGB1 {
private:
    bool save = true , exit = false ;
    unsigned char imagergb[SIZE][SIZE][RGB] , image2rgb[SIZE][SIZE][RGB], image3rgb[SIZE][SIZE][RGB] , temprgb[SIZE][SIZE][RGB];
    bool validRGB(int i,int j);
    void equalRGB();
public:
    void saveImageRGB();
    void loadImageRGB();
    void MenuRGB();
    void Black_WhiteRGB();
    void InvertRGB();
    void MergeRGB();
    void FlipRGB();
    void RotateRGB();
    void Darken_LightenRGB();
    void Detect_EdgeRGB();
    void EnlargeRGB();
    void ShrinkRGB();
    void MirrorRGB();
    void ShuffleRGB();
    void BlurRGB();
    void CropRGB();
    void Skew_RightRGB();
    void Skew_UpRGB();
    void ExitRGB();
};