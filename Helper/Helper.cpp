#include "Helper.h"

void Helper::clearConsole() {
	system("cls");  //Aufruf um Console zu löschen, in Linux cls = clear
}

void Helper::resetField() {
	for (int i = 0; i < 10; i++) {
		field[i] = " ";
	}
}

void Helper::drawField() {
	//clearConsole();
	std::cout << "" << std::endl;
	std::cout << field[1] << " | " << field[2] << " | " << field[3] << std::endl
		<< "..|...|.." << std::endl
		<< field[4] << " | " << field[5] << " | " << field[6] << std::endl
		<< "..|...|.." << std::endl
		<< field[7] << " | " << field[8] << " | " << field[9] << std::endl
		<< "..|...|.." << std::endl;
}

bool Helper::isDigit(const std::string& value) {
	for (int i = 0; i < value.length(); i++) {
		if (isdigit(value[i]) == false) {
			return false;
		}
	}
	return true;
}

bool Helper::checkWin(std::string player) {
	return (field[1] == player && field[2] == player && field[3] == player) || (field[4] == player && field[5] == player && field[6] == player) ||
		(field[7] == player && field[8] == player && field[9] == player) || (field[1] == player && field[4] == player && field[7] == player) ||
		(field[2] == player && field[5] == player && field[8] == player) || (field[3] == player && field[6] == player && field[9] == player) ||
		(field[1] == player && field[5] == player && field[9] == player) || (field[3] == player && field[5] == player && field[7] == player);
}

bool Helper::checkFull() {
	for (int i = 1; i <= 9; i++) {
		if (field[i] == " ")
			return false;
	}
	return true;
}

bool Helper::writeInput(int input, bool player1) {
	std::cout << "writeInput with input: " << input << " and player1: " << player1 << std::endl;
	if (field[input] == " ") {
		if (player1) {
			field[input] = "x";
		}
		else {
			field[input] = "o";
		}
		return true;
	}
	else {
		std::cout << "Position is already filed: " << field[input] << " Try again." << std::endl;
		inputPlayerSwitchValid = false;
		if (!player1) {
			int newPosition = nextAvailablePosition(input);
			std::cout << "Get new position " << newPosition << std::endl;
			field[newPosition] = "o";
			return true;
		}	
	}
	return false;
}

int Helper::nextAvailablePosition(int position) {
	std::vector<int> vec;
	for (int i = 1; i < 10; i++) {
		if (field[i] == " ")
			vec.push_back(i);
	}
	if (!vec.empty()) {
		for (auto value : vec) {
			std::cout << "Look at value: " << value << std::endl;
			if (value > position)
				return value;
		}
		std::cout << "Look at vec.front() " << vec.front() << std::endl;
		return vec.front();
	}
	return -1;
}

std::string Helper::keyInput(bool player1) {
	std::string input{ ' ' };
	std::cout << "Input:";
	std::cin >> input;
	std::cout << std::endl;

	if (isDigit(input)) {
		int inputValue = std::stoi(input);
		if (0 < inputValue && inputValue < 10) {
			writeInput(inputValue, player1);
		}
		else {
			std::cout << "Number is to high. Try again." << std::endl;
			inputPlayerSwitchValid = false;
		}
	}
	else {
		std::cout << "Current input was not valid. Try again" << std::endl;
		inputPlayerSwitchValid = false;
	}
	std::cout << "Return value is: " << input << std::endl;
	return input;
}

bool Helper::checkIfWinExist() {
	if (checkWin("x")) {
		std::cout << "Player 1 wins the game!" << std::endl;
		return true;
	}
	else if (checkWin("o")) {
		std::cout << "Player 2 wins the game!" << std::endl;
		return true;
	}
	else if (checkFull()) {
		std::cout << "It is a draw." << std::endl;
		return true;
	}
	return false;
}

void Helper::singlePlayer() {
	std::string input{ ' ' };
	bool inputPlayer1 = true;
	resetField();
	inputPlayerSwitchValid = true;
	while (input != "q") {
		drawField();
		input = keyInput(inputPlayer1);
		std::cout << "Input is : " << input << std::endl;
		bool playerWin = checkIfWinExist();
		if (playerWin)
			input = "q";
		if (!playerWin && inputPlayerSwitchValid) {
			int randomNumber = (rand() % 9) + 1;
			std::cout << "randomNumber : " << randomNumber << std::endl;
			bool writeSuccess{ false };
			do {
				writeSuccess = writeInput(randomNumber, false);
			} while (!writeSuccess);
			checkIfWinExist();
		}
		inputPlayerSwitchValid = true;
	}
	drawField();
}

void Helper::multiPlayer() {
	std::string input{ ' ' };
	bool inputPlayer1 = true;
	resetField();
	inputPlayerSwitchValid = true;
	while (input != "q") {
		drawField();
		input = keyInput(inputPlayer1);
		std::cout << "Input is : " << input << std::endl;
		if (inputPlayerSwitchValid) {
			if (inputPlayer1 == true) {
				inputPlayer1 = false;
			}
			else {
				inputPlayer1 = true;
			}
		}
		bool playerWin = checkIfWinExist();
		if (playerWin)
			input = "q";
		inputPlayerSwitchValid = true;
	}
	drawField();
}

void Helper::help() {
	std::cout << "HELP" << std::endl
		<< "SinglePlayer: In Singleplayer you play against the computer" << std::endl
		<< "MultiPlayer: In Multiplayer you play against another Player" << std::endl
		<< "Quit: You end the game" << std::endl;
}

Helper::Helper():
inputPlayerSwitchValid(false)
{
}

void Helper::menu() {
	bool running(true);
	while (running) {
		char inputMenu;
		std::cout << "\n\n"
			<< "MENU \n\n"
			<< "1: SinglePlayer \n"
			<< "2: MultiPlayer \n"
			<< "3: Help \n"
			<< "4: Quit \n\n\n"
			<< "Input: ";
		std::cin >> inputMenu;

		switch (inputMenu) {
		case '1':
			singlePlayer();
			break;
		case '2':
			multiPlayer();
			break;
		case '3':
			help();
			break;
		case '4':
		case 'q':
			running = false;
			break;
		default:
			//clearConsole();
			std::cout << " \n Invalid input!" << std::endl;
		}
	}
}