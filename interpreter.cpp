#include <cstdio>
#include <iostream>
#include <fstream>
#include <stack>

#include "interpreter.h"
#include "mainwindow.h"

//Global var
//Brainfuck array and its pointers
char data[30000];
char *d;
const char *p;

/**
 * Constructor
 */
Interpreter::Interpreter() {}

/**
 * Set the data to be interpreted
 * @param prog the information in the console
 */
void Interpreter::setData(const char prog[]){
    d=data;
    p=prog;

    for(int i = 0; i<5 ; i++){
        cout << p[i];
    }
}

/**
 * Increment the pointer
 */
void Interpreter::pointerInc(){
    d++;
}

/**
 * Decrement the pointer
 */
void Interpreter::pointerDec(){
    d--;
}

/**
 * Increment the value at the cell
 */
void Interpreter::bitInc(){
    (*d)++;
}

/**
 * Decrement the value at the cell
 */
void Interpreter::bitDec(){
    (*d)--;
}

/**
 * Now defunct. Ignore.
 */
void Interpreter::output(){
 // MainWindow window;
  //window.output(*d);
}
void Interpreter::input(){
   // cin>>*d;
}

/**
 * If it is a while open bracket
 */
void Interpreter::bracketOpen(){
    int bal = 1;
    if(*d == '\0'){
        do{
            p++;
            if(*p == '[')
                bal++;
            else if(*p == ']')
                bal--;
        }while(bal !=0);
    }
}

/**
 * If is is a while close bracket
 */
void Interpreter::bracketClose(){
    int bal = 0;
        do{
            if(*p == '[')
                bal++;
            else if(*p == ']')
                bal--;
            p--;
        }while(bal !=0);
}

/**
 * If the current value at the pointer is one of these cases, do something
 */
void Interpreter::evaluate(){
    while(*p){
        switch(*p){
        case '>':
          pointerInc();
          break;
        case '<':
          pointerDec();
          break;
        case '+':
          bitInc();
          break;
        case '-':
          bitDec();
          break;
        case '.':
          output();
          break;
        case ',':
          input();
          break;
        case '[':
          bracketOpen();
          break;
        case ']':
          bracketClose();
          break;
          }
         p++;
        }
    }
