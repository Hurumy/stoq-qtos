
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <complex>
#include <bitset>
#include <random>

//#define DEBUG
#define BIT_SIZE 8

bool packet2Bit(std::complex<double> a, std::complex<double> b, std::string gates) {
	std::complex<double>	alpha = a; // p0
	std::complex<double>	beta = b; // p1
	std::complex<double>	temp_a;
	std::complex<double>	temp_b;
	char	gate;

	// apply gates to the bit
	for (int i=0; !gates.empty() && gates[i] != '\0'; i++) {
		gate = gates[i];
		temp_a = alpha;
		temp_b = beta;

		// Hadamard gate
		if (gate == 'H') {
			alpha = (temp_a + temp_b) * 0.70710678;
			beta = (temp_a - temp_b) * 0.70710678;
		}
		
		// Pauli-X gate 
		else if (gate == 'X') {
			alpha = beta;
			beta = temp_a;
		}

		// Pauli-Y gate
		else if (gate == 'Y') {
			alpha.real(temp_b.imag());
			alpha.imag(-1.0*(temp_b.real()));
			beta.real(-1.0*(temp_a.imag()));
			beta.imag(temp_a.real());
		}

		// Pauli-Z gate
		else if (gate == 'Z') {
			beta.real(-1.0*temp_b.real());
			beta.imag(-1.0*temp_b.imag());
		}
	}

#ifdef DEBUG
	std::cerr << "a: " << alpha << "  b: " << beta << std::endl;
#endif

	// measure bit
	std::random_device	rd;
	uint32_t num = rd();

#ifdef DEBUG
	std::cerr << "percent/0: " << (double)std::pow((double)std::abs(alpha), (int)2) << std::endl;
#endif

	double	rand = (double)num/(double)UINT32_MAX;
	if (rand < (double)std::pow((double)std::abs(alpha), (int)2))
		return false;
	return true;
}

int	parsePacket(std::complex<double> &a, std::complex<double> &b) {
	std::vector<std::string> packet;
	std::string str;
	std::string alpha;
	std::string beta;

	// read from stdin
	while (1) {
		std::cin >> str;
		
		if (str == "QBIT") {
			std::cin >> alpha; // a:(0,0)
			std::cin >> beta; // b:(0,0)
			std::cin >> str; // END

			// convert string to std::complex
			alpha = alpha.substr(2); // (0,0)
			beta = beta.substr(2); // (0,0)
			
			std::stringstream ss;
			ss << alpha;
			ss >> a;
			ss << beta;
			ss >> b;
			return 0;
		}
	}
	return -1;
}

int	decodeQbit(std::string gates) {
	std::complex<double> a;
	std::complex<double> b;
	std::bitset<BIT_SIZE> bs;
	std::string str;

	while (1) {
		for (size_t i=0; i<BIT_SIZE; i++) {
			parsePacket(a, b);
			bs[i] = packet2Bit(a, b, gates);
		}
#ifdef DEBUG
		std::cerr << "char: " << bs << std::endl;
#endif
		std::cout << (char)bs.to_ulong();
	}
}

int	main(int argc, char **argv) {
	if (argc < 2 || argc > 2 || argv[1] == "help") {
		std::cout << "./qtos gates" << std::endl;
	} else if (argc == 2) {
		decodeQbit(argv[1]);
	}

	return 0;
}

