#include <iostream>

#include "eight_puzzle_problem.h"
#include "bfs.h"

int main() {

	//auto problem = EightPuzzleProblem({2, 6, 8, 0, 5, 1, 3, 7, 4});
	//auto problem = EightPuzzleProblem({1, 0, 2, 3, 4, 5, 6, 7, 8});
	//auto problem = EightPuzzleProblem({1, 4, 2, 3, 5, 8, 6, 0, 7});
	auto problem = EightPuzzleProblem({1, 4, 2, 6, 3, 8, 5, 0, 7});


	std::cout << "Problem:\n";
	problem.print_state( problem.initial_state() );

	/*
	for( auto node : problem.expand( problem.initial_state() ) ) {
		problem.print_action( node.action );
		std::cout << '\n';
		problem.print_state( node.state );
	}
	*/

	auto solution = bfs( problem );
	std::cout << "Solution: ";
	for( auto action : solution ) {
		problem.print_action( action );
		std::cout << ' ';
	}
	std::cout << '\n';

	return 0;
}
