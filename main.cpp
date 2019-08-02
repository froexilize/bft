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
		int ask_army() {
			if(betrayer) {
				return std::rand() % 9 + 1;
			}
			return army_size;
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
	
	return 0;
}
