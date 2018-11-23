#include "eight_puzzle_problem.h"

#include <utility>

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
		neighboors.push_back({state_copy, Action::LEFT, 1});
	}

	if( posx - 1 >= 0 ) {
		State state_copy{state};
		std::swap(state_copy[zeropos], state_copy[posy*3+posx-1]);
		neighboors.push_back({state_copy, Action::RIGHT, 1});
	}

	if( posy + 1 < 3 ) {
		State state_copy{state};
		std::swap(state_copy[zeropos], state_copy[(posy+1)*3+posx]);
		neighboors.push_back({state_copy, Action::DOWN, 1});
	}

	if( posy - 1 <= 0 ) {
		State state_copy{state};
		std::swap(state_copy[zeropos], state_copy[(posy-1)*3+posx]);
		neighboors.push_back({state_copy, Action::UP, 1});
	}

	return neighboors;
}
