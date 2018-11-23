#include "eight_puzzle_problem.h"

#include <utility>
#include <iostream>

EightPuzzleProblem::EightPuzzleProblem( const State& initial_state ) : _initial_state{initial_state} { }

EightPuzzleProblem::State EightPuzzleProblem::initial_state() const {
	return _initial_state;
}

bool EightPuzzleProblem::is_goal(const State& state) const {
	return state == State{0, 1, 2, 3, 4, 5, 6, 7, 8};
}

std::vector<EightPuzzleProblem::Node> EightPuzzleProblem::expand(const State& state) const {
	std::vector<Node> neighboors;

	int zeropos = 0;
	while( zeropos < 8 && state[zeropos] != 0 )
		zeropos++;

	int posx = zeropos%3;
	int posy = zeropos/3;

	if( posx + 1 < 3 ) {
		State state_copy{state};
		std::swap(state_copy[zeropos], state_copy[posy*3+posx+1]);
		neighboors.push_back({state_copy, Action::RIGHT, 1});
	}

	if( posx - 1 >= 0 ) {
		State state_copy{state};
		std::swap(state_copy[zeropos], state_copy[posy*3+posx-1]);
		neighboors.push_back({state_copy, Action::LEFT, 1});
	}

	if( posy + 1 < 3 ) {
		State state_copy{state};
		std::swap(state_copy[zeropos], state_copy[(posy+1)*3+posx]);
		neighboors.push_back({state_copy, Action::DOWN, 1});
	}

	if( posy - 1 >= 0 ) {
		State state_copy{state};
		std::swap(state_copy[zeropos], state_copy[(posy-1)*3+posx]);
		neighboors.push_back({state_copy, Action::UP, 1});
	}

	return neighboors;
}

EightPuzzleProblem::State EightPuzzleProblem::revert_action( const State& state, const Action& action ) const {
	State reverted_state{state};

	int zeropos = 0;
	while( zeropos < 8 && state[zeropos] != 0 )
		zeropos++;

	int posx = zeropos%3;
	int posy = zeropos/3;

	if( action == Action::LEFT && posx < 2 ) {
		std::swap(reverted_state[zeropos], reverted_state[posy*3+posx+1]);
	}

	else if( action == Action::RIGHT && posx > 0 ) {
		std::swap(reverted_state[zeropos], reverted_state[posy*3+posx-1]);
	}

	else if( action == Action::DOWN && posy > 0 ) {
		std::swap(reverted_state[zeropos], reverted_state[(posy-1)*3+posx]);
	}

	else if( action == Action::UP && posy < 2 ) {
		std::swap(reverted_state[zeropos], reverted_state[(posy+1)*3+posx]);
	}
	
	return reverted_state;
}

void EightPuzzleProblem::print_state( State state ) const {
	for( int i = 0; i < 3; i++ ) {
		for( int j = 0; j < 3; j++ ) {
			std::cout << (int)state[3*i+j] << ' ';
		}
		std::cout << '\n';
	}
}

void EightPuzzleProblem::print_action( Action action ) const {
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
