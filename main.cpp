#include <ctime>
#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <unordered_map>
#include <map>

std::mt19937_64 gen;

class General {
	public:
		General() {
			army_size = gen() % 9 + 1;
		}

		bool betrayer;
		int army_size;
		std::vector<int> other;
		std::vector<int> real;
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

		void calc() {
			real.resize(other.size());
			for(size_t i = 0; i < full.size(); ++i) { // iterate each army...
				//std::cout << "Check army #" << i + 1 << std::endl;
				auto q = get_quorum();
				bool checked = false;
				std::map<int, int> armies;
				for(size_t j = 0; j < full.size(); ++j) { // ...and info from each general
					auto value = full[j][i];
					auto v = armies.find(value);
					if(v == armies.end()) {
						armies.emplace(std::make_pair(value, 1));
					}
					else {
						v->second = ++v->second;
						if(v->second >= q) {
							std::cout << "Accept value " << v->first << " because the quorum limit (" << q << ")." << std::endl;
							real[i] = v->first;
							checked = true;
							break;
						}
					}
				}
				if(!checked) {
					real[i] = -1;
					std::cout << "Failed to pass quorum limit (" << q << ")." << std::endl;
				}
			}
		}

		size_t get_quorum() {
			size_t q = other.size() / 2;
			return other.size() % 2 ? q : q + 1;
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
				print_full(i);
			}
		}

		void print_full(size_t i) {
			std::cout << "( ";
			for(auto g:full[i]) {
				std::cout << g << " ";
			}
			std::cout << ") ";
		}

		void print_calc() {
			std::cout << "( ";
			for(auto &g:real) {
				std::cout << g << " ";
			}
			std::cout << ")";
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
// Step 4: Determine real values
	for(size_t i = 0; i < generals.size(); ++ i) {
		std::cout << "General " << i + 1 <<  " =======================" << std::endl;
		generals[i].calc();
		generals[i].print_calc();
		std::cout << std::endl;
	}

	return 0;
}


