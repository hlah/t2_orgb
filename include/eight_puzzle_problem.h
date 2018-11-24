#ifndef __EIGHT_PUZZLE_PROBLEM_H__
#define __EIGHT_PUZZLE_PROBLEM_H__

#include <vector>
#include <array>

class EightPuzzleProblem {
	public:

		typedef std::array< uint8_t, 9 > State;

		enum class Action {
			UP,
			DOWN,
			LEFT,
			RIGHT
		};

		struct Node {
			State state;
			Action action;
			unsigned int cost;
		};

		EightPuzzleProblem( const State& initial_state );

		State initial_state() const;

		bool is_goal(const State& state) const;

		std::vector<Node> expand(const Node& node) const;

		State revert_action( const State& state, const Action& action ) const;

		void print_state( State state ) const;

		void print_action( Action action ) const;


	private:

		const State _initial_state;


};

#endif // __EIGHT_PUZZLE_PROBLEM_H__
