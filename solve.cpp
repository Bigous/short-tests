#include <iostream>
#include <vector>

std::vector< int > algarismos{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
std::vector< int > algarismos_sem_zero{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

// A idéia é resolver as letras e cada variável representa uma letra, então não há motivos para não usar a própria letra
// como identificador.
// NOLINTNEXTLINE(readability-identifier-length, readability-identifier-naming)
int c, r, o, s, a, d, n, g, e;

#define CROSS (( c * 10000 ) + ( r * 1000 ) + ( o * 100 ) + ( s * 10 ) + s)
#define ROADS (( r * 10000 ) + ( o * 1000 ) + ( a * 100 ) + ( d * 10 ) + s)
#define DANGER (( d * 100000 ) + ( a * 10000 ) + ( n * 1000 ) + ( g * 100 ) + ( e * 10 ) + r)

auto print_solution = []() -> void {
	std::cout << "   CROSS  :   " << c << r << o << s << s << std::endl;
	std::cout << "+  ROADS  :+  " << r << o << a << d << s << std::endl;
	std::cout << " -------  : -------" << std::endl;
	std::cout << "  DANGER  :  " << d << a << n << g << e << r << std::endl << std::endl;
};

// Resolução por "força bruta" -> 1 for para cada letra diferente.
// NOLINTNEXTLINE(readability-function-cognitive-complexity)
auto solve = []() -> void {
	for( auto solve_c: algarismos_sem_zero ) {
		c = solve_c;
		for( auto solve_r: algarismos_sem_zero ) {
			r = solve_r;
			if( r == c ) {
				continue;
			}
			for( auto solve_d: algarismos_sem_zero ) {
				d = solve_d;
				if( d == c || d == r ) {
					continue;
				}
				for( auto solve_o: algarismos ) {
					o = solve_o;
					if( o == c || o == r || o == d ) {
						continue;
					}
					for( auto solve_s: algarismos ) {
						s = solve_s;
						if( s == c || s == r || s == d || s == o ) {
							continue;
						}
						for( auto solve_a: algarismos ) {
							a = solve_a;
							if( a == c || a == r || a == d || a == o || a == s ) {
								continue;
							}
							for( auto solve_n: algarismos ) {
								n = solve_n;
								if( n == c || n == r || n == d || n == o || n == s || n == a ) {
									continue;
								}
								for( auto solve_g: algarismos ) {
									g = solve_g;
									if( g == c || g == r || g == d || g == o || g == s || g == a || g == n ) {
										continue;
									}
									for( auto solve_e: algarismos ) {
										e = solve_e;
										if( e == c || e == r || e == d || e == o || e == s || e == a || e == n || e == g ) {
											continue;
										}
										if( CROSS + ROADS == DANGER ) {
											print_solution();
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
};

auto main() -> int
{
	solve();
	return 0;
}