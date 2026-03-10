#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class HighScore {

	const std::string HIGHSCORE_FILE1 = "highscore1.txt";
	const std::string HIGHSCORE_FILE2 = "highscore2.txt";
	const std::string HIGHSCORE_FILE3 = "highscore3.txt";
	const std::string HIGHSCORE_FILE4 = "highscore4.txt";

private:
	unsigned long long m_highscore;
	std::string HIGHSCORE_FILE_NAME;
public:
	// Constructor, sets value of highest score from file
	HighScore(int difficulty);

	void setHighScore(unsigned long long new_highscore); // set new high score

	unsigned long long getHighScore(); // get new high score

	void resetHighScore();
};

#endif