#pragma once
#include "MyString.h"

class Grade {
	double score;
	MyString comment;

public:
	Grade();
	Grade(double score, const MyString& comment);

	double getScore()const;
	const MyString& getComment() const;

	void saveToBinary(std::ofstream& ofs) const;
	void loadFromBinary(std::ifstream& ifs);
};