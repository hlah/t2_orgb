#ifndef __IDASTAR_H__
#define __IDASTAR_H__

#include <limits>
#include <set>
#include <stack>

#include <iostream>

template <class P>
std::tuple<bool, unsigned int, std::vector<typename P::Action>> idastar_aux( 
		const P& problem, 
		std::function<unsigned int(typename P::State)> heuristic,
		const typename P::Node& node,
		std::set<typename P::State>& path_states, 
		unsigned int bound ) 
{
	std::vector<typename P::Action> solution{};
	unsigned int min = std::numeric_limits<unsigned int>::max();
	bool found = false;

	auto f = node.cost + heuristic(node.state);

	if( f > bound )
		min = f;
	else if( problem.is_goal( node.state ) ) {
		solution.push_back( node.action );
		found = true;
	} else {

		for( auto new_node : problem.expand( node ) ) {

			if( path_states.find( new_node.state ) == path_states.end() ) {
				
				path_states.insert( new_node.state );

				auto result = idastar_aux( problem, heuristic, new_node, path_states, bound );
				if( std::get<0>(result) ) {
					found = true;
					solution = std::get<2>(result);
					solution.insert( solution.begin(), node.action );
				} else {
					min = std::min( min, std::get<1>(result) );
				}

				path_states.erase( new_node.state );

			}

		}

	}



	return { found, min, solution };
}

template <class P>
std::vector<typename P::Action> idastar( const P& problem, std::function<unsigned int(typename P::State)> heuristic ) {
	std::vector<typename P::Action> solution{};


	bool searching = true;
	unsigned int bound = heuristic( problem.initial_state() );

	while( searching ) {

		std::set<typename P::State> path_states;

		auto result = idastar_aux<P>( problem, heuristic, {problem.initial_state(), P::Action::UP, 0}, path_states, bound );
		if( std::get<0>(result) ) {
			searching = false;
			solution = std::get<2>(result);
			solution.erase( solution.begin() );
		} else if(std::get<1>(result) == std::numeric_limits<unsigned int>::max() ){
			searching = false;
		} else {
			bound = std::get<1>(result);
		}
	}

	return solution;
}

#endif // __IDASTAR_H__
