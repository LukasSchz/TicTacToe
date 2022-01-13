#include<iostream>
#include<time.h>
#include<string>
#include<mutex>
#include<stdlib.h>
#include<vector>

class Helper {

private:
	std::string field[10];
	bool inputPlayerSwitchValid;
	std::mutex inputThreadSafe;

	void clearConsole();
	void resetField();
	void drawField();
	void help();
	void singlePlayer();
	void multiPlayer();

	bool isDigit(const std::string& value);
	bool checkWin(std::string player);
	bool checkFull();
	bool checkIfWinExist();
	bool writeInput(int input, bool player1);
	int nextAvailablePosition(int position);

	std::string keyInput(bool player1);

public:
	Helper();
	void menu();

};