/*
 * The declaration file for the TextFileIO class.
 */
#ifndef INSULTGENERATOR
#define INSULTGENERATOR

#include <string>
#include <vector>

using namespace std;

const string INSULTS_SOURCE("InsultsSource.txt");
const int maxNumOfInsults(10000);

class FileException {
public:
	FileException(const string& message);
	string what() const;

private:
	string message;
};

class NumInsultsOutOfBounds {
public:
	NumInsultsOutOfBounds(const string&);
	string what() const;

private:
	string message;
};

class InsultGenerator {
public:
	InsultGenerator();
	void initialize();
	vector<string> generate(int);
	string talkToMe();
	void generateAndSave(string filename, int numInsults);

private:
	int sourceLength;
	vector<string> firstAdjective;
	vector<string> secondAdjective;
	vector<string> noun;
	int randomInt(int);
};
#endif
