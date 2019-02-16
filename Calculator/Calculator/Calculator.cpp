/**
	Calculator

	main.cpp
	Calculator.cpp

	Description: 
	Flow text calculator capable of basic arithmetic (Addition, Substraction, Multiplication, Division, Parenthesis).

	To-Do:
	- Code optimization.

	versions:
		ver 1.2:
		- Add capability of calculating exponentials.
		- Add capability of calculating factorial.

		ver 1.1:
		- Added capability of recognizing negative numbers.
		- Added extensive code documentation.
		- Some code optimization.

	@author Dominique Lahl
	@version 1.2 16/02/2019
*/

#include <iostream>
#include <string>
#include <Windows.h>
#include "Banner.cpp" class Banner

#define PRINT(x); std::cout << x << std::endl;
#define DEBUG(x, y); std::cout << x << ": " << y << std::endl;

class Calculator {
/**
	Class for the calculator. 
*/
public:
	void main() {
		/**
			Main function for the calculator. Deploys all operation-functions and shows the main menu.
		*/
		
		// Creates and prints the banner through Banner-class of another file.
		Banner banner("Calculator", "-+*/^", 12, 7, 2);
		std::cout << banner.createBanner();

		// Application-loop. While this runs, the app is running.
		while (true) {
			std::cout << "\n['x' as first character to close]\n";
			std::cout << "Enter a calculation:\n";


			std::string calculation;
			std::cin >> calculation;

			// Will clear the terminal.
			system("CLS");

			calculation = input_check(calculation); 
			 
			if (calculation == "") {
				break;
			}
			
			else if (calculation != " ") {
				// Will work through operations by priority.
				calculation = parenthesis_calculation(calculation);
				DEBUG("Paranthesis result", calculation)
				calculation = factorial_calculation(calculation);
				DEBUG("Factorial result", calculation);
				calculation = exponential_calculation(calculation);
				DEBUG("Exponential result", calculation)
				calculation = multiplication_calculation(calculation);
				DEBUG("Multiplication result", calculation)
				calculation = division_calculation(calculation);
				DEBUG("Division result", calculation)
				calculation = addition_calculation(calculation);
				DEBUG("Addition result", calculation)
				calculation = substraction_calculation(calculation);
				DEBUG("Substraction result", calculation)
			}
		}
	}

private:
	std::string parenthesis_calculation(std::string calc) {
		/**
			Function for calculation of parenthesis' content. Works through every operation
			with substr of the calculation.

			@param calc String with the calculation.
			@returns String with the finished calculation.
		*/

		size_t pt_b;

		while (true) {
			pt_b = calc.find('(');

			if (pt_b != std::string::npos) {
				size_t pt_e = calc.find(')');

				std::string sub_calc = division_calculation(calc.substr(pt_b + 1, (pt_e - pt_b - 1)));

				sub_calc = factorial_calculation(sub_calc);
				sub_calc = exponential_calculation(sub_calc);
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

	std::string factorial_calculation(std::string calc) {
		/**
			Function for calculation of factorial operations.

			@param calc String with the calculation.
			@returns String with the finished calculation.
		*/

		size_t factorial;

		while (true) {
			factorial = calc.find('!');

			if (factorial != std::string::npos) {
				int size_a;
				double a;

				number_size(calc, 1, '!', &size_a, &a);

				unsigned long long int b = a;

				for (unsigned long long int i = a - 1; i > 0; i--) {
					b = b * i;
				}

				calc.replace((factorial - size_a), size_a + 1, std::to_string(b));
			}

			else {
				return calc;
				break;
			}
		}
	}

	std::string exponential_calculation(std::string calc) {
		/**
					Function for calculation of exponential operations.

					@param calc String with the calculation.
					@returns String with the finished calculation.
				*/

		size_t exponent;

		while (true) {
			exponent = calc.find('^');

			if (exponent != std::string::npos) {
				int size_a, size_b;
				double a, b;

				number_size(calc, 1, '^', &size_a, &a);
				number_size(calc, 2, '^', &size_b, &b);

				for (double i = b; i <= b; i++) {
					a *= a;
				}

				int size_c = size_a + size_b + 1;

				calc.replace((exponent - size_a), size_c, std::to_string(a));
			}

			else {
				return calc;
				break;
			}
		}
	}

	std::string multiplication_calculation(std::string calc) {
		/**
			Function for calculation of multiplication operations.

			@param calc String with the calculation.
			@returns String with the finished calculation.
		*/

		size_t multiplicator;

		while (true) {
			multiplicator = calc.find('*');

			if (multiplicator != std::string::npos) {
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

	std::string division_calculation(std::string calc) {
		/**
			Function for calculation of division operations.

			@param calc String with the calculation.
			@returns String with the finished calculation.
		*/

		// 'size_t' to work with find function.
		size_t divisor;

		while (true) {
			divisor = calc.find('/');

			// 'string::npos' means it didn't find anything.
			if (divisor != std::string::npos) {
				// Variables for size of both numbers and the numbers themself. Numbers stored as double
				// for division operations.
				int size_a, size_b;
				double a, b;

				// Will look at number in both directions of divisor. Values will be set through pointer.
				number_size(calc, 1, '/', &size_a, &a);
				number_size(calc, 2, '/', &size_b, &b);

				double c = a / b;
				int size_c = size_a + size_b + 1;

				calc.replace((divisor - size_a), size_c, std::to_string(c));
			}

			// If no divisor is found, calculation will be returned.
			else {
				return calc;
				break;
			}
		}
	}

	std::string addition_calculation(std::string calc) {
		/**
			Function for calculation of addition operations.

			@param calc String with the calculation.
			@returns String with the finished calculation.
		*/

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
		/**
			Function for calculation of substraction operations.

			@param calc String with the calculation.
			@returns String with the finished calculation.
		*/

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

	std::string input_check(std::string calc) {
		/**
			Controls if the input is a calculation. Uses the ascii-codes of the respective
			character for that.

			@param calc String with the input.
			@returns Either the calculation or string for decision of operation in main() function.
		*/

		if (calc[0] != '-' && calc[0] != 'x' && !((int(calc[0]) <= 57) && (int(calc[0]) >= 48))) {
			// To make sure that an operator, except for '-', won't be at the first position.
			calc.erase(0, 1);
		}

		for (int i = 0; i <= calc.size() - 1; i += 1) {
			// Loop to control input. Mistakes will result in a return, otherwise the loop will just
			// run through
			if (calc[i] == 'x') {
				// Character to exit application.
				return "";
			}

			// Ascii characters: 48 - 57 = 0 - 9; 40 = '('; 41 = ')'; 42 = '*'; 43 = '+';
			else if ((((int(calc[i]) <= 57) && (int(calc[i]) >= 48)) || (int(calc[i]) >= 40 && int(calc[i] <= 43)) || 
					 calc[i] == ' ' || calc[i] == '!' || calc[i] == '-' || calc[i] == '/' || calc[i] == '^')) {}

			else {
				PRINT("Please only numbers and allowed symbols!\n'+' - Plus\n'-' - Minus\n'*' Multipli\n'/' Divisi\n'^' Potenz")
					return " ";
			}
		}

		return calc;
	}

	void number_size(std::string sub_calc, int direction, char opt_char, int* number_size, double* number) {
		/**
			Returns numbers and their sizes going forward and backwards.

			@param sub_calc String with the calculation substr.
			@param direction Decides the direction of the number to be analyzed.
			@param opt_char Looks for the operator of the respective sub calculation.
			@param *number_size Value of the size of the number. Pointer.
			@param *number Value of respective number. Pointer.
		*/

		size_t opt = sub_calc.find(opt_char);
		size_t opt_before; 
		size_t opt_after;

		if (direction == 1) {
			// Size of number going <-.
			opt_before = sub_calc.find_last_of("+-*/^", opt - 1);

			if (opt_before != std::string::npos) {
				*number_size = static_cast<int>(opt - opt_before - 1);
				sub_calc = sub_calc.substr(opt_before + 1, reinterpret_cast<unsigned long long int>(number_size));
				// Changes string to double.
				*number = atof(sub_calc.c_str());
			}

			else {
				*number_size = static_cast<int>(opt);
				sub_calc = sub_calc.substr(0, reinterpret_cast<unsigned long long int>(number_size));
				*number = atof(sub_calc.c_str());
			}
		}

		else if (direction == 2) {
			// Size of number going ->.
			// If the number is negative, the next operator after the '-' will be looked for.
			if (sub_calc[opt + 1] == '-') {
				opt_after = sub_calc.find_first_of("+-*/^", opt + 2);
			}

			else {
				opt_after = sub_calc.find_first_of("+-*/^", opt + 1);
			}

			if (opt_after != std::string::npos) {
				*number_size = static_cast<int>(opt_after - opt - 1);
				sub_calc = sub_calc.substr(opt + 1, reinterpret_cast<unsigned long long int>(number_size));
				*number = atof(sub_calc.c_str());
			}

			else {
				*number_size = static_cast<int>(sub_calc.size() - opt - 1);
				sub_calc = sub_calc.substr(opt + 1, reinterpret_cast<unsigned long long int>(number_size));
				*number = atof(sub_calc.c_str());
			}
		}
	}
};