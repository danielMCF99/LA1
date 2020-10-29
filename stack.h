//
// Created by Carlos Beiramar on 2019-04-30.
//

#ifndef UNTITLED_STACK_H
#define UNTITLED_STACK_H

#include "estado.h"

struct Node {
    ESTADO data;
    struct Node* next;
};


void push(ESTADO data);
int isEmpty();
ESTADO elementoTopo();
void pop();

#endif //UNTITLED_STACK_H

