#include <iostream>
#include <fstream>
#include <string>
#include <vector>


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

	// Output the data stored in dataFrame 
	for (unsigned i = 0; i < dataFrame.size(); i++) {
		std::cout << "Plant ID # " << dataFrame[i].id << "\n";
		std::cout << "\tSepal Length: " << dataFrame[i].sepalLength << '\n';
		std::cout << "\tSepal Width: " << dataFrame[i].sepalWidth << '\n';
		std::cout << "\tPetal Length: " << dataFrame[i].petalLength << '\n';
		std::cout << "\tPetal Width: " << dataFrame[i].petalWidth << '\n';
		std::cout << "\tSpecies: " << dataFrame[i].species << '\n';
	}

	return 0;

}