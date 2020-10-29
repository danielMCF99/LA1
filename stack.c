//
// Created by Carlos Beiramar on 2019-04-30.
//

#include "stack.h"
#include "estado.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


//apontador do top
struct Node* top;

//inserir valores
void push(ESTADO data) {
    struct Node* temp;
    temp = (struct Node*)malloc(sizeof(struct Node));

    if(!temp){
        printf("a stack esta sobrelotada");
        exit(1);
    }
    temp->data = data;     //introduzir o valor recebido
    temp->next = top;     //direcionar o apontador top para next
    top=temp;             //aponta o top para inicio da stack
}

//verificar se a stack esta vazia
int isEmpty() {
    return top == NULL;
}

//indicar o elemento de topo da stack
ESTADO elementoTopo() {
    if(!isEmpty(top)) {
        return top->data;
    } else {
        exit(EXIT_FAILURE);
    }
}


//remover elementos
void pop() {
    struct Node* temp;
    if(top == NULL) {
        printf("\nA stack esta vazia! \n");
        exit(1);
    } else {
        temp = top;
        top = top ->next;       //o nodo seguinte fica o ser o top
        temp->next= NULL;       //destruir a ligaçao entre o temp e o nodo seguinte
        free(temp);             //liberta memoria do nodo de topo
    }
}