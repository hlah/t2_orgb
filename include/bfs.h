#ifndef  __BFS__H__
#define  __BFS__H__

#include <queue>
#include <map>

#include <iostream>

template <class P>
std::vector<typename P::Action> bfs( const P& problem ) {
	std::vector<typename P::Action> solution{};

	// fila
	std::queue<typename P::State> open_list;

	std::map<typename P::State, typename P::Action> closed_list;

	open_list.push( problem.initial_state() );

	bool found = false;

	while( !open_list.empty() && !found ) {

		auto current_state = open_list.front();

		open_list.pop();

		for( auto new_node : problem.expand( current_state ) ) {

			if( closed_list.find( new_node.state ) == closed_list.end() ) {

				open_list.push( new_node.state );
				closed_list[new_node.state] = new_node.action;

				if( problem.is_goal( new_node.state ) ) {

					// reconstroi solução
					auto find_state = new_node.state;
					while( find_state != problem.initial_state() ) {
						solution.insert( solution.begin(), closed_list[find_state] );
						find_state = problem.revert_action( find_state, closed_list[find_state] );
					}
					
					found = true;
					break;
				}
			}
		}
	}

	return solution;
}

#endif //  __BFS__H__

