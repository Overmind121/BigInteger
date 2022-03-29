/*********************************************************************************
 * Luke Kim, lusukim
 * 2022 Winter CSE101 PA6
 * ListTest.cpp
 * List Test for List ADT
 *********************************************************************************/
#include "List.h"

int main(){
    List A;
    List B;
    A.moveBack();
    A.insertAfter(5);
    A.insertAfter(6);
    A.insertAfter(7);
    currentPos = A.position();
    std::cout << "Cursor Pos: "<<currentPos<< std::endl;
    A.clear();
    A.moveFront();
    std::cout << "Front Element: "<< A.peekNext() << std::endl;
    A.moveNext();
    std::cout << "Cursor Pos: "<< A.position() << std::endl;
    std::cout << A.peekNext() << std::endl;
    A.insertAfter(8);
    std::cout << "Cursor Pos: "<< A.position() << std::endl;
    std::cout << A.peekNext() << std::endl;
    A.moveNext();
    std::cout << "Cursor Pos: "<< A.position() << std::endl;
    std::cout << A.peekNext() << std::endl;
    A.moveBack();
    std::cout << "Back Element: "<< A.peekPrev() << std::endl;
    std::cout << "Back Element: "<< A.back() << std::endl;
    std::cout << "Cursor Pos: "<< A.position() << std::endl;
    std::cout << "Length: "<< A.length() << std::endl;

    A.insertAfter(10);
    std::cout << "Cursor Pos: "<< A.position() << std::endl;
    std::cout << "Length: "<< A.length() << std::endl;
    std::cout << "next Element: "<< A.peekNext() << std::endl;
    std::cout << "Back Element: "<< A.back() << std::endl;

    A.moveBack();
    std::cout << "Cursor Pos: "<< A.position() << std::endl;
    std::cout << "Length: "<< A.length() << std::endl;
    std::cout << "next Element: "<< A.peekNext() << std::endl;
    std::cout << "Back Element: "<< A.back() << std::endl;
    std::cout << "Cursor Pos: "<< A.position() << std::endl;
    A.insertAfter(5);
    std::cout << "Next node value: " << A.peekNext() << std::endl;
    std::cout << "Cursor Pos: "<< A.position() << std::endl;
    A.insertAfter(6);
    std::cout << "Next node value: " << A.peekNext() << std::endl;
    std::cout << "Cursor Pos: "<< A.position() << std::endl;
    A.insertAfter(7);
    std::cout << "Next node value: " << A.peekNext() << std::endl;
    std::cout << "Cursor Pos: "<< A.position() << std::endl;
    A.insertAfter(7);

    B.insertBefore(1);
    B.insertBefore(2);
    B.insertBefore(2);
    B.insertBefore(1);
    B.insertBefore(2);
    B.insertBefore(3);
    B.insertBefore(1);
    std::cout << "List B: " << B << std::endl;
    std::cout << "Cursor val "<< B.position() << std::endl;
    std::cout << "Find prev value " << B.findPrev(3) << std::endl;
    B.movePrev();
    std::cout << "Cursor val "<< B.position() << std::endl;
    std::cout << "prev val " << B.peekPrev() << std::endl;
    std::cout << "After val " << B.peekNext() << std::endl;
    B.cleanup();

    return 0;
}