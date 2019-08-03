#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

class General {
	public:
		General() {
			army_size = std::rand() % 9 + 1;
		}

		bool betrayer;
		int army_size;
		std::vector<int> other;


		int ask_army() {
			if(betrayer) {
				return std::rand() % 9 + 1;
			}
			return army_size;
		}

		void print_other() {
			std::cout << "( ";
			for(auto g:other) {
				std::cout << g << " ";
			}
			std::cout << ")" << std::endl;
		}
};

int main() {
	std::srand(unsigned(std::time(0)));
	const int n = 4;
	const int m = 1;
	std::vector<General> generals;
	generals.resize(n);
	std::cout << "Random army size:" << std::endl;
	std::cout << "( ";
	for(auto g:generals) {
		std::cout << g.army_size << " ";
	}
	std::cout << ")" << std::endl;
	generals[2].betrayer = true;
// Step 1: ask army sizes
	std::cout << "Ask army size. Generals have knowledge:" << std::endl;
	std::cout << "Note: third general is betrayer" << std::endl;
	for (size_t i = 0; i < generals.size(); ++i) {
		generals[i].other.resize(generals.size());
		for(size_t j = 0; j < generals.size(); ++j) {
			generals[i].other[j] = (i == j) ? generals[j].army_size : generals[j].ask_army();
		}
		generals[i].print_other();
	}



	return 0;
}


