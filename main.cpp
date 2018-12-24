#include <iostream>
#include "rsa.hpp"

using namespace std;


int main()
{
    RSA myRSA(2,3000);
    myRSA.init();
    myRSA.writer();
    return 0;
}
