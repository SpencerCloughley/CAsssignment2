// C++Asssignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <limits> // for numeric_limits

using namespace std;

int generateRandomNumber(int min, int max) {
	return rand() % (max - min + 1) + min;
}
class Ticket {
private:
	int ticketId;
	vector<int> lineNumbers;
public:
	int getTicketId() {
		return ticketId;
	}
	vector<int> getLineNumbers() {
		return lineNumbers;
	}
	void setTicketId(int id) {
		ticketId = id;
	}
	void setLineNumbers(vector<int> nums) {
		lineNumbers = nums;
	}
};

int main()
{
	srand(time(0)); // Seed the random number generator

	cout << "Lottery Simulation - Lottario\n";

	string playerName;
	int studentNumber;

	char playAgain = 'Y';
	int grandTotalWinnings = 0; // Accumulated winnings across all replays
	int totalSpent = 0;
	int numberOfLines;
	int totalCost;
	int totalWinnings = 0;
	int bonusLines;
	int freeLines=0;
	Ticket nextTicket;
	unordered_set<int> usedNumbers;
	bool validNumber = false;
	vector<Ticket> winningTickets;


	int number;
	char computerGenerate;
	int ticketId=0;

	cout << "Enter your name: "; // User enters their name
	cin >> playerName;

	cout << "Enter your student number: "; // User enters their student number
	while (!(cin >> studentNumber)) {
		cout << "Invalid input. Please enter a valid student number: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	char knowRules;
	while (true) {
		cout << "Do you know the rules & regulations (Y/N)? "; // Asks if they know the rules
		cin >> knowRules;
		cin.ignore();

		if (knowRules == 'Y' || knowRules == 'y' || knowRules == 'N' || knowRules == 'n') {
			break;
		}
		else {
			cout << "Invalid input. Please select 'Y' or 'N'.\n";
		}
	}
	if (knowRules == 'N' || knowRules == 'n') {
		cout << "Rules: You need to pick 7 numbers between 1 and 50.\n";
		cout << "Each line costs 1 CAD.\n";
	}
		

	while (playAgain == 'Y' || playAgain == 'y') {
		vector<Ticket> playerNumbers;      // Store player's numbers for each line
		vector<Ticket> bonusNumbers;		// Store bonus numbers for each line
		vector<Ticket> computerNumbers;    // Store computer's numbers for each line
		cout << "How many lines do you want to play? "; // Asks user how many lines they want.
		while (!(cin >> numberOfLines)) {
			cout << "Invalid input. Please enter how many times you would like to play: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		//To make it more clear, if the player pays for one line to play, one more computer-generated line will also be giving to the player as a bonus line.  - Taken from the Assignment Description
		//In my understanding this means that we are doubling their plays, if they pay for 2 they get 2 bonusLines, if they pay for 10 they get 10 bonusLines
		bonusLines = numberOfLines;
		totalCost = numberOfLines*1; //Each ticket costs $1
		cout << "You are paying $" << totalCost << " CAD to play " << numberOfLines << " draws. You also get " << bonusLines << " bonus draws. \n";
		totalSpent -= totalCost;
		//asking if they would like to generate their lines manually or the computer to generate them
		while (true) {
			cout << "Would you like the computer to generate your lines(Y/N)? ";
			cin >> computerGenerate;
			cin.ignore();

			if (computerGenerate == 'Y' || computerGenerate == 'y' || computerGenerate == 'N' || computerGenerate == 'n') {
				break;
			}
			else {
				cout << "Invalid input. Please select 'Y' or 'N'.\n";
			}
		}
		cout << "\n";
		if (computerGenerate == 'Y' || computerGenerate == 'y') {
			for (int i = 0; i < numberOfLines + freeLines; ++i) {
				vector<int> playerLineNumbers;
				for (int j = 0; j < 7; ++j) {
					number = generateRandomNumber(1, 45);
					playerLineNumbers.push_back(number);
				}
				ticketId++;
				nextTicket.setLineNumbers(playerLineNumbers);
				nextTicket.setTicketId(ticketId);
				playerNumbers.push_back(nextTicket);

				cout << "Computer picked for you: ";
				for (int num : playerLineNumbers) {
					cout << " " << num;
				}
				cout << endl;


				//generates bonus ticket
				vector<int> bonusLineNumbers;
				for (int j = 0; j < 7; ++j) {
					number = generateRandomNumber(1, 45);
					bonusLineNumbers.push_back(number);
				}
				nextTicket.setLineNumbers(bonusLineNumbers);
				bonusNumbers.push_back(nextTicket);

				cout << "Computer picked bonus ticket for you: ";
				for (int num : bonusLineNumbers) {
					cout << " " << num;
				}
				cout << endl;

				//generates winning ticket
				vector<int> computerLineNumbers;
				for (int j = 0; j < 7; ++j) {
					number = generateRandomNumber(1, 45);
					computerLineNumbers.push_back(number);
				}
				nextTicket.setLineNumbers(computerLineNumbers);
				computerNumbers.push_back(nextTicket);

				cout << "\n";
			}
		}
		else {
			for (int i = 0; i < numberOfLines+freeLines; ++i) {
				cout << "Enter 7 unique numbers for Line " << i + 1 << " (between 1 and 45):\n";
				usedNumbers.clear(); // Emptys set of used numbers to start again
				vector<int> playerLineNumbers;
				//For loop to create all the number in the row
				for (int j = 0; j < 7; ++j) {
					
					while (!validNumber) {
						cout << "Enter the " << j + 1 << "th number: ";
						while (!(cin >> number)) {
							cout << "Invalid input. Please a number between 1-45: ";
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}

						if (number < 1 || number > 45) {
							cout << "Invalid number. Number must be between 1 and 45.\n";
						}
						else if (usedNumbers.count(number) > 0) {
							cout << "Number already used. Please enter a different number.\n";
						}
						else {
							playerLineNumbers.push_back(number);
							usedNumbers.insert(number);
							validNumber = true;
						}
					}
				}
				ticketId++;
				nextTicket.setLineNumbers(playerLineNumbers);
				playerNumbers.push_back(nextTicket);

				//generates bonus ticket
				vector<int> bonusLineNumbers;
				for (int j = 0; j < 7; ++j) {
					number = generateRandomNumber(1, 45);
					bonusLineNumbers.push_back(number);
				}
				nextTicket.setLineNumbers(bonusLineNumbers);
				bonusNumbers.push_back(nextTicket);

				//Print out user selected ticket and bonus ticket


				//generates winning ticket
				vector<int> computerLineNumbers;
				for (int j = 0; j < 7; ++j) {
					number = generateRandomNumber(1, 45);
					computerLineNumbers.push_back(number);
				}
				nextTicket.setLineNumbers(computerLineNumbers);
				computerNumbers.push_back(nextTicket);

				cout << "\n";

			}//End of for loop running over number of Lines wanted

		}//End of else for player selected numbers

		//Test to see if there are any matches and if so how many. What do they win if there are matches?
		for (int i = 0; i < numberOfLines; ++i) {
			int matches = 0;
			const vector<int> lineNumbers = playerNumbers[i].getLineNumbers();
			const vector<int> bonusLineNumbers = bonusNumbers[i].getLineNumbers();
			const vector<int> computerLineNumbers = computerNumbers[i].getLineNumbers();

			cout << "Ticket ID: " << playerNumbers[i].getTicketId() << "\n";
			cout << "Generated numbers:";
			for (int number : computerLineNumbers) {
				cout << " " << number;
			}
			cout << "\n";

			//Checks player tickets against the computer tickets
			for (int number : computerLineNumbers) {
				if (find(lineNumbers.begin(), lineNumbers.end(), number) != lineNumbers.end()) {
					++matches;
				}
			}

			cout << "You picked: ";
			for (int num : lineNumbers) {
				cout << " " << num;
			}

			if (matches > 0) {
				cout << "\nCongratulations! You have " << matches << " match(es).";

				switch (matches) {
				case 1:
					cout << "\nYou picked 1 number correctly but you won nothing.\n";
					totalWinnings += 0;
					break;
				case 2:
					cout << "\nYou picked 2 numbers correctly but you won nothing.\n";
					totalWinnings += 0;
					break;
				case 3:
					cout << "\nYou picked 3 numbers correctly and won 10 CAD!\n";
					totalWinnings += 10;
					break;
				case 4:
					cout << "\nYou picked 4 numbers correctly and won 30 CAD!\n";
					winningTickets.push_back(playerNumbers[i]);
					totalWinnings += 30;
					break;
				case 5:
					cout << "\nYou picked 5 numbers correctly and won 500 CAD!\n";
					winningTickets.push_back(playerNumbers[i]);
					totalWinnings += 500;
					break;
				case 6:
					cout << "\nYou picked 6 numbers correctly and won 10,000 CAD!\n";
					winningTickets.push_back(playerNumbers[i]);
					totalWinnings += 1000;
					break;
				case 7:
					cout << "\nYou picked all 7 numbers correctly and won 40,000,000 CAD!\n";
					winningTickets.push_back(playerNumbers[i]);
					totalWinnings += 40000000;
					break;
				}
			}
			else {
				cout << "\nSorry, you didn't win any matches.\n";
			}

			cout << "\n";

			matches = 0;
			//Checks bonus tickets against the computer tickets
			for (int number : computerLineNumbers) {
				if (find(bonusLineNumbers.begin(), bonusLineNumbers.end(), number) != bonusLineNumbers.end()) {
					++matches;
				}
			}
			cout << "Bonus Ticket picked: ";
			for (int num : bonusLineNumbers) {
				cout << " " << num;
			}
			if (matches > 0) {
				cout << "\nCongratulations! You have " << matches << " match(es).";

				switch (matches) {
				case 1:
					cout << "\nYou picked 1 number correctly but you won nothing.\n";
					totalWinnings += 0;
					break;
				case 2:
					cout << "\nYou picked 2 numbers correctly but you won nothing.\n";
					totalWinnings += 0;
					break;
				case 3:
					cout << "\nYou picked 3 numbers correctly and won 10 CAD!\n";
					totalWinnings += 10;
					break;
				case 4:
					cout << "\nYou picked 4 numbers correctly and won 30 CAD!\n";
					winningTickets.push_back(bonusNumbers[i]);
					totalWinnings += 30;
					break;
				case 5:
					cout << "\nYou picked 5 numbers correctly and won 500 CAD!\n";
					winningTickets.push_back(bonusNumbers[i]);
					totalWinnings += 500;
					break;
				case 6:
					cout << "\nYou picked 6 numbers correctly and won 10,000 CAD!\n";
					winningTickets.push_back(bonusNumbers[i]);
					totalWinnings += 1000;
					break;
				case 7:
					cout << "\nYou picked all 7 numbers correctly and won 40,000,000 CAD!\n";
					winningTickets.push_back(bonusNumbers[i]);
					totalWinnings += 40000000;
					break;
				}
			}
			else {
				cout << "\nSorry, you didn't win any matches.\n";
			}
			cout << "\n";
		}

		cout << "Your total winnings for this draw: " << totalWinnings << " CAD.\n";
		grandTotalWinnings += totalWinnings; // Accumulate the winnings for this replay
		//After each play cycle save all the data to word document/text file

		//Play again feature
		cout << "Do you want to play again (Y/N)? ";
		cin >> playAgain;
		cin.ignore();

		if (playAgain != 'Y' && playAgain != 'y') {
			cout << "Thank you for playing!\n";
			cout << "Your grand total winnings: $" << grandTotalWinnings + totalSpent << " CAD.\n"; // Display the accumulated winnings
			//Print out winning tickets
			for (Ticket ticket : winningTickets) {
				for (int num : ticket.getLineNumbers()) {
					cout << " " << num;
				}

			}
		}
	}
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file