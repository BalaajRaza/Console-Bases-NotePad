#ifndef WORDSTACK_H
#define WORDSTACK_H

#include <iostream>
using namespace std;

class Letter{
public:
    char l;
    Letter *next;

    Letter(char c) : l(c), next(NULL) {}
};

class WordStack{
public:
    Letter *top;

    WordStack() : top(NULL){}

    void push(char l){
        Letter *newLetter = new Letter(l);
        newLetter->next = top;
        top = newLetter;
    }

    void pop(){
        if (top)
        {
            Letter *temp = top;
            top = top->next;
            delete temp;
        }
    }

    void clear(){
        while (top)
        {
            pop();
        }
        top == NULL;
    }

    bool isEmpty(){
        return top == NULL;
    }
    
};
#endif