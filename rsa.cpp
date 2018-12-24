#include "rsa.hpp"
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>


unsigned long long int	 RSA::findRandomPrime( int lowRange, int highRange)
{
    bool primeFlag = true;

    while(1)
    {
        int random_variable = ((std::rand())%(highRange - lowRange + 1))+lowRange;
        int root = sqrt(random_variable) ;

        for(int i=2; i<=root; i++)
        {
            if(random_variable%i == 0)
            {
               primeFlag = true;
            }

        }
        if(primeFlag)
        {
            primeFlag = false;
            continue;
        }
        return random_variable;
    }

}
void RSA::calculatePrimes()
{
    primeOne = findRandomPrime(minVal,maxVal);
    while((primeTwo = findRandomPrime(minVal,maxVal)) == primeOne);

}

void RSA::init()
{
    calculatePrimes();
    modul = primeOne * primeTwo;
    totient = ( primeOne -1 ) * (primeTwo -1);
    publicKey = getPublicKey();
    privateKey = getPrivateKey();
}

RSA::RSA( int minVal_, int maxVal_):minVal(minVal_),maxVal(maxVal_)
{
    std::srand(std::time(0));      // use current time as seed for random generator
}

 unsigned long long int	 RSA::getPublicKey()
{
    int pKey;
    std::cout<<"\nGenerating Public Key ..."<<std::endl;
    while(1)
    {
        pKey = findRandomPrime(2,totient);
        if ((pKey%totient) != 0 && (totient%pKey) != 0)
        {

            break;
        }

    }


    return pKey;
}
 unsigned long long int	 RSA::getPrivateKey()
{
    int i = 0;
    privateKey = 2;
    std::cout<<"\nGenerating Private Key ..."<<std::endl;
    while((i = ((publicKey*privateKey)%totient)) != 1 || publicKey == privateKey)
    {
        privateKey++;
    }

    return privateKey;
}

void RSA::writer()
{
    std::cout <<primeOne<<" "<<primeTwo<<" "<<totient<<" "<<modul<<" "<<publicKey<<" "<<privateKey<<" "<<std::endl;
    std::string data("hello");
    std::cout <<decrypt(encrypt(data),data.size())<<std::endl;
}

unsigned long long int	* RSA::encrypt(std::string txtE)
{
    unsigned long long int	 *buff = new unsigned long long int	[txtE.size()];
    unsigned long long int	 result = 1;
    unsigned long long int	 current = 0;
    for (unsigned short i = 0 ; i < txtE.size() ; i++)
    {
        current = (unsigned long long int)txtE.at(i) - 97;
        for(long long j =0 ; j < publicKey ; j++)
        {
            result = result * current;
            result = result % modul;
        }
         *(buff+i) = result;
         result =1;
    }

     return buff;
}

std::string RSA::decrypt(unsigned long long int	* txtD, size_t buffSize)
{
    std::string buff(buffSize,' ');
   unsigned long long int	 result = 1;
   unsigned long long int	 current = 0;

    for (unsigned short i = 0 ; i < buffSize ; i++)
    {
        current = *(txtD+i);
        std::cout<<current<<std::endl;

        for(long long j =0 ; j < privateKey ; j++)
        {
            result = result * current;
            result = result % modul;
        }
        std::cout<<result<<std::endl;
        buff.at(i) = result + 97;
        result = 1;
    }
    delete txtD;
    return buff;
}
