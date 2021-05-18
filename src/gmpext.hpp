#pragma once
#include<gmp.h>
#include<gmpxx.h>
#include<iostream>
using namespace std;

inline mpz_class pow(mpz_class a, mpz_class b, mpz_class n)
{
	mpz_class r;
	mpz_powm(r.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t(), n.get_mpz_t());
	return r;
}