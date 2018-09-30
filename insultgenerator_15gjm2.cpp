//============================================================================
// Name        : Hello.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
 * The implementation of the TextFileIO object.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>

#include "insultgenerator_15gjm2.h"

using namespace std;

FileException::FileException(const string& m) : message(m) {} //exception constructor

string FileException::what() const {
		return message;
}

InsultGenerator::InsultGenerator() : sourceLength(0) {} //insult constructor

void InsultGenerator::initialize() {
	string line;
	ifstream fileIn(INSULTS_SOURCE.c_str());
	sourceLength = 0;
	if (fileIn.is_open()) {
		while (!fileIn.eof()) {
			fileIn >> line;
			firstAdjective.push_back(line);
			fileIn >> line;
			secondAdjective.push_back(line);
			fileIn >> line;
			noun.push_back(line);
			sourceLength += 1;
		}
		fileIn.close();
	} else if (fileIn.fail()) {
		throw FileException("Insults source file: " + INSULTS_SOURCE + " cannot be read");
		return;
	}
}

int InsultGenerator::randomInt(int bound) {
	int randInt = rand() % bound;
	return randInt;
}

string InsultGenerator::talkToMe() {
	// Since strings are mutable in C++, can directly append the insults to it.
	string insult("Thou ");

	insult += firstAdjective.at(randomInt(sourceLength));
	insult += " " + secondAdjective.at(randomInt(sourceLength));
	insult += noun.at(randomInt(sourceLength));

	return insult;
}
NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& m) : message(m) {}

string NumInsultsOutOfBounds::what() const {
	return message;
}

vector<string> InsultGenerator::generate(int numInsults) {
	if (numInsults < 1 || numInsults > maxNumOfInsults) {
		throw NumInsultsOutOfBounds("This is not a valid number");
	}

	set<string> setOfInsults;
	string insult;

	while (numInsults > setOfInsults.size()) {
		insult = string(talkToMe());
		setOfInsults.insert(insult);
	}

	vector<string> insults;
	copy(setOfInsults.begin(), setOfInsults.end(), back_inserter(insults));
	return insults;
}

void InsultGenerator::generateAndSave(string filename, int numInsults) {
	int lineNumber = 0;
	vector<string> insultVector = generate(numInsults);
	ofstream fileOut(filename.c_str());

	if (fileOut.fail()) {
		throw FileException("Your File: " + filename + " cannot be written");
	}

	while(lineNumber < numInsults) {
		fileOut << insultVector[lineNumber] << endl;
		lineNumber += 1;
	}
	fileOut.close();
}
