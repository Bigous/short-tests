#include <algorithm>
#include <format>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string_view>
#include <vector>
#include <sstream>
// #include <fmt/format.h>
#include <fmt/ranges.h>

constexpr auto ToString( const std::vector< std::string_view > &vec ) -> std::string
{
	std::string ret;
	ret.reserve( 3                        // First and Last bracket and the final \0
	             + ( vec.size() - 1 ) * 2 // Comma and space between items
	             + std::reduce(           // The sum of the sizes of the strings inside the vector
										 vec.cbegin(), vec.cend(), static_cast< std::size_t >( 0 ),
										 []( const auto &acc, const auto &item ) -> auto{ return acc + item.size(); } ) );
	ret.push_back( '[' );
	for( std::size_t i = 0; const auto &item: vec ) {
		ret.append( item );
		if( ++i < vec.size() ) {
			ret.append( ", " );
		}
	}
	ret.push_back( ']' );
	return ret;
}

auto ToString(const auto &iterable) -> std::string
{
  std::stringstream ss_ret;
  ss_ret << '[';
	std::ranges::copy(iterable, std::ostream_iterator<std::size_t>(ss_ret, ", "));
  ss_ret << ']';
  return ss_ret.str();
}

void PrintChunk()
{

	auto treats = std::vector< std::string_view >{ "toy", "chicken", "catnip", "dog" };

	std::cout << "Chunk\n\tInitial: " << ToString( treats ) << '\n';

  auto chunked = treats | std::views::chunk(2);

  //std::cout << "\tFinal: " << fmt::format("{}", chunked) << std::endl;
  //fmt::print("{}\n", chunked);
	std::cout << "\tFinal: " << ToString(chunked);
}

auto main() -> int
{
	try {
		// 1 - Chunk
		PrintChunk();
	} catch( const std::exception &exception ) {
		std::cerr << "Unhandled exception: " << exception.what() << std::endl;
	}
	return 0;
}