//
//  Snake.c
//  Snake
//
//  Created by Alexandre Kahn on 11/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//

#include "Snake.h"
static struct Snake** list;

struct Snake *bodypart(int i){
    return list[i];
}

struct Coordinate {
    int x, y;
};

