#include <iostream>

#include "eight_puzzle_problem.h"

void print_state(const EightPuzzleProblem::State& state) {
	for( int i = 0; i < 3; i++ ) {
		for( int j = 0; j < 3; j++ ) {
			std::cout << (int)state[3*i+j] << ' ';
		}
		std::cout << '\n';
	}
}

void print_action(const EightPuzzleProblem::Action& action) {
	switch(action) {
		case EightPuzzleProblem::Action::UP:
			std::cout << "UP";
			break;
		case EightPuzzleProblem::Action::DOWN:
			std::cout << "DOWN";
			break;
		case EightPuzzleProblem::Action::LEFT:
			std::cout << "LEFT";
			break;
		case EightPuzzleProblem::Action::RIGHT:
			std::cout << "RIGHT";
			break;
	}
}

int main() {

	std::cout << "Hello World!\n";

	auto problem = EightPuzzleProblem({2, 6, 8, 0, 5, 1, 3, 7, 4});

	auto nodes = problem.expand( problem.initial_state() );

	for( auto node : nodes ) {
		print_action( node.action );
		std::cout << '\n';
		print_state( node.state );
		std::cout << "cost: " << (int) node.cost << '\n';
	}

	return 0;
}
