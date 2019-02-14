// Calculatorv.cpp : Calculator capable of basic mathematics (Addition, Substraction, Multiplication, Division, Parenthesis).				
// ver: 1.0
// to-do: 

#include <iostream>
#include <string>
#include <Windows.h>
#include "Banner.cpp" class Banner

#define PRINT(x); std::cout << x << std::endl;
#define DEBUG(x, y); std::cout << x << ": " << y << std::endl;

class Calculator {

public:
	void main() {
		Banner banner("Calculator", "-+*/^", 12, 7, 2);
		std::cout << banner.createBanner();

		while (true) {
			std::cout << "\n['x' as first character to close]\n";
			std::cout << "Enter a calculation:\n";

			std::string calculation;
			std::cin >> calculation;

			system("CLS");

			calculation = input_check(calculation); 
			 
			if (calculation == "") {
				break;
			}else {
				calculation = parenthesis_calculation(calculation);
				calculation = division_calculation(calculation);
				calculation = multiplication_calculation(calculation);
				calculation = addition_calculation(calculation);
				calculation = substraction_calculation(calculation);
				PRINT(calculation)
			}
		}
	}

private:
	std::string input_check(std::string calc) {
		int will_calulate = -1;
		if (calc[0] != '-' && calc[0] != 'x' && !((int(calc[0]) <= 57) && (int(calc[0]) >= 48))) {
			calc.erase(0, 1);
		}
		for (int i = 0; i <= calc.size() - 1; i += 1) {
			if (calc[i] == 'x') {
				return "";
			}
			else if ((((int(calc[i]) <= 57) && (int(calc[i]) >= 48)) || (int(calc[i]) >= 40 && int(calc[i] <= 43)) ||
				int(calc[i] == 32 || int(calc[i]) == 45 || int(calc[i]) == 47 || int(calc[i]) == 94))) {
				will_calulate += 1;
			}
			else {
				PRINT("Please only numbers and allowed symbols!\n'+' - Plus\n'-' - Minus\n'*' Multipli\n'/' Divisi\n'^' Potenz")
					break;
			}
		}
		if (will_calulate == calc.size() - 1) {
			return calc;
		}
	}

	std::string division_calculation(std::string calc) {
		size_t divisor;
		while (true) {
			divisor = calc.find('/');
			if (divisor != std::string::npos) {
				int size_a, size_b;
				double a, b;
				number_size(calc, 1, '/', &size_a, &a);
				number_size(calc, 2, '/', &size_b, &b);
				double c = a / b;
				int size_c = size_a + size_b + 1;
				calc.replace((divisor - size_a), size_c, std::to_string(c));
			}
			else {
				return calc;
				break;
			}

		}

	}

	std::string multiplication_calculation(std::string calc) {
		size_t multiplicator;
		while (true) {
			multiplicator = calc.find('*');
			if (multiplicator != std::string::npos){
				int size_a, size_b;
				double a, b;
				number_size(calc, 1, '*', &size_a, &a);
				number_size(calc, 2, '*', &size_b, &b);
				double c = a * b;
				int size_c = size_a + size_b + 1;
				calc.replace((multiplicator - size_a), size_c, std::to_string(c));
			}
			else {
				return calc;
				break;
			}
		}
	}

	std::string addition_calculation(std::string calc) {
		size_t plus;
		while (true) {
			plus = calc.find('+');
				if (plus != std::string::npos) {
					int size_a, size_b;
					double a, b;
					number_size(calc, 1, '+', &size_a, &a);
					number_size(calc, 2, '+', &size_b, &b);
					double c = a + b;
					int size_c = size_a + size_b + 1;
					calc.replace((plus - size_a), size_c, std::to_string(c));
				}
				else {
					return calc;
					break;
				}
		}
	}

	std::string substraction_calculation(std::string calc) {
		size_t minus;
		while (true) {
			minus = calc.find('-');
			if (minus != std::string::npos && minus != 0) {
				int size_a, size_b;
				double a, b;
				number_size(calc, 1, '-', &size_a, &a);
				number_size(calc, 2, '-', &size_b, &b);
				double c = a - b;
				int size_c = size_a + size_b + 1;
				calc.replace((minus - size_a), size_c, std::to_string(c));
			}
			else {
				return calc;
				break;
			}
		}
	}

	std::string parenthesis_calculation(std::string calc) {
		size_t pt_b;

		while (true) {
			pt_b = calc.find('(');
			if (pt_b != std::string::npos) {
				size_t pt_e = calc.find(')');
				std::string sub_calc = division_calculation(calc.substr(pt_b + 1, (pt_e - pt_b - 1)));
				sub_calc = multiplication_calculation(sub_calc);
				sub_calc = addition_calculation(sub_calc);
				sub_calc = substraction_calculation(sub_calc);
				calc.replace(pt_b, (pt_e - pt_b + 1), sub_calc);
			}
			else {
				return calc;
				break;
			}
		}
	}

	void number_size(std::string sub_calc, int direction, char opt_char, int* number_size, double* number) {
		/*
		 Returns size of number going forward or backwards.
		*/
		if (direction == 1) {
			// Size of number going <-.
			size_t opt = sub_calc.find(opt_char);
			size_t opt_before = sub_calc.find_last_of("+-*/^", opt - 1);
			if (opt_before != std::string::npos) {
				*number_size = static_cast<int>(opt - opt_before - 1);
				sub_calc = sub_calc.substr(opt_before + 1, reinterpret_cast<unsigned long long int>(number_size));
				*number = atof(sub_calc.c_str());
			}
			else {
				*number_size = static_cast<int>(opt);
				*number = stoi(sub_calc.substr(0, reinterpret_cast<unsigned long long int>(number_size)));
			}
		}
		else if (direction == 2) {
			// Size of number going ->.
			size_t opt = sub_calc.find(opt_char);
			size_t opt_after = sub_calc.find_first_of("+-*/^", opt + 1);
			if (opt_after != std::string::npos) {
				*number_size = static_cast<int>(opt_after - opt - 1);
				sub_calc = sub_calc.substr(opt + 1, reinterpret_cast<unsigned long long int>(number_size));
				*number = atof(sub_calc.c_str());
			}
			else {
				*number_size = static_cast<int>(sub_calc.size() - opt - 1);
				*number = stoi(sub_calc.substr(opt + 1, reinterpret_cast<unsigned long long int>(number_size)));
			}
		}

	}
	
};


