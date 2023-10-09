// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name: CS213-2023-20220012-20220034-20220348-Part1.cpp
// Last Modification Date:	xx/xx/xxxx
// Member1 and ID  :Ahmed Ehab Shehata Ali  20220012
// Member1's email :

// Member2 and ID  :Ahmed Mohamed Amer Ahmed    20220034
// Member2's email :ahmedamer42214953@gmail.com

// Member3 and ID  :Mohanad Abdullrahem Abdullrahman    20220348
// Member3's email :
// Purpose:..........

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include "bmplib.cpp"
using namespace std;

// the orginal image
unsigned char image[SIZE][SIZE];
// a copy to save the changes without modifing the original
unsigned char filteredImage[SIZE][SIZE];
// the image to use when using the merge filter
unsigned char mergeImage[SIZE][SIZE];
// the 4 quarters of the images for shuffle image
unsigned char s1[128][128];
unsigned char s2[128][128];
unsigned char s3[128][128];
unsigned char s4[128][128];

void loadImage();
void saveImage();
void loadMergeImage();
char getTheFilterNameFromUser();
bool applyFilter();
void blackAndWhiteFilter();
void invertFilter();
void mergeFilter();
void flipImage();
void darkenAndLightenImage();
void rotateImage();
void detectImageEdges();
void enlargeImage();
void shrinkImage();
void mirrorImage();
void shuffleImage();
void blurImage();
void cropImage();
void skewImageRight();
void skewImageUp();

int main(){
  bool cont;
  cout << "Ahlan ya user ya habibi\n";
  loadImage();
  do
  {
    cont = applyFilter();
  } while (cont);
}

bool applyFilter(){
  char filter = getTheFilterNameFromUser();
  switch (filter)
  {
  case '1':
    blackAndWhiteFilter();
    break;
  case '2':
    invertFilter();
    break;
  case '3':
    loadMergeImage();
    mergeFilter();
    break;
  case '4':
    flipImage();
    break;
  case '5':
    rotateImage();
    break;
  case '6':
    darkenAndLightenImage();
    break;
  case '7':
    detectImageEdges();
    break;
case '8':
    enlargeImage();
    break;
  case '9':
    shrinkImage();
    break;
  case 'a':
    mirrorImage();
    break;
  case 'b':
    shuffleImage();
    break;
  case 'c':
    blurImage();
    break;
  case 'd':
    cropImage();
    break;
  case 's':
    saveImage();
    break;
  case '0':
    return false;
    break;
  }
  return true;
}

char getTheFilterNameFromUser()
{
  char filter;
  cout << "\nPlease select a filter to apply or 0 to exit:\n";
  cout << "1- Black & White Filter\n";
  cout << "2- Invert Filter\n";
  cout << "3- Merge Filter \n";
  cout << "4- Flip Image\n";
  cout << "5- Rotate Image\n";
  cout << "6- Darken and Lighten Image \n";
  cout << "7- Detect Image Edges \n";
  cout << "8- Enlarge Image\n";
  cout << "9- Shrink Image\n";
  cout << "a- Mirror 1/2 Image\n";
  cout << "b- Shuffle Image\n";
  cout << "c- Blur Image\n";
  cout << "d- Crop Image\n";
  cout << "e- Skew Image Right  \n";
  cout << "f- Skew Image Up  \n";
  cout << "s- Save the image to a file\n";
  cout << "0- Exit\n";
  cin >> filter;
  return filter;
}

// load the original image
void loadImage()
{
  char imageFileName[100];

  cout << "Please enter file name of the image to process: \n";
  cin >> imageFileName;

  strcat(imageFileName, ".bmp");
  readGSBMP(imageFileName, image);
}

// load the second image to merge with the first
void loadMergeImage()
{
  char imageFileName[100];

  cout << "Please enter file name of the image to merge with: \n";
  cin >> imageFileName;

  strcat(imageFileName, ".bmp");
  readGSBMP(imageFileName, mergeImage);
}

// save the filtered image
void saveImage()
{
  char imageFileName[100];

  cout << "Please enter target file name: ";
  cin >> imageFileName;

  strcat(imageFileName, ".bmp");
  writeGSBMP(imageFileName, filteredImage);
}

// ##############################
// ######### The Filters ########
// ##############################

// Filter 1
void blackAndWhiteFilter()
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (image[i][j] > 127)
        filteredImage[i][j] = 255;
      else
        filteredImage[i][j] = 0;
    }
  }
}

// Filter 2
void invertFilter()
{
  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      // turning every pixel to the opposite level of brightness
      filteredImage[i][j] = 255 - image[i][j];
    }
  }
}

// Filter 3
void mergeFilter()
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      filteredImage[i][j] = (image[i][j] + mergeImage[i][j]) / 2;
    }
  }
}

// Filter 4
void flipImage()
{
  int i, j;
  char flipType;

  cout << "Flip (h)orizontally or (v)ertically ? ";
  cin >> flipType;

  if (flipType == 'h' || flipType == 'H')
  {
    for (i = 0; i < SIZE; i++)
    {
      for (j = 0; j < SIZE; j++)
      {
        // Flip the image horizontally
        filteredImage[i][j] = image[i][SIZE - 1 - j];
      }
    }
  }
  else if (flipType == 'v' || flipType == 'V')
  {
    for (i = 0; i < SIZE; i++)
    {
      for (j = 0; j < SIZE; j++)
      {
        // Flip the image vertically
        filteredImage[i][j] = image[SIZE - 1 - i][j];
      }
    }
  }
  else
  {
    // Output Error messege to the user
    cout << "Invalid flip\n";
  }
}

// Filter 5
void rotateImage() {
    cout<<"Rotate (90), (180) or (270) degrees?\n";
    int degree; cin>>degree;
    if(degree == 180){
        for(int i=0 ; i<SIZE; i++){
            for(int j=0 ; j<SIZE; j++){
                // the image rotate 180 degrees
                filteredImage[i][j]=image[255-i][255-j];
            }
        }
    }

    else if(degree == 270){
        for(int i=0 ; i<SIZE; i++){
            for(int j=0 ; j<SIZE; j++){
                // the image rotate 270 degrees
                filteredImage[i][j]=image[j][255-i];
            }
        }
    }

    else if(degree == 90){
        for(int i=0 ; i<SIZE; i++){
            for(int j=0 ; j<SIZE; j++){
                // the image rotate 90 degrees
                filteredImage[i][j]=image[255-j][i];
            }
        }
    }
}

// Filter 6
void darkenAndLightenImage(){
    cout << "Do you want to (d)arken or (l)ighten? \n";
    char c;
    cin >> c;
    if(c== 'l' || c=='L'){
        for(int i=0 ; i<SIZE ; i++){
            for(int j=0 ; j<SIZE ; j++){
                // the image get lighter by 50%
                filteredImage[i][j]=(image[i][j]+255)/2;
            }
        }
    }
    else if(c =='d' || c == 'D'){
        for(int i=0 ; i<SIZE ; i++){
            for(int j=0 ; j<SIZE ; j++){
                // the image get darker by 50%
                filteredImage[i][j]=(image[i][j])/2;
            }
        }
    }
}

// Filter 7
void detectImageEdges()
{
  int i, j;

  for (i = 0; i < SIZE; ++i)
  {
      for (j = 0; j < SIZE; ++j)
      {
          if (j > 0 && j < SIZE - 1)
          {
              // Check for possible casess to detect image edges
              if (image[i][j - 1] >= 127 && image[i][j] < 127 && image[i][j + 1] >= 127)
              {
                  filteredImage[i][j - 1] = 255;
                  filteredImage[i][j] = 0;
                  filteredImage[i][j + 1] = 255;
              }
              else if (image[i][j - 1] < 127 && image[i][j] < 127 && image[i][j + 1] >= 127)
              {
                  filteredImage[i][j - 1] = 255;
                  filteredImage[i][j] = 0;
                  filteredImage[i][j + 1] = 255;
              }
              else if (image[i][j - 1] >= 127 && image[i][j] < 127 && image[i][j + 1] < 127)
              {
                  filteredImage[i][j - 1] = 255;
                  filteredImage[i][j] = 0;
                  filteredImage[i][j + 1] = 255;
              }
              else if (image[i][j - 1] >= 127 && image[i][j] >= 127 && image[i][j + 1] < 127)
              {
                  filteredImage[i][j - 1] = 255;
                  filteredImage[i][j] = 255;
                  filteredImage[i][j + 1] = 0;
              }
              else
                filteredImage[i][j] = 255;
          }
          if (i > 0 && i < SIZE)
          {
            if (image[i - 1][j] >= 127 && image[i][j] < 127)
            {
              filteredImage[i - 1][j] = 255;
              filteredImage[i][j] = 0;
            }
            if (image[i][j] < 127 && image[i][j + 1] >= 127)
            {
              filteredImage[i][j] = 0;
              filteredImage[i + 1][j] = 255;
            }
            else
              filteredImage[i][j] = 255;
          }
          else
              filteredImage[i][j] = 255;
      }
  }
}

// Filter 8
void enlargeImage() {
    cout<<"Which quarter to enlarge 1, 2, 3, or 4?\n";
    int quart ; cin>>quart;
    int n=-2 , m=0;
    if(quart ==1){
        for(int i=0 ; i<SIZE/2 ; i++){
            n+=2; m=0;
            for(int j=0 ; j<SIZE/2 ; j++){
                filteredImage[n][m]=image[i][j];       filteredImage[n][m+1]=image[i][j];
                filteredImage[n+1][m]=image[i][j];  filteredImage[n+1][m+1]=image[i][j];
                m+=2;
            }
        }
    }

    else if(quart ==2){
        for(int i=0 ; i<SIZE/2 ; i++){
            n+=2; m=0;
            for(int j=127 ; j<SIZE ; j++){
                filteredImage[n][m]=image[i][j];       filteredImage[n][m+1]=image[i][j];
                filteredImage[n+1][m]=image[i][j];  filteredImage[n+1][m+1]=image[i][j];
                m+=2;
            }
        }
    }

    else if(quart ==3){
        for(int i=127 ; i<SIZE ; i++){
            n+=2; m=0;
            for(int j=0 ; j<128 ; j++){
                filteredImage[n][m]=image[i][j];      filteredImage[n][m+1]=image[i][j];
                filteredImage[n+1][m]=image[i][j];  filteredImage[n+1][m+1]=image[i][j];
                m+=2;
            }
        }
    }

    else if(quart ==4){
        for(int i=127 ; i<SIZE ; i++){
            n+=2; m=0;
            for(int j=127 ; j<SIZE ; j++){
                filteredImage[n][m]=image[i][j];       filteredImage[n][m+1]=image[i][j];
                filteredImage[n+1][m]=image[i][j];  filteredImage[n+1][m+1]=image[i][j];
                m+=2;
            }
        }
    }
}

// Filter 9
void shrinkImage()
{
  // make the filtered image white
  // so even if i used the shrink filter
  // multiple time the images do not overlap
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      filteredImage[i][j] = 255;
    }
  }

  // get the ratio from the user
  int factor;
  string ratio;
  cout << "Shrink to (1/2), (1/3) or (1/4)? ";
  cin >> ratio;
  factor = ratio[2] - '0';

  for (int i = 0, k = 0; i < SIZE; i += factor, k++)
  {
    for (int j = 0, l = 0; j < SIZE; j += factor, l++)
    {

      int sum = 0;
      for (int m = i; m < i + factor; m++)
      {
        for (int n = j; n < j + factor; n++)
        {
          sum += image[m][n];
        }
      }

      filteredImage[k][l] = sum / (factor * factor);
    }
  }
}

// Filter a
void mirrorImage()
{
  int i, j;
  char mirrorSide;
  const int SIZE_HALF = SIZE / 2;

  cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? ";
  cin >> mirrorSide;

  // Check for mirror side
  if (mirrorSide == 'l' || mirrorSide == 'L')
  {
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        if (j < SIZE_HALF)
          filteredImage[i][j] = image[i][j];
        else
          // Store the horizontal flip of the first half of image in first half of filtered image
          filteredImage[i][j] = image[i][SIZE - 1 - j];
      }
    }
  }
  else if (mirrorSide == 'r' || mirrorSide == 'R')
  {
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        if (j < SIZE_HALF)
          // Store the horizontal flip of the second half of image in first half of filtered image
          filteredImage[i][j] = image[i][SIZE - 1 - j];
        else
          filteredImage[i][j] = image[i][j];
      }
    }
  }
  else if (mirrorSide == 'u' || mirrorSide == 'U')
  {
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        if (i < SIZE_HALF)
          filteredImage[i][j] = image[i][j];
        else
          // Store the vertical flip of the first half of image in second half of filtered image
          filteredImage[i][j] = image[SIZE - 1 - i][j];
      }
    }
  }
  else if (mirrorSide == 'd' || mirrorSide == 'D')
  {
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        if (i < SIZE_HALF)
          // Store the vertical flip of the second half of image in first half of filtered image
          filteredImage[i][j] = image[SIZE - 1 - i][j];
        else
          filteredImage[i][j] = image[i][j];
      }
    }
  }
  else
    // Output Error messege to the user
    cout << "Invalid side\n";
}

// Filter b
void shuffleImage() {
    cout<<"New order of quarters ?\n";
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                s1[i][j]=image[i][j];
            }
        }

        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                s2[i][j]=image[i][j+128];
            }
        }

        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                s3[i][j]=image[i+128][j];
            }
        }

        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                s4[i][j]=image[i+128][j+128];
            }
        }

        int v, x, y, z;
        cin>>v>>x>>y>>z;
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                if(v==1)
                    filteredImage[i][j]=s1[i][j];
                else if(v==2)
                    filteredImage[i][j]=s2[i][j];
                else if(v==3)
                    filteredImage[i][j]=s3[i][j];
                else if(v==4)
                    filteredImage[i][j]=s4[i][j];
            }
        }

        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                if(x==1)
                    filteredImage[i][j+128]=s1[i][j];
                else if(x==2)
                    filteredImage[i][j+128]=s2[i][j];
                else if(x==3)
                    filteredImage[i][j+128]=s3[i][j];
                else if(x==4)
                    filteredImage[i][j+128]=s4[i][j];
            }
        }

        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                if(y==1)
                    filteredImage[i+128][j]=s1[i][j];
                else if(y==2)
                    filteredImage[i+128][j]=s2[i][j];
                else if(y==3)
                    filteredImage[i+128][j]=s3[i][j];
                else if(y==4)
                    filteredImage[i+128][j]=s4[i][j];
            }
        }

        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                if(z==1)
                    filteredImage[i+128][j+128]=s1[i][j];
                else if(z==2)
                    filteredImage[i+128][j+128]=s2[i][j];
                else if(z==3)
                    filteredImage[i+128][j+128]=s3[i][j];
                else if(z==4)
                    filteredImage[i+128][j+128]=s4[i][j];
            }
        }
}

// Filter c
void blurImage()
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {

      int sum = 0;
      for (int k = i - 1; k < i + 2; k++)
      {
        for (int l = j - 1; l < j + 2; l++)
        {
          if (k < 0 || l < 0 || k > 255 || l > 255)
          {
            continue;
          }
          sum += image[k][l];
        }
      }

      filteredImage[i][j] = sum / 9;
    }
  }
}

// Filter d
void cropImage()
{
  int x, y, len, width, i, j;

    cout << "Please enter x y l w: ";
    cin >> x >> y >> len >> width;

    for (i = 0; i < SIZE; i++)
    {
      for (j = 0; j < SIZE; j++)
        // Make the filtered image white
        filteredImage[i][j] = 255;
    }
    for (i = y; i < len + y; i++)
    {
        for (j = x; j < width + x; j++)
        {
          // Keep the required rectangle or square of the image
          filteredImage[i][j] = image[i][j];
        }
    }
}

// Filter e
void skewImageRight() {}

// Filter f
void skewImageUp() {}
