#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

//CONSTANT GLOBAL VARIABLES-----------------------------------------------------------------------------
const string DEFAULT_NAME = "n/a";
const string DEFAULT_CREATURE_TYPE = "typeless";
const int TYPELIST_SIZE = 4;
const string TYPES_LIST[TYPELIST_SIZE] = { "macara", "ceffyl", "nuggle", "bahamut" };
const int DEFAULT_HEALTH_AND_STRENGTH = 100;
const int DEFAULT_SIZE = 5;
const int ARMY_SIZE = 10;

//CLASSES-----------------------------------------------------------------------------------------------
class Creature {
public:

	void setCreature(string newName, string newType, int newHealth, int newStrength);

	string getName() { return creatureName; }
	string getType() { return creatureType; }
	int  getHealth() { return creatureHealth; }
	int getStrength() { return creatureStrength; }
	int getDamage(string type, int strength);

	Creature() {

		setCreature(DEFAULT_NAME, DEFAULT_CREATURE_TYPE, DEFAULT_HEALTH_AND_STRENGTH, DEFAULT_HEALTH_AND_STRENGTH);

	}
	~Creature() {

		setCreature(DEFAULT_NAME, DEFAULT_CREATURE_TYPE, DEFAULT_HEALTH_AND_STRENGTH, DEFAULT_HEALTH_AND_STRENGTH);

	}
	Creature(Creature& otherCreature) {

		setCreature(otherCreature.creatureName, otherCreature.creatureType, otherCreature.creatureHealth, otherCreature.creatureStrength);

	}
	Creature(string newName, string newType) {

		setCreature(newName, newType, (rand() % 51) + 50, (rand() % 51) + 50);

	}
	Creature(string newName, string newType, int newHealth, int newStrength) {

		setCreature(newName, newType, newHealth, newStrength);

	}



private:

	string creatureName = DEFAULT_NAME;
	string creatureType = DEFAULT_CREATURE_TYPE;
	int creatureHealth = DEFAULT_HEALTH_AND_STRENGTH;
	int creatureStrength = DEFAULT_HEALTH_AND_STRENGTH;

};
class Army {
public:

	Army();
	~Army();
	Army(string newArmyName, string fileName);
	Army(Army& otherArmy);

	string getArmyCreatureName(int index) { return creatures[index].getName(); }
	string getArmyCreatureType(int index) { return creatures[index].getType(); }
	string getArmyName() { return armyName; }

	int getArmyCreatureHealth(int index) { return creatures[index].getHealth(); }
	int getArmyCreatureStrength(int index) { return creatures[index].getStrength(); }
	int getArmyCreatureDamage(int index) { return creatures[index].getDamage(creatures[index].getType(), creatures[index].getStrength()); }
	int getCreatureCount() { return creatureCount; }

	string toString(int index) {

		ostringstream text;
		text << getArmyCreatureName(index) << " the " << getArmyCreatureType(index);
		return text.str();

	}

private:

	string armyName = DEFAULT_NAME;
	int creatureCount = 0;
	Creature creatures[ARMY_SIZE];
	Creature* pCreatures[ARMY_SIZE] = { nullptr };

};
class Game{
public:

	Game(Army Army1, Army Army2);

private:

	string winnerNames[ARMY_SIZE];
	string winnerTeams[ARMY_SIZE];

};

//FUNCTION DECLERATIONS---------------------------------------------------------------------------------
string checkName(string name);
string checkType(string type);
int checkHealthAndStrength(int value);
void printTurn(Army army1, Army army2, int damage, int health, int index);
int checkGameHealth(int value);
void takeTurn(Army attacker, Army defender, int& health, int damage, int& index);

//ENUM--------------------------------------------------------------------------------------------------
enum {

	PLAY = 1,
	QUIT

};

//MAIN--------------------------------------------------------------------------------------------------
int main()
{
    
	srand(time(0));

	int input = 0;
	Army bluArmy("Blu Team", "bluNames.dat");
	Army redArmy("Red Team", "redNames.dat");


	cout << "Welcome to the Battle Game!\n";

	while (input != QUIT) {

		cout << "\nMenu\n"
			"1. Play\n"
			"2. Quit\n"
			"Input: ";

		cin >> input;
		switch (input) {
		case PLAY:
			Game(bluArmy, redArmy);
			break;
		case QUIT:
			cout << "Quitting Program...\n";
			break;
		default:
			cout << "invalid input, please input a valid option\n";
			break;


		}


	}


}

//FUNCTION DEFENITIONS----------------------------------------------------------------------------------
string checkName(string name) {

	int count = 0;
	for (char c : name) {
		if (std::isalpha(c)) {
			count++;
		}
	}
	if (count < 3 && name != DEFAULT_NAME) {

		cout << name << " has less than 3 alphabetic characters, setting to defalut..." << endl;
		return DEFAULT_NAME;

	}
	else {

		return name;

	}

}
string checkType(string type) {

	bool validType = false;

	for (int i = 0; i < TYPELIST_SIZE; i++) {

		if (type == TYPES_LIST[i] || type == DEFAULT_CREATURE_TYPE) {

			validType = true;

		}

	}

	if (validType == true) {

		return type;

	}
	else {

		cout << type << "is not 1 of 4 valid types (sans, table, yogurt, water), setting to default...\n";
		return DEFAULT_CREATURE_TYPE;

	}

}
int checkHealthAndStrength(int value) {

	if (value >= 50 && value <= 100) {

		return value;

	}
	else {

		cout << value << " is either less than 50 or greater than 100, setting to default...\n";
		return DEFAULT_HEALTH_AND_STRENGTH;

	}

}
void printTurn(Army army1, Army army2, int damage, int health, int index) {

   cout << left << setw(20) << army1.toString(index) << right << setw(5)
		<< damage << right << setw(5) << ""
		<< army1.getArmyName()
		 << "       "
	    << left << setw(20) << army2.toString(index) << right << setw(5)
		<< health << right << setw(5) << ""
		<< army2.getArmyName();

	cout << endl;

	
}
int checkGameHealth(int value) {

	if (value > 0) {

		return value;

	}
	else {

		return 0;

	}

}
void takeTurn(Army attacker, Army defender, int& health, int damage, int& numindex) {

	damage = attacker.getArmyCreatureDamage(numindex);

	if (attacker.getArmyCreatureType(numindex) == "ceffyl") {

		if ((rand() % 100) < 15) {
			damage = damage + 25;
			cout << "Ceffyl bonus damage activated!\n";
		}

	}
	else if (attacker.getArmyCreatureType(numindex) == "nuggle") {

		if ((rand() % 15) == 0) {
			damage = damage * 2;
			cout << "Double Nuggle magic mulitplier activated!\n";
		}

	}

	health = health - damage;
	health = checkGameHealth(health);
	printTurn(attacker, defender, damage, health, numindex);
	cout << attacker.getArmyCreatureName(numindex) << " attacked " << defender.getArmyCreatureName(numindex) << " and did " << damage << " damage!\n"
		<< defender.getArmyCreatureName(numindex) << " has " << health << " HP left!\n\n";
	
	if (attacker.getArmyCreatureType(numindex) == "bahamut") {

		health = health - damage;
		health = checkGameHealth(health);
		printTurn(attacker, defender, damage, health, numindex);
		damage = attacker.getArmyCreatureDamage(numindex);
		cout << attacker.getArmyCreatureName(numindex) << " was too fast and attacked " << defender.getArmyCreatureName(numindex) << " again, and did " << damage << " damage!\n"
			<< defender.getArmyCreatureName(numindex) << " has " << health << " HP left!\n\n";

	}

}

//CLASS FUNCTIONS---------------------------------------------------------------------------------------
void Creature::setCreature(string newName, string newType, int newHealth, int newStrength) {

	creatureName = checkName(newName);
	creatureType = checkType(newType);
	creatureStrength = checkHealthAndStrength(newStrength);
	creatureHealth = checkHealthAndStrength(newHealth);

}
int Creature::getDamage(string type, int strength) {

	return rand() % strength + 1;

}
	
//ARMY CONSTRUCTORS-------------------------------------------------------------------------------------
Army::Army() {

	cout << "Default constructor is running...\n";

	armyName = DEFAULT_NAME;
	creatureCount = ARMY_SIZE;

	for (int i = 0; i < ARMY_SIZE; i++) {

		creatures[i].setCreature(DEFAULT_NAME, DEFAULT_CREATURE_TYPE, DEFAULT_HEALTH_AND_STRENGTH, DEFAULT_HEALTH_AND_STRENGTH);
		pCreatures[i] = &creatures[i];

	}


}
Army::~Army() {

	armyName = DEFAULT_NAME;

}
Army::Army(string newArmyName, string fileName) {

	string nameInput;

	ifstream infile;
	infile.open(fileName);
	if (!infile) {
		cout << "Cannot open file" << endl;
		exit(EXIT_FAILURE);
	}

	armyName = checkName(newArmyName);


	for (int i = 0; i < ARMY_SIZE; i++) {

		nameInput = "";
		infile >> nameInput;

		creatures[creatureCount].setCreature(checkName(nameInput), TYPES_LIST[rand() % 4], (rand() % 51) + 50, (rand() % 51) + 50);

		if (nameInput != "") {

			creatureCount++;

		}

	}

}
Army::Army(Army& otherArmy) {

	armyName = otherArmy.armyName;

	for (int i = 0; i < ARMY_SIZE; i++) {

		creatures[i] = otherArmy.creatures[i];

	}

}

//GAME CONSTRUCTOR--------------------------------------------------------------------------------------
Game::Game(Army Army1, Army Army2) {

	cout << "\n";
	
	int army1Health = 0;
	int army2Health = 0;
	int AttackerDamage = 0;
	bool Army1Turn = true;
	
	int whosFirst = rand() % 2;

	if (whosFirst == 1) {

		Army1Turn = false;

	} 

	for (int i = 0; i < ARMY_SIZE; i++) {

		int defender1Health = Army1.getArmyCreatureHealth(0);
		int defender2Health = Army2.getArmyCreatureHealth(0);

		cout << "Round " << i + 1 << "\n\nAttacker           Damage     Army           Defender           Health     Army\n";

		while ((defender1Health > 0) && (defender2Health > 0)) {

			if (Army1Turn == true) {

				takeTurn(Army1, Army2, defender2Health, AttackerDamage, i);
				Army1Turn = false;

			}
			else if (Army1Turn == false) {

				takeTurn(Army2, Army1, defender1Health, AttackerDamage, i);
				Army1Turn = true;
			}

		}

		army1Health = army1Health + defender1Health;
		army2Health = army2Health + defender2Health;

		if (defender1Health == 0) {

			cout << Army2.getArmyCreatureName(i) << " from " << Army2.getArmyName() << " has won the round!\n------------------------------------------------------------------------------------\n";

		}
		else {

			cout << Army1.getArmyCreatureName(i) << Army1.getArmyName() << "has won the round!\n------------------------------------------------------------------------------------\n";

		}

	}
	
	cout << "Winner: \n";

	if (army1Health > army2Health) {

		cout << Army1.getArmyName() << " has won with " << army1Health << "!\n"
			<< Army2.getArmyName() << " lost with " << army2Health << "!\n";

	}
	else {

		cout << Army2.getArmyName() << " has won with " << army2Health << "!\n"
			<< Army1.getArmyName() << " lost with " << army1Health << "!\n";


	}



}