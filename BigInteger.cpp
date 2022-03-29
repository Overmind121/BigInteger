/*********************************************************************************
 * Luke Kim, lusukim
 * 2022 Winter CSE101 PA6
 * BigInteger.cpp
 * BigInteger ADT
 *********************************************************************************/
#include "BigInteger.h"
#include "List.h"
#include <math.h>
#include <cstdlib>

using namespace std;


void negateList(List& L);
void scalarMultList(List& L, ListElement m);
void shiftList(List& L, int p);
void sumList(List& S, List A, List B, int sgn);
int normalizeList(List &L);

int power = 9;
long base = pow(10, power);


BigInteger::BigInteger(){
    signum = 0;
    digits = List();
}

BigInteger::BigInteger(std::string s){
    if (s.length() == 0){
        throw std::length_error("string is empty in constructor");
    }

    string elementVal = "";
    int aNums = s.length();
    int end = 0;
    if (s[0] == '-'){
        signum = -1;
        aNums-=1;
        end += 1;
    }
    else if (s[0] == '+'){
        signum = 1;
        aNums -=1;
        end +=1;
    }
    else if (s[0] != '-' && s[0] != '+'){
        signum = 1;
    }
  
    for (int i = s.length()-1; i >= end; i--){
        elementVal = s[i] + elementVal;

        if ((int)elementVal.length() == power){
            long element = stol(elementVal);

            digits.insertAfter(element);
            elementVal = "";
        }
        
    }
    if (elementVal.length() > 0){
        long element = stol(elementVal);
        digits.insertAfter(element);
    }
    for (digits.moveFront(); digits.peekNext() == 0;){
        digits.eraseAfter();
    }
    
}

BigInteger::BigInteger(const BigInteger& N){
    this->signum = N.signum;
    this->digits = N.digits;
}

int BigInteger::sign() const{
    return signum;
}

int BigInteger::compare(const BigInteger& N) const{
  
    if (signum < N.signum){
        return -1;
    }

    else if (signum > N.signum){
        return 1;
    }
    
    else{
        if (signum == -1){
            if (digits.length() < N.digits.length()){
                return 1;
            }
            if (digits.length() > N.digits.length()){
                return -1;
            }
        }
        if (signum == 1){
            if (digits.length() > N.digits.length()){
                return 1;
            }
            if (digits.length() < N.digits.length()){
                return -1;
            }
        }
        if ((digits == N.digits) || (digits.length() == 0 && N.digits.length() == 0)){
        return 0;
        }
        List A  = digits;
        List B = N.digits;

        A.moveFront();
        B.moveFront();
        while (A.position() != A.length()){
            if (A.peekNext() > B.peekNext()){
                return 1;
            }
            else if (A.peekNext() < B.peekNext()){
                return -1;
            }
            else{
                A.moveNext();
                B.moveNext();
            }
        }
    }
    return 0;
}

void BigInteger::makeZero(){
    signum = 0;
    digits.clear();
}

void BigInteger::negate(){
    if (signum == 1){
        signum = -1;
    }
    else if (signum == -1){
        signum = (1);
    }
    else {
        return;
    }
}

void sumList(List& S, List A, List B, int sgn){
    S.clear();
    scalarMultList(B, sgn); 
    A.moveBack();
    B.moveBack();
    while (A.position() != 0 && B.position() != 0){
        int sum = A.peekPrev() + B.peekPrev();
        S.insertAfter(sum);
        A.movePrev();
        B.movePrev();
    }
    while (A.position() != 0){
        S.insertAfter(A.peekPrev());
        A.movePrev();
    }
    while (B.position() != 0){
        S.insertAfter(B.peekPrev());
        B.movePrev();
    }
}

BigInteger BigInteger::mult(const BigInteger& N) const{

    List Mdigits = digits;
    List Ndigits = N.digits;
    List prod = List();

    BigInteger A = BigInteger();

    int shifts = 0;
    if (signum == N.signum){
        A.signum = 1;
    }
    else if (signum != N.signum){
        A.signum = -1;
    }
    if (signum == 0 || N.signum == 0){
        A.signum = 0;
        return A;
    }
    for (Ndigits.moveBack(); Ndigits.position() > 0; Ndigits.movePrev()){
        scalarMultList(Mdigits, Ndigits.peekPrev());
        sumList(prod, prod, Mdigits, 1);
        normalizeList(prod);
        shifts = N.digits.length() - Ndigits.position();
        prod.moveBack();
        shiftList(prod, shifts);
        sumList(A.digits, A.digits, prod, 1);
        normalizeList(A.digits);
        prod.clear();
        Mdigits = digits;

    }
    
    return A;
}

void shiftList(List& L, int p){
    for (int i = 0; i < p; i++){
        L.insertAfter(0);
    }
}

BigInteger BigInteger::sub(const BigInteger& N) const{
    List Ndigits = N.digits;
    List Mdigits = digits;

    BigInteger A;
    if (signum == 1 && N.signum == -1){
        // M - (-N) = M + N
        sumList(A.digits, Mdigits, Ndigits, 1);
    }
    if (signum == -1 && N.signum == 1){
        // (-M) - N = -M + -N
        scalarMultList(Mdigits, -1);
        sumList(A.digits, Mdigits, Ndigits, -1);
    }
    if (signum == 1 && N.signum == 1){
        // M -N
        //cout << "positive" << endl;
        sumList(A.digits, Mdigits, Ndigits, -1);
    }
    if (signum == -1 && N.signum == -1){
        // (-M) - (-N) = (-M) + N
        scalarMultList(Mdigits, -1);
        sumList(A.digits, Mdigits, Ndigits, 1);
    }

    int signA = normalizeList(A.digits);
    A.signum = signA;
    return A;
}
BigInteger BigInteger::add(const BigInteger& N) const{

    List Ndigits = N.digits;
    List Mdigits = digits;
    

    BigInteger A;
    if (N.signum == -1 && signum ==1){
        sumList(A.digits, Mdigits, Ndigits, -1);
    }
    else if (N.signum == 1 && signum == -1){
        sumList(A.digits, Ndigits, Mdigits, -1);
    }
    else if (N.signum == 1 && signum == 1){
        sumList(A.digits, Mdigits, Ndigits, 1);
    }
    else if (N.signum == -1 && signum == -1){
        scalarMultList(Mdigits, -1);
        sumList(A.digits, Mdigits, Ndigits, -1);
    }
    else if (N.signum == 0){
        A.digits = Ndigits;
        A.signum = N.signum;
        return A;
    }
    else if(signum == 0){
        A.digits = digits;
        A.signum = signum;
        return A;
    }

    
    int signA = normalizeList(A.digits);
    A.signum = signA;
    return A;
}

void negateList(List& L){
    for (L.moveFront(); L.position() < L.length(); L.moveNext()){
        L.setAfter(-(L.peekNext()));
    }
}

void scalarMultList(List& L, ListElement m){
    for (L.moveFront(); L.position() < L.length(); L.moveNext()){
        L.setAfter(m*(L.peekNext()));
    }
}



int normalizeList(List& L){
    long carry = 0;
    long multiple = 0;
    L.moveBack();
    while (L.position() > 0 || carry != 0){
       
        if (L.position() == 0){
            L.insertAfter(carry);
            carry = 0;
            break;
        }
        L.setBefore(L.peekPrev() + carry);
        if (L.peekPrev() >= base){
            if ((L.peekPrev() % base) != 0){
                multiple = L.peekPrev() - (L.peekPrev() % base);
                L.setBefore(L.peekPrev() - multiple);
                carry = multiple/base;
            }
            else{
                carry = L.peekPrev()/base;
                L.setBefore(0);
            }
        }
        else if (L.peekPrev() < 0 && L.position() != 1){
            if ((L.peekPrev() % base) != 0){
                multiple = L.peekPrev() - (base + (L.peekPrev() % base));
                L.setBefore(L.peekPrev()-multiple);
                carry = (multiple/base);
            }
            else{
                carry = L.peekPrev()/base;
                L.setBefore(0);
            }
        }
        else{
            carry = 0;
        }
        L.movePrev();

    }
    L.moveFront();
    while (L.peekNext() == 0 && L.length() > 2){
        L.eraseAfter();
    }
    L.moveFront();
    if (L.peekNext() > 0){
        return 1;
    }
    else if (L.peekNext() < 0){
        for (L.moveFront(); L.position() < L.length(); L.moveNext()){
            L.setAfter(-L.peekNext());
        }
        L.moveBack();
        while (L.position() > 0){
            L.setBefore(L.peekPrev() + carry);
            if (L.peekPrev() < 0){
                carry = -1;
                L.setBefore(L.peekPrev() + base);
            }
            else{
                carry = 0;
            }
            L.movePrev();

        }
        return -1;
    }
    else {
        return 0;
    }

    
}

std::string BigInteger::to_string(){
    std::string biginteger = "";

    if (signum == 0){
        biginteger = "0";
        return biginteger;
    }

    if (signum == -1){
        biginteger+="-";
    }
    for(digits.moveFront(); digits.position() < digits.length(); digits.moveNext()){
        if (digits.position() == 0 && digits.peekNext() != 0){
            biginteger += std::to_string(digits.peekNext());
        }
        else if (digits.peekNext() < 0){
            biginteger += std::to_string(-digits.peekNext());
        }
        else{
            std::string digits_str = std::to_string(digits.peekNext());
            int num_zeros = power - digits_str.length();
            for (int j = 0; j < num_zeros; j++){
                biginteger+= "0";
            }
            biginteger+=digits_str;
        }
    }
    return biginteger;
} 

std::ostream& operator<< ( std::ostream& stream, BigInteger N ){
    return stream << N.to_string();
}

bool operator==( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == 0){
        return true;
    }
    return false;
}
bool operator<( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == -1){
        return true;
    }
    return false;
}

bool operator<=( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == -1 || A.compare(B) == 0){
        return true;
    }
    return false;
}

bool operator>( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == 1){
        return true;
    }
    return false;
}
bool operator>=( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == 1 || A.compare(B) == 0){
        return true;
    }
    return false;
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    BigInteger C = A.add(B);
    return C;
}
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    BigInteger C = A.add(B);
    std::swap(A.signum, C.signum);
    A.digits = C.digits;
    return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    BigInteger C = A.sub(B);
    return C;
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    BigInteger C = A.sub(B);
    std::swap(A.signum, C.signum);
    A.digits = C.digits;
    return A;
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    BigInteger C;
    C = A.mult(B);
    return C;
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    BigInteger C = A.mult(B);
    std::swap(A.signum, C.signum);
    A.digits = C.digits;
    return A;
}