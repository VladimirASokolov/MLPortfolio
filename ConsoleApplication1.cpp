#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

double sumV(vector<double> vect) {
	double s = 0;
	for (auto& n : vect)
		s += n;
	return s;
}

double meanV(vector<double> vect) {
	return (sumV(vect) / vect.size());
}

double medianV(vector<double> vect) {
	vector<double> vCopy(vect);
	int s = vCopy.size();
	sort(vCopy.begin(), vCopy.end());
	if (s % 2 == 0)
		return (vCopy[s / 2 - 1] + vCopy[s / 2]) / 2;
	else
		return vCopy[s / 2];
	return 0;
}

double rangeV(vector<double> vect) {
	vector<double> vCopy(vect);
	sort(vCopy.begin(), vCopy.end());
	return (vCopy.back() - vCopy.front());
}

double covar(vector<double> vRM, vector<double> vMEDV) {
	double s = 0;
	double m1 = meanV(vRM);
	double m2 = meanV(vMEDV);
	for (int i = 0; i < vRM.size(); i++)
		s = s + (vRM[i] - m1) * (vMEDV[i] - m2);
	return s / (vRM.size() - 1);
}

double cor(vector<double> vRM, vector<double> vMEDV) {
	double s1 = 0;
	double s2 = 0;
	double m1 = meanV(vRM);
	double m2 = meanV(vMEDV);
	for (int i = 0; i < vRM.size(); i++) {
		s1 = s1 + pow(vRM[i] - m1,2);
		s2 = s2 + pow(vMEDV[i] - m2, 2);
	}
	return (covar(vRM, vMEDV) / (sqrt(s1/(vRM.size()-1))* sqrt(s2 / (vRM.size() - 1))));
}

void print_stats(vector<double> vect) {
	cout << "\n Sum = " << sumV(vect) << endl;
	cout << "\n Mean = " << meanV(vect) << endl;
	cout << "\n Median = " << medianV(vect) << endl;
	cout << "\n Range = " << rangeV(vect) << endl;
}

int main(int argc, char** argv)
{
	ifstream inFS;
	string line;
	string rm_in, medv_in;
	const int MAX_LEN = 1000;
	vector<double> rm(MAX_LEN);
	vector<double> medv(MAX_LEN);

	cout << "Opening file Boston.csv." << endl;

	inFS.open("Boston.csv");
	if (!inFS.is_open()) {
		cout << "Could not open file Boston.csv." << endl;
		return 1;
	}

	cout << "Reading line 1" << endl;
	getline(inFS, line);

	cout << "heading: " << line << endl;

	int numObservations = 0;
	while (inFS.good()) {
		getline(inFS, rm_in, ',');
		getline(inFS, medv_in, '\n');
		rm.at(numObservations) = stof(rm_in);
		medv.at(numObservations) = stof(medv_in);
		numObservations++;
	}

	rm.resize(numObservations); medv.resize(numObservations);

	cout << "new length " << rm.size() << endl;

	cout << "Closing file Boston.csv." << endl;
	inFS.close();
	cout << "number of records: " << numObservations << endl;

	cout << "\nStats for rm" << endl;
	print_stats(rm);

	cout << "\nStats for medv" << endl;
	print_stats(medv);

	cout << "\n Covariance = " << covar(rm, medv) << endl;

	cout << "\n Correlation = " << cor(rm, medv) << endl;

	cout << "\nProgram terminated.";

	return 0;
}