#include <cctype>      // std::isdigit
#include <cstdlib>     // std::atoi
#include <format>      // std::format
#include <functional>  // std::function
#include <future>      // std::async, std::future, std::launch
#include <iostream>    // std::cout, std::cerr, std::endl
#include <limits>      // std::numeric_limits
#include <random>      // std::random_device, std::default_random_engine, std::uniform_int_distribution
#include <string_view> // std::string_view
#include <vector>      // std::vector

auto IsPrime( int value ) -> bool
{
	if( value < 2 || ( value != 2 ) && ( ( value & 1 ) != 1 ) ) {
		return false;
	}
	for( int i = 3; i < value / 2; i += 2 ) {
		if( value % i == 0 ) {
			return false;
		}
	}
	return true;
}

auto HowManyArePrimeRandom( int quantity ) -> int
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

auto HowManyArePrimeFixedSequence( int quantity ) -> int
{
	std::default_random_engine    random_engine( 42 );
	std::uniform_int_distribution get_random_int_possible_prime{ 2, std::numeric_limits< int >::max() };
	int                           result = 0;
	for( int i = 0; i < quantity; i++ ) {
		if( IsPrime( get_random_int_possible_prime( random_engine ) ) ) {
			++result;
		}
	}
	return result;
}

auto GetIntFromParameter( const char *parameter ) -> int
{
	const char *p = parameter;
	while( ( *p ) != '\0' ) {
		if( std::isdigit( *p ) == 0 ) {
			throw std::exception( std::format( "Parameter [{}] is a valid not positive number.", parameter ).c_str() );
		}
		++p;
	}
	return std::atoi( parameter );
}

constexpr const char *kUsage = R"(Usage:
    {0} [<number of iterations on each thread> [<number of threads>:5 [--fixed]]]

  Options:
    number of iterations on each thread: is the number of elements each thead will pull from the random|fixed list and calculate if it's prime.
    number of threads: is the number of threads that will be started. Defauls to 5 if ommited.
    --fixed: Defines if the random generator will be defined with a fixed seed or a random one.

  Examples:
    {0} 100 10 --fixed
      Runs 10 threads with 100 number pulled each from the same fixed list for each thread (all threads must return the same number of primes).
            
    {0} 100 10
      Runs 10 threads with 100 number pulled each from the a random list for each thread (all threads will return a different number of primes).
            
    {0} 100
      Runs 5 threads with 100 number pulled each from the a random list for each thread (all threads will return a different number of primes).
            
    {0} std::endl 
      Shows this usage.
)";

auto main( int argc, char *argv[] ) -> int
{
	try {
		// std::vector< std::string_view >   args( argv, argv + argc );
		if( argc < 2 || argc > 4 ) {
			std::cout << std::format( kUsage, argv[0] ) << std::endl;
			return ( argc < 2 ) ? 0 : 1;
		}
		int                               value     = GetIntFromParameter( argv[1] );
		int                               n_threads = argc >= 3 ? GetIntFromParameter( argv[2] ) : 5;
		std::vector< std::future< int > > executions;
		std::function< int( int ) >       fn_thread = HowManyArePrimeRandom;

		if( ( argc == 4 ) ) {
			if( std::strcmp( argv[3], "--fixed" ) == 0 ) {
				fn_thread = HowManyArePrimeFixedSequence;
			} else {
				throw std::exception(
						std::format( "The 3rd parameter [{}] must be \"--fixed\" or cannot be passed.", argv[3] ).c_str() );
			}
		}

		executions.reserve( n_threads );

		for( int i = 0; i < n_threads; ++i ) {
			executions.push_back( std::async( std::launch::async, fn_thread, value ) );
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