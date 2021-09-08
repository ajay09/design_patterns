// model different board games
// all the board games have certain things as common e.g. all have several players and 
//  those players take turns.

#include <iostream>
#include <string>

using namespace std;

class Game {
public:
	explicit Game(const int number_of_players) : number_of_players(number_of_players) {}

	void run() {
		start();
		while (!have_winner())
			take_turn();
		cout << "Player " << get_winner() << " wins.\n";
	}
	/*
		Describe the high-level algo as public "run()". run() is common to all the games.
		But the actual parts of the algo, the constituent parts are pure virtual
		and you use inhertance to define them. They are defined by each of the Game 
		we wish to implement.
	*/
protected:
	virtual void start() = 0;

	virtual bool have_winner() = 0;

	virtual void take_turn() = 0;

	virtual int get_winner() = 0;

	int number_of_players;
	int current_player{ 0 };
};


class Chess : public Game {
public:
	explicit Chess() : Game{2} {}
protected:
	void start() override{
		cout << "Starting a game of chess with " << number_of_players << " players.\n";
	}

	bool have_winner() override{
		return turns == max_turns;
	}

	void take_turn() override{
		cout << "Turn " << turns << " taken by player " << current_player << endl;
		turns++;
		current_player = (current_player + 1) % number_of_players;
	}

	int get_winner() override{
		return current_player;
	}
private:
	int turns{ 0 };
	int max_turns{ 10 };
};

int main() {
	Chess chess;
	chess.run();

	return 0;
}