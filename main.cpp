#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <tuple>

struct Data {
	int id;
	float sepalLength;
	float sepalWidth;
	float petalLength;
	float petalWidth;
	std::string species;
	friend std::istream& operator>>(std::istream& input, Data& df);
};

// Overload the >> operator to parse the input stream into the Data struct
std::istream& operator>>(std::istream& input, Data& df)
{
	char comma;
	input >> df.id;
	input >> comma;
	input >> df.sepalLength;
	input >> comma;
	input >> df.sepalWidth;
	input >> comma;
	input >> df.petalLength;
	input >> comma;
	input >> df.petalWidth;
	input >> comma;
	std::getline(input, df.species, '\n');
	return input;
}



// Gradient descent function
std::tuple<float,float> gradient_descent(const std::vector<Data>& df, float m, float b, double L) {
	float m_gradient{0};
	float b_gradient{0};
	const int df_size = df.size();

	for (unsigned i = 0; i < df_size; i++) {
		float x = df[i].sepalLength;
		float y = df[i].petalLength;

		m_gradient += x * (y - (m * x + b));
		b_gradient +=  y - (m * x + b);
	}
	
	float new_m = m - (-2.0f / df_size) * m_gradient * L;
	float new_b = b - (-2.0f / df_size) * b_gradient * L;
	return { new_m, new_b };
}


int main() {
	
	std::ifstream f("Data/Iris.csv");
	std::vector<Data> dataFrame;
	Data data;

	// Read the file
	if (f.is_open()) { 

		// Skip the header line.
		std::string headerline;
		std::getline(f, headerline);

		while (f >> data) {
			dataFrame.push_back(data);
	}
		f.close();
	}

	float m = 0;
	float b = 0;
	const double learning_rate{ 0.0001 };
	const int epochs = 5000;

	std::tuple<float, float> vals{};

	for (int i = 0; i < epochs; i++) {
		
		vals = gradient_descent(dataFrame, m, b, learning_rate);
		m = std::get<0>(vals);
		b = std::get<1>(vals);
		
		if (i % 100 == 0) {
			std::cout << "Epoch: " << i << "\n";
		}
	}

	std::cout << "Final m: " << m << '\n';
	std::cout << "Final b: " << b;
	
	return 0;
}