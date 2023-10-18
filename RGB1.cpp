#include "RGB1.h"
#include <bits/stdc++.h>
#include "bmplib.h"
#include "bmplib.cpp"
using namespace std ;
bool RGB1::validRGB(int i, int j) {
    return i<SIZE&&j<SIZE &&i>=0&&j>=0 ;
}

void RGB1::equalRGB() {
    for(int i = 0 ; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                imagergb[i][j][k] = image2rgb[i][j][k];
            }
        }
    }
}

void RGB1::saveImageRGB() {
    char imageFileName[100];
    cout << endl << "Enter the target image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, imagergb);
    save = true;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                imagergb[i][j][k] = temprgb[i][j][k];
            }
        }
    }
    cout << endl << "Image saved successfully !!" << endl ;
    if(!exit)
        MenuRGB();
}

void RGB1:: loadImageRGB() {
    char imageFileName[100];
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    if(readRGBBMP(imageFileName , imagergb) != 1){
        readRGBBMP(imageFileName , temprgb);
    }else{
        loadImageRGB();
    }
    MenuRGB();
}

void RGB1::MenuRGB() {
    int filter;
    cout<<"1- Black & White Filter"<<endl;
    cout<<"2- Invert Filter"<<endl;
    cout<<"3- Merge Filter"<<endl;
    cout<<"4- Flip Image"<<endl;
    cout<<"5- Rotate Image"<<endl;
    cout<<"6- Darken and Lighten Image "<<endl;
    cout<<"7- Detect Image Edges"<<endl;
    cout<<"8- Enlarge Image"<<endl;
    cout<<"9- Shrink Image"<<endl;
    cout<<"10- Mirror 1/2 Image"<<endl;
    cout<<"11- Shuffle Image"<<endl;
    cout<<"12- Blur Image"<<endl;
    cout<<"13- Crop Image"<<endl;
    cout<<"14- Skew Image Right"<<endl;
    cout<<"15- Skew Image Up"<<endl;
    cout<<"16- Save image"<<endl;
    cout<<"0- Exit"<<endl;
    cout<<"   Enter number of filter (1->16) or 0 to Exit:"<<flush;
    cin>>filter;
    switch (filter){
        case 0:
            ExitRGB();
            break;
        case 1:
            Black_WhiteRGB();
            break;
        case 2:
            InvertRGB();
            break;
        case 3:
            MergeRGB();
            break;
        case 4:
            FlipRGB();
            break;
        case 5:
            RotateRGB();
            break;
        case 6:
            Darken_LightenRGB();
            break;
        case 7:
            Detect_EdgeRGB();
            break;
        case 8:
            EnlargeRGB();
            break;
        case 9:
            ShrinkRGB();
            break;
        case 10:
            MirrorRGB();
            break;
        case 11:
            ShuffleRGB();
            break;
        case 12:
            BlurRGB();
            break;
        case 13:
            CropRGB();
            break;
        case 14:
            Skew_RightRGB();
            break;
        case 15:
            Skew_UpRGB();
            break;
        case 16:
            saveImageRGB();
            break;
        default:
            cout<<"ERROR!!"<<endl;
            MenuRGB();
            break;
    }

}

void RGB1::Black_WhiteRGB() {
    for(int i = 0 ; i < SIZE ; ++i){
        for(int j = 0 ; j < SIZE ; ++j){
            imagergb[i][j][0] = imagergb[i][j][1] ;
            imagergb[i][j][2] = imagergb[i][j][1] ;
        }
    }
    save= false;
    MenuRGB();
}

void RGB1::InvertRGB() {
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0 ; j < SIZE ; ++j){
            for(int k = 0 ; k < RGB ; ++k){
                imagergb[i][j][k] = 255-imagergb[i][j][k];
            }
        }
    }
    save= false;
    MenuRGB();
}

void RGB1::MergeRGB() {
    char imageFileName[100];
    cout << "   Please enter name of image file to merge with: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    if(readRGBBMP(imageFileName, image2rgb) != 1){
        for(int i = 0 ; i < SIZE ; i++){
            for (int j = 0; j < SIZE ; ++j){
                for(int k = 0 ; k < RGB ; ++k){
                    imagergb[i][j][k] =(imagergb[i][j][k]+image2rgb[i][j][k])/2;
                }
            }
        }
        save= false;
        cout << endl << "Filter Applied Successfully !!" << endl ;
        MenuRGB();
    }else{
        cout << "ERROR!!" << endl ;
        MergeRGB();
    }
}

void RGB1::FlipRGB() {
    char f;
    cout <<"   Flip (h)orizontally or (v)ertically ? "<< flush;
    cin >> f;
    int p = -1 , m ;
    for(int i = SIZE-1; i >= 0; --i){
        m=0;
        p++;
        for (int j = SIZE-1 ; j >= 0 ; --j){
            for(int k = RGB-1 ; k >= 0 ; --k){
                image2rgb[m][p][k] = imagergb[i][j][k];
            }
            m++ ;
        }
    }
    for(int i = 0; i < SIZE / 2; i++) {
        for(int j = i; j < SIZE - i - 1 ; j++) {
            for(int k = 0 ; k < RGB ; ++k){
                if(f == 'v') {
                    int t = image2rgb[i][j][k];
                    image2rgb[i][j][k] = image2rgb[SIZE - 1 - j][i][k];
                    image2rgb[SIZE - 1 - j][i][k] = image2rgb[SIZE - 1 - i][SIZE - 1 - j][k];
                    image2rgb[SIZE - 1 - i][SIZE - 1 - j][k] = image2rgb[j][SIZE - 1 - i][k];
                    image2rgb[j][SIZE - 1 - i][k] = t;
                }
                else if(f == 'h'){
                    int t = image2rgb[i][j][k];
                    image2rgb[i][j][k]=image2rgb[j][SIZE-i-1][k];
                    image2rgb[j][SIZE-i-1][k]=image2rgb[SIZE-i-1][SIZE-j-1][k];
                    image2rgb[SIZE-i-1][SIZE-j-1][k]=image2rgb[SIZE-j-1][i][k];
                    image2rgb[SIZE-j-1][i][k]=t;
                }
            }
        }
    }
    if(f != 'h' && f != 'v'){
        cout << "ERROR!!" << endl;
        FlipRGB();
    }
    else{
        equalRGB();
        save= false;
        cout << endl << "Filter Applied Successfully !!" << endl ;
        MenuRGB();
    }
}

void RGB1::RotateRGB() {
    int rotate;
    cout<<"   Rotate (90), (180) or (270) degrees? "<<flush;
    cin>>rotate;
    if(rotate == 90 || rotate == 180 || rotate == 270){
        int flips = rotate/90 ;
        while(flips--){
            for (int i = 0; i < SIZE/2; i++){
                for (int j = i; j<SIZE-i-1; j++){
                    for(int k = 0 ; k < RGB ; ++k){
                        int t = imagergb[i][j][k];
                        imagergb[i][j][k] = imagergb[SIZE-1-j][i][k];
                        imagergb[SIZE-1-j][i][k] = imagergb[SIZE-1-i][SIZE-1-j][k];
                        imagergb[SIZE-1-i][SIZE-1-j][k] = imagergb[j][SIZE-1-i][k];
                        imagergb[j][SIZE-1-i][k] = t;
                    }
                }
            }
        }
        save= false;
        cout << endl << "Filter Applied Successfully !!" << endl ;
        MenuRGB();
    }
    else{
        cout<<"ERROR!!"<<endl;
        RotateRGB();
    }
}

void RGB1::Darken_LightenRGB() {
    char mood;
    cout<<"   Do you want to (d)arken or (l)ighten? "<<flush;
    cin>>mood;
    if(mood=='d'){
        for(int i = 0; i < SIZE; ++i){
            for (int j = 0; j < SIZE; ++j){
                for(int k = 0 ; k < RGB ; ++k){
                    imagergb[i][j][k] *= 0.5;
                }
            }
        }
        save = false;
        cout << endl << "Filter Applied Successfully !!" << endl ;
        MenuRGB();
    }
    else if(mood=='l'){
        for(int i = 0; i < SIZE; ++i){
            for (int j = 0; j < SIZE; ++j){
                for(int k = 0 ; k < RGB ; ++k){
                    imagergb[i][j][k] += (255-imagergb[i][j][k])/2 ;
                }
            }
        }
        save = false;
        cout << endl << "Filter Applied Successfully !!" << endl ;
        MenuRGB();
    }
    else{
        cout<<"ERROR!!"<<endl ;
        Darken_LightenRGB();
    }
}

void RGB1::Detect_EdgeRGB() {
    for(int i = 0 ; i < SIZE ; ++i){
        for(int j = 0 ; j < SIZE ; ++j){
            imagergb[i][j][0] = imagergb[i][j][1] ;
            imagergb[i][j][2] = imagergb[i][j][1] ;
        }
    }
    for(int i = 0 ; i < SIZE ; ++i){
        for(int j = 0 ; j < SIZE ; ++j){
            for(int k = 0 ; k < RGB ; ++k){
                if(imagergb[i][j][k] > 127)
                    imagergb[i][j][k] = 255 ;
                else
                    imagergb[i][j][k] = 0 ;
            }
        }
    }
    for(int i=0;i<SIZE;i++){
        for (int j = 0; j <SIZE ; ++j){
            for(int k = 0 ; k < RGB ; ++k){
                if(imagergb[i][j][k]==0&&
                   ((validRGB(i-1,j-1)&&imagergb[i-1][j-1][k]==255)
                    ||(validRGB(i-1,j)&&imagergb[i-1][j][k]==255)
                    ||(validRGB(i-1,j+1)&&imagergb[i-1][j+1][k]==255)
                    ||(validRGB(i,j-1)&&imagergb[i][j-1][k]==255)
                    ||(validRGB(i+1,j-1)&&imagergb[i+1][j-1][k]==255)
                    ||(validRGB(i+1,j)&&imagergb[i+1][j][k]==255)
                    ||(validRGB(i+1,j+1)&&imagergb[i+1][j+1][k]==255)
                    ||(validRGB(i,j+1)&&imagergb[i][j+1][k]==255)))
                {
                    image2rgb[i][j][k]=0;
                }
                else{
                    image2rgb[i][j][k]=255;
                }
            }
        }
    }
    equalRGB();
    MenuRGB();
}

void RGB1::EnlargeRGB() {
    int qu;
    cout << "Which quarter to enlarge 1, 2, 3 or 4?" << flush;
    cin >> qu;
    switch (qu) {
        case 1 :
            for (int i = 0; i < 128; ++i) {
                for (int j = 0; j < 128; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        image3rgb[i][j][k] = imagergb[i][j][k];
                    }

                }
            }
            for (int i = 0; i < 256; ++i) {
                for (int j = 0; j < 256; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        image2rgb[i][j][k] = image3rgb[i / 2][j / 2][k];
                    }
                }

            }
            break;
        case 2 :
            for (int i = 0; i < 128; ++i) {
                for (int j = 127; j < 256; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        image3rgb[i][j - 127][k] = imagergb[i][j][k];
                    }
                }
            }
            for (int i = 0; i < 256; ++i) {
                for (int j = 0; j < 256; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        image2rgb[i][j][k] = image3rgb[i / 2][j / 2][k];
                    }
                }
            }
            break;
        case 3 :
            for(int i = 127 ; i < 256 ; ++i){
                for(int j = 0 ; j < 128 ; ++j){
                    for(int k = 0 ; k < RGB ; ++k){
                        image3rgb[i-127][j][k] = imagergb[i][j][k] ;
                    }
                }
            }
            for(int i = 0 ; i < 256 ; ++i) {
                for (int j = 0; j < 256; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        image2rgb[i][j][k] = image3rgb[i / 2][j / 2][k];
                    }
                }
            }
            break;
        case 4 :
            for(int i = 127 ; i < 256 ; ++i){
                for(int j = 127 ; j < 256 ; ++j){
                    for(int k = 0 ; k < RGB ; ++k){
                        image3rgb[i-127][j-127][k] = imagergb[i][j][k] ;
                    }
                }
            }
            for(int i = 0 ; i < 256 ; ++i){
                for(int j = 0 ; j < 256 ; ++j){
                    for(int k = 0 ; k < RGB ; ++k){
                        image2rgb[i][j][k] = image3rgb[i/2][j/2][k] ;
                    }
                }
            }
            break ;
        default:
            cout << "ERROR!!!" << endl ;
            EnlargeRGB() ;
            break;
    }
    save = false ;
    equalRGB();
    MenuRGB();
}

void RGB1::ShrinkRGB() {
    cout<<"Shrink to (1/(2)), (1/(3)) or (1/(4))?"<<flush;
    int Shrink;
    cin>>Shrink;
    for (int i = 0; i <SIZE; ++i){
        for (int j = 0; j <SIZE ; ++j){
            for(int k = 0 ; k < RGB ; ++k){
                image2rgb[i][j][k]= 255;
                image2rgb[i/Shrink][j/Shrink][k]=imagergb[i][j][k];
            }
        }
    }save= false;
    equalRGB();
    MenuRGB();

}

void RGB1::MirrorRGB() {
    char c ;
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?" << flush ;
    cin >> c ;
    switch(c) {
        case 'l' :
            for (int i = 0; i < 256; ++i) {
                for (int j = 0; j < 256; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        imagergb[i][255 - j][k] = imagergb[i][j][k];
                    }
                }
            }
            break ;
        case 'r' :
            for(int i = 255 ; i >= 0 ;--i){
                for(int j = 255 ; j >= 0 ; --j){
                    for(int k = RGB-1 ; k >= 0 ; --k){
                        imagergb[i][255-j][k] = imagergb[i][j][k] ;
                    }
                }
            }
            break;
        case 'd' :
            for(int i = 255 ; i >= 0 ; --i){
                for(int j = 255 ; j >= 0 ; --j){
                    for(int k = RGB-1 ; k >= 0 ; --k){
                        imagergb[255-i][j][k] = imagergb[i][j][k] ;
                    }
                }
            }
            break;
        case 'u' :
            for(int i = 0 ; i < 256 ; ++i){
                for(int j = 0 ; j < 256 ; ++j){
                    for(int k = 0 ; k < RGB ; ++k){
                        imagergb[255-i][j][k] = imagergb[i][j][k] ;
                    }
                }
            }
            break;
        default :
            cout << "ERROR!!!" << endl ;
            MirrorRGB() ;
            break;
    }
    save = false ;
    MenuRGB();
}

void RGB1::ShuffleRGB(){
}

void RGB1::BlurRGB() {
    int b = 4 ;
    while(b--){
        for(int i = 0 ; i < SIZE ; ++i){
            for(int j = 0 ; j < SIZE ; ++j){
                for(int k = 0 ; k < RGB ; ++k){
                    int cnt = 1 ;
                    int y=imagergb[i][j][k];
                    if(((validRGB(i-1,j-1)&&(y+=imagergb[i-1][j-1][k])&&++cnt)
                        ||(validRGB(i-1,j)&&(y+=imagergb[i-1][j][k])&&++cnt)
                        ||(validRGB(i-1,j+1)&&(y+=imagergb[i-1][j+1][k])&&++cnt)
                        ||(validRGB(i,j-1)&&(y+=imagergb[i][j-1][k])&&++cnt)
                        ||(validRGB(i+1,j-1)&&(y+=imagergb[i+1][j-1][k])&&++cnt)
                        ||(validRGB(i+1,j)&&(y+=imagergb[i+1][j][k])&&++cnt)
                        ||(validRGB(i+1,j+1)&&(y+=imagergb[i+1][j+1][k])&&++cnt)
                        ||(validRGB(i,j+1)&&(y+=imagergb[i][j+1][k])&&++cnt))){
                        imagergb[i][j][k] = y/cnt ;
                    }
                }
            }
        }
    }
    save= false;
    MenuRGB();
}

void RGB1::CropRGB() {
    cout<<"Please enter x y l w:"<<flush;
    int x,y,l,w;
    cin>>x>>y>>l>>w;
    for (int i = 0; i <256; ++i){
        for (int j = 0; j <256 ; ++j){
            for(int k = 0 ; k < RGB ; ++k){
                if((i>=x&&i<=x+l)&&(j>=y&&j<=y+w)){
                    continue;
                }
                imagergb[i][j][k]=255;
            }
        }
    }
    save= false;
    MenuRGB();
}

void RGB1::Skew_RightRGB() {
    cout<<"Please enter degree to skew right:"<<flush;
    double a;
    cin>>a;
    a*=3.14/180;
    int ed=(256*tan(a));
    unsigned char imgrgb[SIZE][SIZE+ed][RGB];
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE+ed ; ++j){
            for(int k = 0 ; k < RGB ; ++k){
                imgrgb[i][j][k]=255;
            }
        }
    }
    for (int i = 0; i < SIZE; ++i){
        int o=(256-i)*tan(a);
        for (int j = 0; j+o < SIZE+ed ; ++j){
            for(int k = 0 ; k < RGB ; ++k){
                if(j < SIZE)
                    imgrgb[i][j+o][k]=imagergb[i][j][k];
            }
        }
    }
    for(int i = 0 ; i < SIZE ; ++i){
        for(int j = 0 ; j < SIZE+ed ; ++j){
            for(int k = 0 ; k < RGB ; ++k){
                imagergb[i][((j*255)/(255+ed))][k] = imgrgb[i][j][k] ;
            }
        }
    }
    save = false ;
    MenuRGB();
}

void RGB1::Skew_UpRGB() {
    cout<<"Please enter degree to skew up:"<<flush;
    double a;
    cin>>a;
    a*=3.14/180;
    int ed=(256*tan(a));
    unsigned char imgrgb[SIZE][SIZE+ed][RGB];
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE+ed ; ++j){
            for(int k = 0 ; k < RGB ; ++k){
                imgrgb[i][j][k]=255;
            }
        }
    }
    for (int i = 0; i < SIZE; ++i){
        int o=(256-i)*tan(a);
        for (int j = 0; j+o < SIZE+ed ; ++j){
            for(int k = 0 ; k < RGB ; ++k){
                if(j < SIZE)
                    imgrgb[i][j+o][k]=imagergb[j][i][k];
            }
        }
    }
    for(int i = 0 ; i < SIZE ; ++i){
        for(int j = 0 ; j < SIZE+ed ; ++j){
            for(int k = 0 ; k < RGB ; ++k){
                imagergb[((j*255)/(255+ed))][i][k] = imgrgb[i][j][k] ;
            }
        }
    }
    save = false ;
    MenuRGB();
}

void RGB1::ExitRGB() {
    exit = true ;
    if (!save){
        cout << "YOU FORGOT TO SAVE IMAGE DO YOU WANT TO SAVE IT ?? " << flush;
        string y;
        cin >> y;
        if (y == "YES" || y == "yes" || y == "Yes" || y == "y" || y == "Y"){
            saveImageRGB();
        }
    }
}