
// File:        main.cpp
// Author:      cheeren
// Date:        2018-03-31
// Description: Partial test of PA4 functionality
//              Reads Point data from external files
//              Produces PNG images of the point sets


#include "path.h"
#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"

using namespace cs221util;
using namespace std;

int main()
{
    
//        PNG origIm1;
//        origIm1.readFromFile("images/fun.png");
//        pair<int,int> start1(211,0);
//        pair<int,int> end1(211,213);
//        path test(origIm1,start1,end1);
//        PNG out1 = test.render();
//        out1.writeToFile("images/test__out.png");
//
    PNG origIm1;
    origIm1.readFromFile("images/snake.png");
    pair<int,int> start1(2,2);
    pair<int,int> end1(637,477);
    path snake(origIm1,start1,end1);
    printf("%d\n",snake.length());
    PNG out1 = snake.render();
    out1.writeToFile("images/snakePath.png");
//
    PNG origIm2;
    origIm2.readFromFile("images/maze.png");
    pair<int,int> start2(3,10);
    pair<int,int> end2(637,477);
    path maze(origIm2,start2,end2);
    PNG out2 = maze.render();
    printf("%d\n",maze.length());
    out2.writeToFile("images/mazePath.png");

    PNG origIm3;
    origIm3.readFromFile("images/sunshine.png");
    pair<int,int> start3(320,420);
    pair<int,int> end3(100,100);
    path sunshine(origIm3,start3,end3);
    PNG out3 = sunshine.render();
    printf("%d\n",sunshine.length());
    out3.writeToFile("images/sunshinePath.png");

  return 0;
}
