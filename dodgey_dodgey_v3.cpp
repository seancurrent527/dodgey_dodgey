//Implementation for C++ dodgey dodgey

#include <iostream>
#include <ctime>

using namespace std;

struct obstacle {

	int pos[2];
	int dir;
	int axis;
    int max = 21;
    
    obstacle() {
        pos[0] = 0;
        pos[1] = 0;
        dir = 0;
        axis = 0;
    }
    
	void incr() {
		pos[axis] += dir;
        if (pos[0] < 0 || pos[1] < 0 || pos[0] > max || pos[1] > max) {
            pos[0] = 0;
            pos[1] = 0;
            dir = 0;
            axis = 0;
        }
	}

	char printme() {
		if (dir == 0) {
            return ' ';
        }
        else if (axis == 0) {
			if (dir == 1) {
				return '>';
			}
			else {
				return '<';
			}
		}
		else {
			if (dir == 1) {
				return 'v';
			}
			else {
				return '^';
			}
		}
	}
};

struct allObs {

	obstacle list[200];
	int counter;

    allObs() {
        int i;
        obstacle _new;
        counter = 0;
        for (i = 0; i < 200; i++) {
            list[i] = _new;
        }
    }
        

	void incrAll() {
		int i;
        obstacle * ptr;

		for (i = 0; i < 200; i++) {
            ptr = &list[i];
            if (ptr) {
				list[i].incr();
			}
			else {
				continue;
			}
		}
	}

	void newObs(int size) {
		int max = size + 1;
		int ax = rand() % 2;
		int d = rand() % 2;
		int x;
		int y;
		obstacle _new;

		if (d == 0) {
			d = -1;
		}

		if (ax == 0) {
			y = rand() % size + 1;
			if (d == 1) {
				x = 0;
			}
			else {
				x = max;
			}
		}
		else {
			x = rand() % size + 1;
			if (d == 1) {
				y = 0;
			}
			else {
				y = max;
			}
		}

		_new.pos[0] = x;
		_new.pos[1] = y;
		_new.dir = d;
		_new.axis = ax;

		list[counter] = _new;
		counter++;

		if (counter >= 200) {
			counter = 0;
		}
	}
};

struct player {

	int pos[2];
	int max;
	char rep;
    
    player( ) {
        rep = 'P';
    }

	void setRep(char n) {
		rep = n;
	}

	char printme() {
		return rep;
	}

	void movePlayer() {
		char inp;
		cin >> inp;
		if (inp == 'w' && pos[1] > 1) {
			pos[1]--;
		}
		else if (inp == 's' && pos[1] < max) {
			pos[1]++;
		}
		else if (inp == 'a' && pos[0] > 1) {    //This don't work
			pos[0]--;
		}
		else if (inp == 'd' && pos[0] < max) {  //This don't work
			pos[0]++;
		}
		else {
			cout << "That is not a valid movement." << endl;
			movePlayer();
		}
	}

	bool isAlive(struct allObs enemies) {
		int i;
        obstacle * ptr;
        obstacle obs;

		for (i = 0; i < 200; i++) {
            ptr=&enemies.list[i];
            if (ptr) {
				obs = enemies.list[i];
				if (pos[0] == obs.pos[0] && pos[1] == obs.pos[1]) {
					return false;
				}
			}
		}
		return true;
	}
};

class PlayerMap {

	player you;
	allObs them;
	int size;
    int border = 22;
	char grid[22][22];

	void resetMap() {
		int i;
		int j;
		for (i = 0; i < border; i++) {
			for (j = 0; j < border; j++) {
				grid[j][i] = ' ';
			}
		}
	}

	void mapPlayer() {
		grid[you.pos[1]][you.pos[0]] = you.printme();
	}

	void mapObstacles() {    //ERROR HERE //FIXED
		int i;
        obstacle * ptr;
        obstacle enemy;
        char spot;

		for (i = 0; i < 200; i++) {
            ptr=&them.list[i];
            if (ptr) {
				enemy = them.list[i];
				spot = grid[enemy.pos[1]][enemy.pos[0]];
				if (spot == you.printme()) {
					grid[enemy.pos[1]][enemy.pos[0]] = 'O';
				}
				else if (spot == ' ') {
					grid[enemy.pos[1]][enemy.pos[0]] = enemy.printme();
				}
				else if (spot == enemy.printme()) {
					grid[enemy.pos[1]][enemy.pos[0]] = enemy.printme();
				}
                else if (spot == 'O') {
                    continue;
                }
				else {
					grid[enemy.pos[1]][enemy.pos[0]] = 'X';
				}
			}
		}
	}

	void printline() {
		int i;
        cout << "  +";
        for (i = 0; i < size; i++) {
			cout << "-+";
		}
        cout << '\n';
	}

public:
    int turns;

    PlayerMap() {
        size = 10;
        turns = 0;
        resetMap();
    }

	void set_size(int n) {
		size = n;
	}

	void set_player(player p) {
		you = p;
	}

	int get_turns() {
		return turns;
	}

	bool playRound() {   //ERROR HERE
		int i;
		you.movePlayer();
		them.incrAll();
		for (i = 0; i < (turns / 20 + 1); i++) {
			them.newObs(size);
		}
		return you.isAlive(them);
	}

	void printme() {
		int i;
		int j;
        resetMap();
		mapPlayer();
		mapObstacles();
        cout << "Turn: " << turns << '\n';
        cout << ' ';
        for (j = 0; j < size + 1; j++) {
			cout << grid[0][j] << ' ';
		}
		cout << grid[0][size + 1] << '\n';
		printline();
        for (i = 1; i < size + 1; i++) {
            cout << ' ';
            for (j = 0; j < size + 1; j++) {
				cout << grid[i][j] << '|';
			}
			cout << grid[i][size + 1] << '\n';
			printline();
		}
        cout << ' ';
        for (j = 0; j < size + 1; j++) {
			cout << grid[size + 1][j] << ' ';
		}
		cout << grid[size + 1][size + 1] << endl;
	}
};

int main() {
    
    srand(time(NULL));
    
    cout << "Welcome to Dodgey-Dodgey!" << '\n';
    cout << "Use WASD to move. Input one character, and then press enter." << '\n';
    cout << "Avoid the arrows to win!" << '\n' << endl;
    
    while (true) {
        cout << "Enter size of play field: (2 < N < 20, or enter 0 to exit) ";
        
        int N;
        char inp;
        char cont;
        PlayerMap MAP;
        player YOU;
        cin >> N;
        
        MAP.set_size(N);
        cout << endl << endl;

        YOU.max = N;
        YOU.pos[0] = (N + 2) / 2 - 1;
        YOU.pos[1] = (N + 2) / 2 - 1;

        MAP.set_player(YOU);

        cout << "Let the game begin!" << '\n' << endl;

        MAP.printme();
        while (MAP.playRound()) {
            MAP.turns++;
            MAP.printme();
        }
        
        MAP.printme();

        cout << "Oh no! You got hit!" << '\n';
        cout << "You lasted for " << MAP.get_turns() << " turns!" << '\n' << endl;

        cout << "Enter any input to continue. ";
        cin >> inp;
        cout << "Play again? (y|n) " << endl;
        cin >> cont;
        if (cont == 'n') {
            break;
        }
    }

    cout << "Goodbye!" << endl;
	return 0;
}


















