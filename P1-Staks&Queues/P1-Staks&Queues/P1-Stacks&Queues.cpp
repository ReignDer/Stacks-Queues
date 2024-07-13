#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
//Mathieu Marc Pobre
class blitzGame {
private:
	std::vector<char>stack;
	std::queue<char>elements;
	int score;
	int numQuery;
public:
	blitzGame() : score(0), numQuery(0){}

	//creates a queue
	void createQueue(std::string text) {
		for (int i = 0; i < text.size(); i++) {
			elements.push(text[i]);
		}
	}

	//Displays the query
	void displayQuery(){
		numQuery++;
		std::cout << "Query #"<< numQuery <<": " << '\n';
		std::cout << "Player Score: " << score << '\n';
		std::cout << "Current State of Game: " << '\n';
		for (int i = 0; i < stack.size(); i++)
			std::cout << stack[i];
		std::cout << '\n' << '\n';
		elements.pop();
	}

	//checks if there are three consecutive gems and pops them out of stack
	void checkStack(char element) {
		if (stack.back() == element && stack[stack.size() - 2] == element)
		{
			for (int i = 0; i < 2; i++) {
				stack.pop_back();
				score++;
			}
			elements.pop();
			score++;
		}


		else {
			stack.push_back(elements.front());
			elements.pop();
		}
	}

	//checks the queue if the top is 'Q', 'E', or a gem
	void checkElements(char element) {
		
		switch (element) {
			case 'Q':
				displayQuery();
				break;
			case 'E':
				//empties the queue
				std::queue<char>().swap(elements);
				break;

			default:
				//stacking or popping gems
				checkStack(element);
				break;
		}
	}

	//state of the game
	void query() {
		while (!elements.empty()) {
			if (stack.size() < 2) {
				stack.push_back(elements.front());
				elements.pop();
			}
			else{
				checkElements(elements.front());
			}
		}
	}

	//check the stack if contents are right
	void display() {
		for (int i = 0; i < stack.size(); i++)
			std::cout << stack[i];
	}
};
int main() {
	std::string text;
	std::fstream file("blitz.txt");

	blitzGame blitz;

	while (getline(file, text)) {
		//std::cout << text<<'\n';
		blitz.createQueue(text);
	}

	blitz.query();

	//blitz.display();  //for testing END

	file.close();
	return 0;
}