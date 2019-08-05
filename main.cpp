#include <ctime>
#include <iostream>
#include <vector>
#include <random>

std::mt19937_64 gen;

class General {
	public:
		General() {
			army_size = gen() % 9 + 1;
		}

		bool betrayer;
		int army_size;
		std::vector<int> other;
		std::vector<std::vector<int> > full;

		int ask_army() {
			if(betrayer) {
				return gen() % 9 + 1;
			}
			return army_size;
		}

		std::vector<int> ask_vector() {
			if(betrayer) {
				std::vector<int> fake_other;
				for(size_t i = 0; i < other.size(); ++i) {
					fake_other.push_back( gen() % 9 + 1);
				}
				return fake_other;
			}
			return other;
		}

		void print_other() {
			std::cout << "( ";
			for(auto g:other) {
				std::cout << g << " ";
			}
			std::cout << ")";
		}

		void print_full() {
			for(size_t i = 0; i < full.size(); ++i) {
				std::cout << "( ";
				for(size_t j = 0; j < full[i].size(); ++j) {
					std::cout << full[i][j] << " ";
				}
				std::cout << ") ";
			}
		}

		void print_full(size_t i) {
			std::cout << "( ";
			for(auto g:full[i]) {
				std::cout << g << " ";
			}
			std::cout << ") ";
		}
};

int main() {
	gen.seed(time(nullptr));
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
// Step 2: form vector
	std::cout << "Ask army size. Generals have knowledge:" << std::endl;
	std::cout << "Note: third general is betrayer" << std::endl;
	for (size_t i = 0; i < generals.size(); ++i) {
		for(size_t j = 0; j < generals.size(); ++j) {
			generals[i].other.push_back( (i == j) ? generals[j].army_size : generals[j].ask_army() );
		}
		std::cout << i + 1 << ": ";
		generals[i].print_other();
		std::cout << std::endl;
	}
// Step 3: ask vectors
	std::cout << "Ask army vectors." << std::endl;
	for(size_t i = 0; i < generals.size(); ++i) { // each general ...
		for(size_t j = 0; j < generals.size(); ++j) { // ...ask another
			generals[i].full.push_back( (i == j) ? generals[j].other : generals[j].ask_vector() );
		}
	}

	// Print output for this step
	std::cout << "  g1,         g2,         g3,         g4" << std::endl;
	for(size_t i = 0; i < generals.size(); ++i) {
		for(size_t j = 0; j < generals.size(); ++j) {
			generals[j].print_full(i);
		}
		std::cout << std::endl;
	}

	return 0;
}


