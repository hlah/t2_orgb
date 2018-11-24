#ifndef  __ASTAR__H__
#define  __ASTAR__H__

#include <queue>
#include <map>
#include <functional>

#include <iostream>

template <class P>
std::vector<typename P::Action> astar( const P& problem, std::function<unsigned int(typename P::State)> heuristic ) {
	std::vector<typename P::Action> solution{};

	typedef std::tuple<unsigned int, typename P::Node> PState;
	typedef std::tuple<typename P::Action, unsigned int> PAction;

	// fila de prioridades
	auto compare_pstate = [] (PState a, PState b) -> bool { return std::get<0>(a) > std::get<0>(b); };
	std::priority_queue<PState, std::vector<PState>, std::function<bool(PState, PState)>> open_list{compare_pstate};


	std::map<typename P::State, PAction> closed_list;

	open_list.push( {0, {problem.initial_state(), P::Action::UP, 0}} );

	bool found = false;

	while( !open_list.empty() && !found ) {

		auto current_node = std::get<1>(open_list.top());

		open_list.pop();

		for( auto new_node : problem.expand( current_node ) ) {

			auto node_it = closed_list.find( new_node.state );
			if( node_it == closed_list.end() || std::get<1>(node_it->second) > new_node.cost ) {

				open_list.push( { new_node.cost + heuristic(new_node.state), new_node} );
				closed_list[new_node.state] = {new_node.action, new_node.cost};

				if( problem.is_goal( new_node.state ) ) {

					// reconstroi solução
					auto find_state = new_node.state;
					while( find_state != problem.initial_state() ) {
						solution.insert( solution.begin(), std::get<0>(closed_list[find_state]) );
						find_state = problem.revert_action( find_state, std::get<0>(closed_list[find_state]) );
					}
					
					found = true;
					break;
				}
			}
		}
	}

	return solution;
}

#endif //  __ASTAR__H__

