#ifndef RSA_HPP_INCLUDED
#define RSA_HPP_INCLUDED
#include <string>

class RSA
{
unsigned long long int	 primeOne,primeTwo,minVal,maxVal,publicKey,privateKey;
unsigned long long int	 modul,totient;
unsigned long long int	 findRandomPrime(int ,int );
unsigned long long int	 getPublicKey();
unsigned long long int	 getPrivateKey();
void calculatePrimes();
public:
    RSA(int,int);
    void writer();
    void init();
    unsigned long long int	* encrypt(std::string);
    std::string decrypt(unsigned long long int	*,size_t);

};


#endif // RSA_HPP_INCLUDED

