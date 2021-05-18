#include<algorithm>
#include<chrono>
#include<ctime>
#include<iostream>
#include"crypto.h"
using namespace std;
using namespace chrono;

mpz_class findFactor(mpz_class n, mpz_class a)
{
	auto f = [=](mpz_class x) {mpz_class res = (x * x + a) % n; return res; };
	if (n % 2 == 0)
		return 2;
	gmp_randclass r1(gmp_randinit_default);
	r1.seed(unsigned long int(time(NULL)));
	mpz_class x1, x2;
	x2 = x1 = r1.get_z_range(n);
	while (true)
	{
		x1 = f(x1);
		x2 = f(f(x2));
		mpz_class p = gcd(abs(x1 - x2), n);
		if (p > 1)
			return p;
		if (x1 == x2)
			return n;
	}
}

vector<mpz_class> phoFactorize(mpz_class n)
{
	vector<mpz_class> factor;
	gmp_randclass r1(gmp_randinit_default);
	r1.seed(unsigned long int(time(NULL)));
	while (n!=1){
		if (mpz_probab_prime_p(n.get_mpz_t(), 30)) {
			factor.push_back(n);
			break;
		}
		else {
			mpz_class c = findFactor(n, r1.get_z_range(n));
			if (mpz_probab_prime_p(c.get_mpz_t(), 30)) {
				factor.push_back(c);
				n /= c;
			}
		}
	}
	sort(factor.begin(), factor.end());
	return factor;
}

void phoFactorizeTest()
{
	mpz_class n("0x2fbf76ea9f0b3");
	vector<mpz_class> factor;

	auto startT1 = steady_clock::now();
	factor = phoFactorize(n);
	auto endT1 = steady_clock::now();
	duration<double, std::micro> elapsed1 = endT1 - startT1;
	cout << "pho factorize:" << (double)elapsed1.count() / 1000 << "ms" << endl;

	for (mpz_class i : factor)
		cout << i.get_str() << endl;
}