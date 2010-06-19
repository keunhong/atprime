#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

typedef unsigned long long int ULLint;
typedef	char byte;

int main(int argc, char **argv){
	ULLint limit = strtoul(argv[1],0,0) + 1;

	// initialize is_prime array with falses
	byte *is_prime = new byte[limit / 8 + 1];
	byte masks[] =  {
				1,  // 0b00000001 
				2,  // 0b00000010
				4,  // 0b00000100
				8,  // 0b00001000
				16, // 0b00010000
				32, // 0b00100000
				64, // 0b01000000
				128 // 0b10000000
			};
	byte masksInv[] = {
				254, // 0b11111110
				253, // 0b11111101
				251, // 0b11111011
				247, // 0b11110111
				239, // 0b11101111
				223, // 0b11011111
				191, // 0b10111111
				127  // 0b01111111
			};
	
	for(ULLint i = 0; i < limit/8; i++) is_prime[i] = 0;

	// Use Sieve of Atkins
	ULLint n = 0;
	for(ULLint x = 1; x < sqrt(limit); x++){
		for(ULLint y = 1; y < sqrt(limit); y++){
			n = 4 * x * x + y * y;
			if((n <= limit) && (n % 12 == 1 || n % 12 == 5)){
				is_prime[n / 8] ^= masks[n % 8];
			}
			
			n = 3 * x * x + y * y;
			if((n <= limit) && (n % 12 == 7)){
				is_prime[n / 8] ^= masks[n % 8];
			}
			
			n = 3 * x * x - y * y;
			if((x > y) && (n <= limit) && (n % 12 == 11)){
				is_prime[n / 8] ^= masks[n % 8];
			}
		}
	}
	
	for(ULLint i = 5; i < sqrt(limit); i++){
		if(is_prime[i]){
			for(ULLint j = i; j * i * i < limit; j++){
				is_prime[(j * i * i) / 8] = is_prime[(j * i * i) / 8] & masksInv[(j * i * i) % 8];
			}
		}
	}
	
	// Print all primes

	if(argv[2] == NULL || argv[2][0] != 's'){
		std::cout << "2 3 ";
		for(ULLint i = 5; i < limit; i++){
			if((is_prime[i/8] | masks[i % 8]) == is_prime[i/8]) std::cout << i << " ";
			//std::cout << (unsigned int)(is_prime[i / 8] & masks[i % 8]);
		}
		std::cout << std::endl;
	}

	
	


	// Terminate
	return 0;

}

