#include "Random.h"
#include<iostream>
#include<array>
#include<string_view>
#include<limits>

void shop();

void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

class Player {
	std::string m_name{};
	int m_gold{};

   public:

	   explicit Player(std::string_view name) :
		   m_name{ name },
		   m_gold{ Random::get(1,200) }
	   {}


	   int gold() const { return m_gold; }

};

namespace Potion {
	enum Type {
		healing,
		mana,
		speed,
		invisibility,
		count,
	};
	 std::array<int, count> costs{20, 23, 12, 50};

	 std::array<int, count> inventory{ 0,0,0,0 };

	constexpr std::array<std::string_view,count> names{ "healing", "mana", "speed", "invisibility" };
	static_assert(costs.size() == count);
	static_assert(names.size() == count);
}

void shop() {
	int n = Potion::Type::count;

	std::cout << "Here is our selection for today : \n";
	for (size_t i = 0; i < n; i++) {
		std::cout <<i << ") " << Potion::names[i] << " costs " << Potion::costs[i] << '\n';
	}

}


int main() {
	std::cout << "Welcome to Roscoe's potion emporium! \n";
	std::cout << "Enter you name : ";
	std::string name{};
	std::getline(std::cin, name);
	Player player(name);
	int totalGold{ player.gold() };
	std::cout << "Hello " << name << "! you have " << totalGold << " gold " << '\n';

	while (true) {
		shop();
		std::cout << totalGold << " gold is left. \n";
		std::cout << "Enter the number of that potion you'd like to buy, or 'q' to quit: \n";
		std::string chooseIdx{};

	std::getline(std::cin, chooseIdx);

		if (chooseIdx.size() > 1) {
			std::cout << "Invalid input, please enter a number or 'q' to quit.\n";
			continue;
		}
		char choosenIdx = chooseIdx[0] ;

		if (choosenIdx == 'q') {
			std::cout << "Your inventory contains : \n";
			for (int i = 0; i < Potion::Type::count; i++) {
				std::cout << Potion::inventory[i] << "x " << "of " << Potion::names[i] << '\n';
			}
			break;

		}
		   
			 if (choosenIdx - '0' >= Potion::Type::count or choosenIdx - '0' < 0) {
				std::cout << " Please enter a valid choice of Potion.\n";
				
				continue;
			}

			 if(!std::cin) {
				std::cin.clear();
				ignoreLine();
				std::cout << "Input failure, please enter again.\n";
				continue;
				
			}
			// when all the conditions are satisfied
			else {
				if (totalGold - Potion::costs[choosenIdx - '0'] < 0) {
					std::cout << "You cannot afford that, Choose a cheaper alternative. \n";
				}
				else {
					std::cout << "You have purchased a potion of " << Potion::names[choosenIdx - '0'] << '\n';
					Potion::inventory[choosenIdx - '0']++;
					totalGold -= Potion::costs[choosenIdx - '0'];
					std::cout << "Now you have " << totalGold << " Gold \n";
				}
			}
			
		
   }
	std::cout << "Thanks for purchasing...\n";
	
}