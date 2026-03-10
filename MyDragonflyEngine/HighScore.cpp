#include "HighScore.h"
#include "LogManager.h"


HighScore::HighScore(int difficulty) {
	switch (difficulty) {
	case 1:
		HIGHSCORE_FILE_NAME = HIGHSCORE_FILE1;
		break;
	case 2:
		HIGHSCORE_FILE_NAME = HIGHSCORE_FILE2;
		break;
	case 3:
		HIGHSCORE_FILE_NAME = HIGHSCORE_FILE3;
		break;
	case 4:
		HIGHSCORE_FILE_NAME = HIGHSCORE_FILE4;
		break;
	}
	std::ifstream input(HIGHSCORE_FILE_NAME);
	input >> m_highscore;
}

void HighScore::setHighScore(unsigned long long new_highscore) {
	std::ifstream input(HIGHSCORE_FILE_NAME);
	unsigned long long highest_number;
	input >> highest_number;

	std::ofstream output(HIGHSCORE_FILE_NAME);
	if (new_highscore > highest_number) {
		output << new_highscore;
	}
	else {
		output << highest_number;
	}
}

unsigned long long HighScore::getHighScore() {
	std::ifstream input(HIGHSCORE_FILE_NAME);
	unsigned long long highest_number;
	input >> highest_number;
	return highest_number;
}

void HighScore::resetHighScore() {
	std::ofstream output(HIGHSCORE_FILE_NAME);
	output << 0;
}
