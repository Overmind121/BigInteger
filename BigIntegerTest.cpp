/*********************************************************************************
 * Luke Kim, lusukim
 * 2022 Winter CSE101 PA6
 * BigIntegerTest.cpp
 * BigIntegerTest ADT
 *********************************************************************************/
#include "BigInteger.h"

using namespace std;
int main(){

    BigInteger A = BigInteger("111122223333");
    BigInteger B = BigInteger("111122223333");
    cout << A << endl;
    cout << B << endl;
    cout << A+B << endl;
    cout << A-B << endl;
    B.makeZero();
    cout << B << endl;
    BigInteger C = A*B;
    cout << C << endl;
    
    if (!(A == B)){
        cout << "A and B are not equal!" << endl;
    }
    B= BigInteger("111122223333");
    BigInteger F = A+B;
    cout << F << endl;
    cout << F -B << endl;
    return(0);
}