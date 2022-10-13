#include <future>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

auto IsPrime( int value ) -> bool
{
	if( ( value != 2 ) && ( ( value & 1 ) != 1 ) ) {
		return false;
	}
	for( int i = 3; i < value / 2; i += 2 ) {
		if( value % i == 0 ) {
			return false;
		}
	}
	return true;
}

auto HowManyArePrime( int quantity ) -> int
{
	std::random_device            random_device;
	std::default_random_engine    random_engine( random_device() );
	std::uniform_int_distribution get_random_int_possible_prime{ 2, std::numeric_limits< int >::max() };
	int                           result = 0;
	for( int i = 0; i < quantity; i++ ) {
		if( IsPrime( get_random_int_possible_prime( random_engine ) ) ) {
			++result;
		}
	}
	return result;
}

auto main( int argc, char *argv[] ) -> int
{
	try {
		std::vector< std::string >        args( argv, argv + argc );
		int                               value     = std::stoi( args[1] );
		int                               n_threads = args.size() == 3 ? std::stoi( args[2] ) : 5;
		std::vector< std::future< int > > executions;

		executions.reserve( n_threads );

		for( int i = 0; i < n_threads; ++i ) {
			executions.push_back( std::async( std::launch::async, HowManyArePrime, value ) );
			std::cout << "Starting thread: " << i + 1 << std::endl;
		}

		for( int thread_number = 0; auto &exec: executions ) {
			std::cout << "Result for thread " << ++thread_number << ": " << exec.get() << std::endl;
		}

		std::cout << "Ending..." << std::endl;

	} catch( const std::exception &exception ) {
		std::cerr << "Unhandled exception: " << exception.what() << std::endl;
	}
}