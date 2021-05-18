#pragma once
#include<gmp.h>
#include<gmpxx.h>
#include<vector>
using namespace std;

//Miller-Rabin prime test
bool isPrime(mpz_class n,int repos);
void isPrimeTest();

//pho factorize
mpz_class findFactor(mpz_class n, mpz_class a);
vector<mpz_class> phoFactorize(mpz_class n);
void phoFactorizeTest();
