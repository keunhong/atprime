#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>

typedef unsigned long long int ULLint;

int main(int argc, char **argv){
	ULLint limit = strtoul(argv[1],0,0) + 1;

	// initialize is_prime array with falses
	bool *is_prime = new bool[limit];
	for(ULLint i = 0; i < limit; i++) is_prime[0] = false;

	// Use Sieve of Atkins
	ULLint n = 0;
	for(ULLint x = 1; x < sqrt(limit); x++){
		for(ULLint y = 1; y < sqrt(limit); y++){
			n = 4 * x * x + y * y;
			if((n <= limit) && (n % 12 == 1 || n % 12 == 5)){
				is_prime[n] = !(is_prime[n]);
			}
			
			n = 3 * x * x + y * y;
			if((n <= limit) && (n % 12 == 7)){
				is_prime[n] = !(is_prime[n]);
			}
			
			n = 3 * x * x - y * y;
			if((x > y) && (n <= limit) && (n % 12 == 11)){
				is_prime[n] = !(is_prime[n]);
			}
		}
	}
	
	for(ULLint i = 5; i < sqrt(limit); i++){
		if(is_prime[i]){
			for(ULLint j = i; j * i * i < limit; j++){
				is_prime[j * i * i] = false;
			}
		}
	}
	
	// Print all primes
	
	ofstream output;
	output.open("output.txt");
	
	if(argv[2] == NULL || argv[2][0] != 's'){
		std::cout << "2 3 ";
		for(ULLint i = 5; i < limit; i++){
			if(is_prime[i]) output << i << "i";
			//if(is_prime[i]) std::cout << i << " ";
		}
		std::cout << std::endl;
	}

	
	


	// Terminate
	return 0;

}

