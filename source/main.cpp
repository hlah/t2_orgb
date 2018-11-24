#include <iostream>

#include "eight_puzzle_problem.h"
#include "bfs.h"
#include "astar.h"

#include <cstdlib> 

unsigned int manhattan_distance( EightPuzzleProblem::State state ) {
	unsigned int h = 0;

	for( int i = 0; i < 9; i++ ) {

		int pos_x = i%3;
		int pos_y = i/3;

		int target_x = state[i]%3;
		int target_y = state[i]/3;

		h += std::abs(target_x - pos_x) + std::abs( target_y - pos_y );
	}

	return h;
}

int main(int argc, char** argv) {
	int option = 0;
	if( argc >= 2 ) {
		try {
			option = std::stoi(argv[1]);
		} catch( const std::invalid_argument& ia ) {
			option = 0;
		}
	}

		


	//auto problem = EightPuzzleProblem({2, 6, 8, 0, 5, 1, 3, 7, 4});
	//auto problem = EightPuzzleProblem({1, 0, 2, 3, 4, 5, 6, 7, 8});
	//auto problem = EightPuzzleProblem({1, 4, 2, 3, 5, 8, 6, 0, 7});
	auto problem = EightPuzzleProblem({1, 4, 2, 6, 3, 8, 5, 0, 7});
	//auto problem = EightPuzzleProblem({1, 2, 0, 6, 4, 8, 5, 6, 7});



	std::cout << "Problem:\n";
	problem.print_state( problem.initial_state() );

	/*
	for( auto node : problem.expand( problem.initial_state() ) ) {
		problem.print_action( node.action );
		std::cout << '\n';
		problem.print_state( node.state );
	}
	*/

	std::vector<EightPuzzleProblem::Action> solution;

	if( option == 0 ) {
		std::cout << "Doing BFS...\n";
		solution = bfs( problem );
	}
	else if( option == 1 ) {
		std::cout << "Doing A*...\n";
		solution = astar( problem, manhattan_distance );
	}

	std::cout << "Solution: ";
	for( auto action : solution ) {
		problem.print_action( action );
		std::cout << ' ';
	}
	std::cout << '\n';

	return 0;
}
