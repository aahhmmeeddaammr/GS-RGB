#include <bits/stdc++.h>
#include "GS.h"
#include "bmplib.h"
#include "bmplib.cpp"
using namespace std ;

bool GS::valid(int i, int j) {
    return i<SIZE&&j<SIZE &&i>=0&&j>=0 ;
}

void GS::equal() {
    for(int i = 0; i < 256 ; ++i){
        for(int j = 0; j < 256; ++j){
            image[i][j]=image2[i][j];
        }
    }
}

void GS::saveImage() {
    char imageFileName[100];
    cout << endl << "Enter the target image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
    save= true;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j]=temp[i][j];
        }
    }
    cout << endl << "Image saved successfully !!" << endl ;
    if(!exit)
        Menu();
}

void GS::loadImage() {
    char imageFileName[100];
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    if(readGSBMP(imageFileName, image) != 1) {
        readGSBMP(imageFileName, temp);
    }
    else{
        loadImage();
    }
    Menu();
}

void GS::Menu() {
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
            Exit();
            break;
        case 1:
            Black_White();
            break;
        case 2:
            Invert();
            break;
        case 3:
            Merge();
            break;
        case 4:
            Flip();
            break;
        case 5:
            Rotate();
            break;
        case 6:
            Darken_Lighten();
            break;
        case 7:
            Detect_Edge();
            break;
        case 8:
            Enlarge();
            break;
        case 9:
            Shrink();
            break;
        case 10:
            Mirror();
            break;
        case 11:
            Shuffle();
            break;
        case 12:
            Blur();
            break;
        case 13:
            Crop();
            break;
        case 14:
            Skew_Right();
            break;
        case 15:
            Skew_Up();
            break;
        case 16:
            saveImage();
            break;
        default:
            cout<<"ERROR!!"<<endl;
            Menu();
            break;
    }

}

void GS::Black_White() {
    for(int i=0;i<SIZE;i++){
        for (int j = 0; j <SIZE ; ++j){
            if(image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
    save = false;
    Menu();
}

void GS::Invert() {
    for(int i=0;i < SIZE;i++){
        for (int j = 0; j < SIZE ; ++j) {
            image[i][j]=255-image[i][j];
        }
    }
    save= false;
    Menu();
}

void GS::Merge() {
    char imageFileName[100];
    cout << "   Please enter name of image file to merge with: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    if(readGSBMP(imageFileName, image2) != 1){
        for(int i=0;i<SIZE;i++){
            for (int j = 0; j <SIZE ; ++j){
                image[i][j]=(image[i][j]+image2[i][j])/2;
            }
        }
        save= false;
        cout << endl << "Filter Applied Successfully !!" << endl ;
        Menu();
    }else{
        cout << "ERROR!!" << endl ;
        Merge();
    }
}

void GS::Flip() {
    char f;
    cout <<"   Flip (h)orizontally or (v)ertically ? "<< flush;
    cin >> f;
    int p = -1 , m ;
    for(int i = SIZE-1; i >= 0; i--){
        m=0;
        p++;
        for (int j = SIZE-1; j >= 0; j--){
            image2[m++][p] = image[i][j];
        }
    }
    for(int i = 0; i < SIZE / 2; i++) {
        for (int j = i; j < SIZE - i - 1; j++) {
            if(f == 'v') {
                int t = image2[i][j];
                image2[i][j] = image2[SIZE - 1 - j][i];
                image2[SIZE - 1 - j][i] = image2[SIZE - 1 - i][SIZE - 1 - j];
                image2[SIZE - 1 - i][SIZE - 1 - j] = image2[j][SIZE - 1 - i];
                image2[j][SIZE - 1 - i] = t;
            }
            else if(f == 'h'){
                int t=image2[i][j];
                image2[i][j]=image2[j][SIZE-i-1];
                image2[j][SIZE-i-1]=image2[SIZE-i-1][SIZE-j-1];
                image2[SIZE-i-1][SIZE-j-1]=image2[SIZE-j-1][i];
                image2[SIZE-j-1][i]=t;
            }
        }
    }
    if(f != 'h' && f != 'v'){
        cout << "ERROR!!" << endl;
        Flip();
    }
    else{
        equal();
        save= false;
        cout << endl << "Filter Applied Successfully !!" << endl ;
        Menu();
    }
}

void GS::Rotate() {
    int rotate;
    cout<<"   Rotate (90), (180) or (270) degrees? "<<flush;
    cin>>rotate;
    if(rotate == 90 || rotate == 180 || rotate == 270){
        int flips = rotate/90 ;
        while(flips--){
            for (int i = 0; i < SIZE/2; i++){
                for (int j = i; j<SIZE-i-1; j++){
                    int t = image[i][j];
                    image[i][j] = image[SIZE-1-j][i];
                    image[SIZE-1-j][i] = image[SIZE-1-i][SIZE-1-j];
                    image[SIZE-1-i][SIZE-1-j] = image[j][SIZE-1-i];
                    image[j][SIZE-1-i] = t;
                }
            }
        }
        save= false;
        cout << endl << "Filter Applied Successfully !!" << endl ;
        Menu();
    }
    else{
        cout<<"ERROR!!"<<endl;
        Rotate();
    }
}

void GS::Darken_Lighten() {
    char mood;
    cout<<"   Do you want to (d)arken or (l)ighten? "<<flush;
    cin>>mood;
    if(mood=='d'){
        for(int i = 0; i < SIZE; ++i){
            for (int j = 0; j < SIZE; ++j){
                image[i][j]*=0.5;
            }
        }
        save = false;
        cout << endl << "Filter Applied Successfully !!" << endl ;
        Menu();
    }
    else if(mood=='l'){
        for(int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j){
                image[i][j]+=(255-image[i][j])/2;
            }
        }
        save = false;
        cout << endl << "Filter Applied Successfully !!" << endl ;
        Menu();
    }
    else{
        cout<<"ERROR!!"<<endl ;
        Darken_Lighten();
    }
}

void GS::Detect_Edge() {
    for(int i=0;i<SIZE;i++){
        for (int j = 0; j <SIZE ; ++j){
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
    for(int i=0;i<SIZE;i++){
        for (int j = 0; j <SIZE ; ++j){
            if(image[i][j]==0&&
               ((valid(i-1,j-1)&&image[i-1][j-1]==255)
                ||(valid(i-1,j)&&image[i-1][j]==255)
                ||(valid(i-1,j+1)&&image[i-1][j+1]==255)
                ||(valid(i,j-1)&&image[i][j-1]==255)
                ||(valid(i+1,j-1)&&image[i+1][j-1]==255)
                ||(valid(i+1,j)&&image[i+1][j]==255)
                ||(valid(i+1,j+1)&&image[i+1][j+1]==255)
                ||(valid(i,j+1)&&image[i][j+1]==255)))
            {
                image2[i][j]=0;
            }
            else{
                image2[i][j]=255;
            }
        }
    }
    equal();
    Menu();
}

void GS::Enlarge() {
    int qu;
    cout << "Which quarter to enlarge 1, 2, 3 or 4?" << flush;
    cin >> qu;
    switch (qu) {
        case 1 :
            for (int i = 0; i < 128; ++i) {
                for (int j = 0; j < 128; ++j) {
                    image3[i][j] = image[i][j];
                }
            }
            for (int i = 0; i < 256; ++i) {
                for (int j = 0; j < 256; ++j) {
                    image2[i][j] = image3[i / 2][j / 2];
                }
            }

            break;
        case 2 :
            for (int i = 0; i < 128; ++i) {
                for (int j = 127; j < 256; ++j) {
                    image3[i][j - 127] = image[i][j];
                }
            }
            for (int i = 0; i < 256; ++i) {
                for (int j = 0; j < 256; ++j) {
                    image2[i][j] = image3[i / 2][j / 2];
                }
            }

            break;
        case 3 :
            for(int i = 127 ; i < 256 ; ++i){
                for(int j = 0 ; j < 128 ; ++j){
                    image3[i-127][j] = image[i][j] ;
                }
            }
            for(int i = 0 ; i < 256 ; ++i){
                for(int j = 0 ; j < 256 ; ++j){
                    image2[i][j] = image3[i/2][j/2] ;
                }
            }

            break ;
        case 4 :
            for(int i = 127 ; i < 256 ; ++i){
                for(int j = 127 ; j < 256 ; ++j){
                    image3[i-127][j-127] = image[i][j] ;
                }
            }
            for(int i = 0 ; i < 256 ; ++i){
                for(int j = 0 ; j < 256 ; ++j){
                    image2[i][j] = image3[i/2][j/2] ;
                }
            }

            break ;
        default:
            cout << "ERROR!!!" << endl ;
            Enlarge() ;
            break;
    }
    save = false ;
    equal();
    Menu();
}

void GS::Shrink() {
    cout<<"Shrink to (1/(2)), (1/(3)) or (1/(4))?"<<flush;
    int Shrink;
    cin>>Shrink;
    for (int i = 0; i <SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image2[i][j] = 255;
            image2[i / Shrink][j / Shrink] = image[i][j];
        }
    }
    save= false;
    equal();
    Menu();
}

void GS::Mirror() {
    char c;
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?" << flush;
    cin >> c;
    switch (c) {
        case 'l' :
            for (int i = 0; i < 256; ++i) {
                for (int j = 0; j < 256; ++j) {
                    image[i][255 - j] = image[i][j];
                }
            }
            break;
        case 'r' :
            for (int i = 255; i >= 0; --i) {
                for (int j = 255; j >= 0; --j) {
                    image[i][255 - j] = image[i][j];
                }
            }
            break;
        case 'd' :
            for (int i = 255; i >= 0; --i) {
                for (int j = 255; j >= 0; --j) {
                    image[255 - i][j] = image[i][j];
                }
            }
            break;
        case 'u' :
            for (int i = 0; i < 256; ++i) {
                for (int j = 0; j < 256; ++j) {
                    image[255 - i][j] = image[i][j];
                }
            }
            break;
        default :
            cout << "ERROR!!!" << endl;
            Mirror();
            break;
    }
    save = false;
    Menu();
}

void GS::Shuffle() {
    int a , b , c , d ;
    cout << "New order of quarters ?" << flush ;
    cin >> a >> b >> c >> d ;
    vector<int> v ;
    vector<pair<int,int>> beg{{0,0},{0,127},{127,0},{127,127}};
    vector<pair<int,int>> end{{127,127},{127,255},{255,127},{255,255}};
    v.emplace_back(a) ; v.emplace_back(b) ; v.emplace_back(c) ; v.emplace_back(d) ;
    int o = 0 ;
    for(auto &k : v){
        int y=beg[o].first;
        for(int i = beg[k-1].first  ; i <= end[k-1].first ; ++i){
            int h=beg[o].second;
            for(int j = beg[k-1].second ; j <= end[k-1].second ; ++j)
            {
                if(h<=end[o].second){
                    image2[y][h]=image[i][j];
                    h++;
                }
            }
            if(y<=end[o].first)
            {
                y++;
            }
        }
        o++;
    }
    equal();
    save = false ;
    Menu();
}

void GS::Blur() {
    int b = 4 ;
    while(b--) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                int cnt = 1;
                int y = image[i][j];
                if (((valid(i - 1, j - 1) && (y += image[i - 1][j - 1]) && ++cnt)
                     || (valid(i - 1, j) && (y += image[i - 1][j]) && ++cnt)
                     || (valid(i - 1, j + 1) && (y += image[i - 1][j + 1]) && ++cnt)
                     || (valid(i, j - 1) && (y += image[i][j - 1]) && ++cnt)
                     || (valid(i + 1, j - 1) && (y += image[i + 1][j - 1]) && ++cnt)
                     || (valid(i + 1, j) && (y += image[i + 1][j]) && ++cnt)
                     || (valid(i + 1, j + 1) && (y += image[i + 1][j + 1]) && ++cnt)
                     || (valid(i, j + 1) && (y += image[i][j + 1]) && ++cnt))) {
                    image[i][j] = y / cnt;
                }
            }
        }
    }
    save= false;
    Menu();
}

void GS::Crop() {
    cout<<"Please enter x y l w:"<<flush;
    int x,y,l,w;
    cin>>x>>y>>l>>w;
    for(int i = 0; i <256; ++i){
        for (int j = 0; j <256 ; ++j){
            if((i>=x&&i<=x+l)&&(j>=y&&j<=y+w)){
                continue;
            }
            image[i][j]=255;
        }
    }
    save= false;
    Menu();
}

void GS::Skew_Right() {
    cout<<"Please enter degree to skew right:"<<flush;
    double a;
    cin>>a;
    a*=3.14/180;
    int ed=(256*tan(a));
    unsigned char img[SIZE][SIZE+ed];
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE+ed ; ++j){
            img[i][j]=255;
        }
    }
    for (int i = 0; i < SIZE; ++i){
        int o=(256-i)*tan(a);
        for (int j = 0; j+o < SIZE+ed ; ++j){
            if(j < SIZE)
                img[i][j+o]=image[i][j];
        }
    }
    for(int i = 0 ; i < SIZE ; ++i){
        for(int j = 0 ; j < SIZE+ed ; ++j){
            image[i][((j*255)/(255+ed))] = img[i][j] ;
        }
    }
    save = false ;
    Menu();

}

void GS::Skew_Up() {
    cout<<"Please enter degree to skew up:"<<flush;
    double a;
    cin>>a;
    a*=3.14/180;
    int ed=(256*tan(a));
    unsigned char img[SIZE][SIZE+ed];
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE+ed ; ++j){
            img[i][j]=255;
        }
    }
    for (int i = 0; i < SIZE; ++i){
        int o=(256-i)*tan(a);
        for (int j = 0; j+o < SIZE+ed ; ++j){
            if(j < SIZE)
                img[i][j+o]=image[j][i];
        }
    }
    for(int i = 0 ; i < SIZE ; ++i){
        for(int j = 0 ; j < SIZE+ed ; ++j){
            image[((j*255)/(255+ed))][i] = img[i][j] ;
        }
    }
    save = false ;
    Menu();
}

void GS::Exit() {
    exit = true ;
    if (!save){
        cout << "YOU FORGOT TO SAVE IMAGE DO YOU WANT TO SAVE IT ?? " << flush;
        string y;
        cin >> y;
        if (y == "YES" || y == "yes" || y == "Yes" || y == "y" || y == "Y"){
            saveImage();
        }
    }
}