// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:				main.cpp
// Last Modification Date:	xx/xx/xxxx
// Author1 and ID and Group:	Mohanad Abdullrahem Abdullrahman 20220348
// Author2 and ID and Group:	Ahmed Ehab Shehata Ali 20220012
// Author3 and ID and Group:	xxxxx xxxxx
// Teaching Assistant:		xxxxx xxxxx
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

int main()
{
  bool cont;
  cout << "Ahlan ya user ya habibi\n";
  loadImage();
  do
  {
    cont = applyFilter();
  } while (cont);
}

bool applyFilter()
{
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
  case '9':
    shrinkImage();
    break;
  case 'a':
    mirrorImage();
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
  cout << "\n\nPlease select a filter to apply or 0 to exit:\n";
  cout << "1- Black & White Filter\n";
  cout << "2- Invert Filter\n";
  cout << "3- Merge Filter \n";
  cout << "4- Flip Image\n";
  cout << "5- Rotate Image\n";
  cout << "6- Darken and Lighten Image \n";
  cout << "7-Detect Image Edges \n";
  // cout << "8-Enlarge Image\n";
  cout << "9-Shrink Image\n";
  cout << "a-Mirror 1/2 Image\n";
  // cout << "b-Shuffle Image\n";
  cout << "c-Blur Image\n";
  cout << "d-Crop Image\n";
  // cout << "e-Skew Image Right  \n";
  // cout << "f-Skew Image Up  \n";
  cout << "s- Save the image to a file\n";
  cout << "0- Exit\n";
  cin >> filter;
  return filter;
}

// load the original image
void loadImage()
{
  char imageFileName[100];

  cout << "Please enter file name of the image to process: ";
  cin >> imageFileName;

  strcat(imageFileName, ".bmp");
  readGSBMP(imageFileName, image);
}

// load the second image to merge with the first
void loadMergeImage()
{
  char imageFileName[100];

  cout << "Please enter file name of the image to merge with: ";
  cin >> imageFileName;

  strcat(imageFileName, ".bmp");
  readGSBMP(imageFileName, mergeImage);
}

// save the filtered image
void saveImage()
{
  char imageFileName[100];

  cout << "Enter the target image file name: ";
  cin >> imageFileName;

  strcat(imageFileName, ".bmp");
  writeGSBMP(imageFileName, filteredImage);
}

// ##############################
// ######### The Filters ########
// ##############################
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

void invertFilter()
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      // turning evrey pixle to the opposite level of brightness
      filteredImage[i][j] = 255 - image[i][j];
    }
  }
}

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
void rotateImage() {}

void darkenAndLightenImage()
{
  char c;
  cout << "Do you want to (d)arken or (l)ighten? ";
  cin >> c;
  float factor = c == 'l' ? 1.5 : 0.5;
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      // Make the image lighter or darker by 50%
      // and make sure to stay in the range 0-255
      filteredImage[i][j] = round(image[i][j] * factor) >= 255 ? 255 : round(image[i][j] * factor);
    }
  }
}

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
void enlargeImage() {}

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
void shuffleImage() {}

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
void skewImageRight() {}
void skewImageUp() {}