#include<chrono>
#include<ctime>
#include<iostream>
#include<vector>
#include"crypto.h"
#include"gmpext.hpp"

using namespace std;
using namespace chrono;

vector<int> small_prime = 
{ 2, 3, 5, 7, 11, 13, 17, 19,23, 29,31, 37, 41, 43, 47, 53, 59, 61, 67, 
71,73, 79,83, 89, 97, 101, 103, 107, 109, 113,127, 131, 137, 139,149, 
151, 157, 163, 167, 173,179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
233, 239, 241, 251, 257, 263, 269, 271, 277, 281,283, 293 ,
307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 
401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599,
601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 
701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 
809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887,
907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997
};

bool isPrime(mpz_class n, int reps)
{
	if (n == 2)
		return true;
	for (auto i : small_prime)
		if (n % i == 0)
			return false;
	for (int i = 0; i < reps; i++) {
		unsigned int t = 0;
		mpz_class u = n - 1;
		while (u % 2 == 0) {
			t += 1;
			u /= 2;
		}
		mpz_class a;
		gmp_randclass r1(gmp_randinit_default);
		r1.seed(unsigned long int(time(NULL)));
		while (true) {
			a = r1.get_z_range(n);
			if (a == 0 || a == 1)
				continue;
			break;
		}
		mpz_class r = pow(a, u, n);
		if (r != 1) {
			while (t > 1 && r != n - 1) {
				r = pow(r, 2, n);
				t -= 1;
			}
			if (r != n - 1)
				return false;
		}
	}
	return true;
}

void isPrimeTest()
{
	mpz_class a;
	gmp_randclass r1(gmp_randinit_default);
	r1.seed(unsigned long int(time(NULL)));

	//验证算法的正确性
	/*for (int i = 0; i < 5000; i++){
		a = r1.get_z_bits(2048);
		bool lhs = isPrime(a, 20);
		bool rhs = mpz_probab_prime_p(a.get_mpz_t(), 20);
		if (lhs != rhs)
			cout << "wrong!" << endl;
	}*/
	
	//测试代码的效率，并与GMP库进行对比
	vector<mpz_class> v;
	for (int i = 0; i < 1000; i++)
		v.push_back(r1.get_z_bits(2048));

	auto startT1 = steady_clock::now();
	for (auto i:v) 
		isPrime(i, 30);
	auto endT1 = steady_clock::now();
	duration<double, std::micro> elapsed1 = endT1 - startT1;
	cout << "myself:" << (double)elapsed1.count() / 1000 << "ms" << endl;

	auto startT2 = steady_clock::now();
	for (auto i : v) 
		mpz_probab_prime_p(i.get_mpz_t(), 30);
	auto endT2 = steady_clock::now();
	duration<double, std::micro> elapsed2 = endT2 - startT2;
	cout << "GMP:" << (double)elapsed2.count() / 1000 << "ms" << endl;
}