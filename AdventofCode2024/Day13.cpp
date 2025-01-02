#include "Day13.h"

int Day13::run() {
	std::string text;
	std::ifstream file("./day13input.txt");

	int result1 = 0;
	double result2 = 0;
	/*
	* system of equations
	* working off Ax = b
	*/
	while (getline(file, text)) {
		int x1 = stoi(text.substr(text.find('+')+1));
		int y1 = stoi(text.substr(text.find(',')+3));
		getline(file, text);
		int x2 = stoi(text.substr(text.find('+')));
		int y2 = stoi(text.substr(text.find(',') + 3));

		Eigen::Matrix2d a;
		a << x1, x2, y1, y2;
		/*
			x1, x2
			y1, y2
		*/

		getline(file, text);
		int x3 = stoi(text.substr(text.find("=")+1));
		int y3 = stoi(text.substr(text.find(",")+4));

		Eigen::Vector2d b;
		b << x3, y3;
		/*
			x3
			y3
		*/

		getline(file, text);
		//solving Linear equations using an inverse matrix
		//Matrix A has an inverse if:
		//A is square
		//nonsingular (by definition, singular = no inverse)
		//determinate = ad - bc, or in our case: x1y2 - x2y1
		//if det(A) == 0, our matrix is singular, no inverse
		/* none actually got determined.
		if (a.determinant() == 0) {
			//std::cout << "determined" << std::endl;
			continue;
		}
		*/
		
		//Ax = b
		//A^-1(Ax) = A^-1(b)	//multiply both sides by inverseA
		//(A^-1 * A)x = A^-1(b)	//transitive multiplication
		//(I)x =  A^-1(b)		//inverseA * A = Identity, we can say identity = 1
		//x = A^-1(b)
		//so, x = (inverse of a) * b
		Eigen::Vector2d v1 = a.inverse() * b;

		//if the result is an int (within tolerance), we have an answer
		if (isNearInt(v1)) {
			result1 += std::round(v1[0]) * 3;
			result1 += std::round(v1[1]);
		}

		//part 2
		//literally same thing, but b + 10000000000000
		Eigen::Vector2d c;
		c << x3 + 10000000000000, y3 + 10000000000000;
		Eigen::Vector2d v2 = a.inverse() * c;
		if (isNearInt(v2)) {
			result2 += std::round(v2[0]) * 3;
			result2 += std::round(v2[1]);
		}
	}
	std::cout << std::setw(4) << "13: " << std::setw(20) << result1 << " " << std::setw(20) << (long long)result2 << std::endl;
	return 1;
}

bool Day13::isNearInt(Eigen::Vector2d x) {
	//this was consistently faster by like 100us
	if (std::abs(x[0] - std::round(x[0])) > 1e-3 ||
		std::abs(x[1] - std::round(x[1])) > 1e-3) {
		return false;
	}
	return true;
	/*
	return std::abs(x[0] - std::round(x[0])) <= 1e-3 &&
		std::abs(x[1] - std::round(x[1])) <= 1e-3;
	*/
}