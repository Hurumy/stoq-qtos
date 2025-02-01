
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <complex>
#include <bitset>

#define DEBUG

std::string bit2Packet(bool bit, std::string gates) {
	std::complex<double>	alpha; // p0
	std::complex<double>	beta; // p1
	std::complex<double>	temp_a;
	std::complex<double>	temp_b;
	char	gate;

	// initialize the qbit
	alpha.imag(0.0);
	beta.imag(0.0);
	if (bit) {
		alpha.real(0.0);
		beta.real(1.0);
	} else {
		alpha.real(1.0);
		beta.real(0.0);
	}

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

	// return result
	std::stringstream ss;

	ss << "QBIT a:";
	ss << alpha;
	ss << " b:";
	ss << beta;
	ss << " END";
	std::string res = ss.str();
	return res;
}

int	string2Packet(std::string str, std::string gates) {
	std::string zero = bit2Packet(0, gates);
	std::string one = bit2Packet(1, gates);

	// each char
	for (size_t i=0; i<str.size(); i++) {
		std::bitset<8> bits(str[i]);

#ifdef DEBUG
	std::cout << "\tDEBUG BITS: "<< bits << std::endl;
#endif

		// each bit
		for (size_t j=0; j<bits.size(); j++) {
			if (bits[j] == false)
				std::cout << zero << std::endl;
			else if (bits[j] == true)
				std::cout << one << std::endl;
		}
	}
	return 0;
}

int	main(int argc, char **argv) {
	if (argc <= 1 || argc > 3 || argv[1] == "help") {
		std::cout << "./stoq [string] [gates]" << std::endl;
		std::cout << "\tgates: X,Y,Z,H" << std::endl;
		exit(0);
	}
	
	if (argc == 3) {
		string2Packet(argv[1], argv[2]);
	}
	else if (argc == 2) {
		string2Packet(argv[1], "");
	}

	return 0;
}

