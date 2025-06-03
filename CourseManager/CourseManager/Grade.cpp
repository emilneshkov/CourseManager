#include "Grade.h"
#include <fstream>
#include "StringHelper.h"

Grade::Grade()
{
	this->score = -1;
	this->comment = MyString();
}

Grade::Grade(double score, const MyString& comment)
{
	this->score = score;
	this->comment = comment;
}

double Grade::getScore() const
{
	return score;
}

const MyString& Grade::getComment() const
{
	return comment;
}

void Grade::saveToBinary(std::ofstream& ofs) const {
	ofs.write(reinterpret_cast<const char*>(&score), sizeof(score));

	writeString(ofs, comment);

}
void Grade::loadFromBinary(std::ifstream& ifs) {
	ifs.read(reinterpret_cast<char*>(&score), sizeof(score));

	readString(ifs, comment);
}