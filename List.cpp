/*********************************************************************************
 * Luke Kim, lusukim
 * 2022 Winter CSE101 PA6
 * List.cpp
 * List ADT
 *********************************************************************************/
#include<iostream>
#include<string>
#include"List.h"
#include<stdexcept>
using namespace std;

List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

List::List(){
    frontDummy = new Node(-1);
    frontDummy->next = backDummy;
    backDummy = new Node(-1);
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L){
    frontDummy = new Node(-1);
    frontDummy->next = backDummy;
    backDummy = new Node(-1);
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    if (L.length() != 0){
        Node* N = L.frontDummy;
        while (N->next != L.backDummy){
            this->insertBefore(N->next->data);
            N = N->next;
        }
    }

}

List::~List(){
    clear();
    delete frontDummy;
    delete backDummy;
    beforeCursor = nullptr;
    afterCursor = nullptr;
    pos_cursor = 0;
}

int List::length() const{
    return (num_elements);
}

ListElement List::front() const{
    if (num_elements == 0){
        throw std::length_error("List: front(): empty Stack");
    }
    return (frontDummy->data);
}

ListElement List::back() const{
    if (num_elements == 0){
        throw std::length_error("List: back(): empty Stack");
    }
    return (backDummy->data);
}

int List::position() const{
    return (pos_cursor);
}

ListElement List::peekNext() const{
    if (pos_cursor == num_elements){
        throw std::length_error("List: peekNext(): position cursor out of bounds");
    }
    return (afterCursor->data);
}

ListElement List::peekPrev() const{
    if (pos_cursor == 0){
        throw std::length_error("List: peekPrev(): position cursor out of bounds");
    }
    return (beforeCursor->data);
}

void List::clear(){
    moveFront();
    while (num_elements != 0){
        eraseAfter();
    }   
}

void List::moveFront(){
    pos_cursor = 0;
    afterCursor = frontDummy->next;
    beforeCursor = frontDummy;
}

void List::moveBack(){
    pos_cursor = num_elements;
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

ListElement List::moveNext(){
    if (pos_cursor >= num_elements){
        throw std::length_error("List: moveNext(): position cursor out of bounds");
    }
    pos_cursor += 1;
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    return (beforeCursor->data);
    
}

ListElement List::movePrev(){
    if (pos_cursor <= 0){
        throw std::length_error("List: movePrev(): position cursor out of bounds");
    }
    pos_cursor -= 1;
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    return (afterCursor->data);
}

void List::insertAfter(ListElement x){
    Node* N = new Node(x);
   if (num_elements==0){
       N->next = backDummy;
       N->prev= frontDummy;
       frontDummy->next = N;
       backDummy->prev = N;
       afterCursor = N;
   }
   else if (pos_cursor == num_elements && afterCursor == backDummy){
       backDummy->prev = N;
       beforeCursor->next = N;
       N->prev = beforeCursor;
       N->next = backDummy; 
       afterCursor = N;
   }
   else{
       N->prev = beforeCursor;
       N->next = afterCursor;
       beforeCursor->next = N;
       afterCursor->prev = N;
       afterCursor = N;
   }
   num_elements+=1;
   return;
}

void List::insertBefore(ListElement x){
    Node* N = new Node(x);
    if (num_elements == 0){
        N->next = backDummy;
        N->prev = frontDummy;
        frontDummy->next = N;
        backDummy->prev = N;
        beforeCursor = N;
    }
    
    else if (pos_cursor == 0 && beforeCursor == frontDummy){
        frontDummy->next = N;
        N->prev = frontDummy;
        N->next = afterCursor;
        afterCursor->prev = N;
        beforeCursor = N;
    }

    else{
        beforeCursor->next = N;
        afterCursor->prev = N;
        N->prev = beforeCursor;
        N->next = afterCursor;
        beforeCursor = N;
    }
    num_elements+=1;
    pos_cursor+=1;
    return;

}

void List::setAfter(ListElement x){
    if (pos_cursor >= num_elements){
        throw std::length_error("List: setAfter(): position cursor out of bounds");
    }
    afterCursor->data = x;
    return;
}

void List::setBefore(ListElement x){
    if (pos_cursor <= 0){
        throw std::length_error("List: setBefore(): position cursor out of bounds");
    }
    beforeCursor->data = x;
    return;
}

void List::eraseAfter(){
    if (pos_cursor >= num_elements){
        throw std::length_error("List: eraseAfter(): position cursor is out of bounds");
    }

    Node* temp = afterCursor;
    afterCursor = afterCursor->next;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    num_elements-=1;
    delete temp;
    return;
}

void List::eraseBefore(){
    if (pos_cursor <= 0){
        throw std::length_error("List: eraseBefore(): position cursor is out of bounds");
    }

    Node* temp = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    num_elements-=1;
    pos_cursor-=1;
    delete temp;
    return;
}


std::string List::to_string() const{
    Node* N = nullptr;
    std::string s = "";

    for (N = frontDummy; N->next != backDummy; N=N->next){
        s += std::to_string(N->next->data)+" ";
    }
    return s;
}

int List::findNext(ListElement x){
    while (pos_cursor != num_elements){
        if (afterCursor->data == x){
            moveNext();
            return pos_cursor;
        }
        moveNext();
    }
    return -1;
    
}

int List::findPrev(ListElement x){
    while (pos_cursor != 0){
        if (beforeCursor->data == x){
            movePrev();
            return pos_cursor;
        }
        movePrev();
    }
    return -1;
}

void List::cleanup(){
    Node* N = nullptr;
    Node* M = nullptr;
    Node* temp = nullptr;
    int NCursor = 1;
    int MCursor = 0;
    for (N = frontDummy->next; N->next != backDummy; N=N->next){
        MCursor = NCursor;
        for (M = N->next; M->next != backDummy; M=M->next){
            MCursor+=1;
            if (N->data == M->data && MCursor <= pos_cursor){
                pos_cursor -=1;
                num_elements -=1;
                if (M == beforeCursor){
                    beforeCursor = M->prev;    
                }
                M->prev->next = M->next;
                M->next->prev = M->prev;
                temp = M;
                M = M->prev;
                MCursor -=1;
                delete temp;
            }
            else if (N->data == M->data && MCursor > pos_cursor){
                num_elements -= 1;
                if (M == afterCursor){
                    afterCursor = M->next;
                }
                M->prev->next = M->next;
                M->next->prev = M->prev;
                temp = M;
                M = M->prev;
                MCursor -=1;
                delete temp; 
            }
        }
        if (pos_cursor == num_elements && M->data == N->data && N->next != backDummy){
                num_elements -= 1;
                pos_cursor-=1;
                backDummy->prev = M->prev;
                if (M == beforeCursor){
                    beforeCursor = M->prev;    
                }
                M->prev->next = backDummy;
                temp = M;
                M = M->prev;
                delete temp;
            }
        else if (M->data == N->data && N->next != backDummy){
            num_elements-=1;
            M->prev->next = M->next;
            M->next->prev = M->prev;
            temp = M;
            M= M->prev;
            delete temp;
        }
        NCursor+=1;

    }

}

List List::concat(const List& L) const{
    Node* N = nullptr;
    List nL;
    for (N = frontDummy; N->next != backDummy; N = N->next){
        nL.insertBefore(N->next->data);
    }
    for (N = L.frontDummy; N->next != L.backDummy; N = N->next){
        nL.insertBefore(N->next->data);
    }
    nL.pos_cursor = 0;
    return nL;
}

bool List::equals(const List& R) const{
    if (num_elements != R.length()){
        return false;
    }
    Node* N = frontDummy;
    Node* M = R.frontDummy;
    while (N != backDummy && M != R.backDummy){
        if (N->next->data != M->next->data){
            return false;
        }
        N = N->next;
        M = M->next;
    }
    return true;
}

std::ostream& operator<< ( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}

bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

List& List::operator=( const List& L){
    if ( this != &L ){
        List temp = L;
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
    }

    return *this;
}