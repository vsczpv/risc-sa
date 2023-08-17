#ifndef RSA_APP_HPP_
#define RSA_APP_HPP_

#include <rv/program.hpp>
#include <rv/benchdata.hpp>

#include <deque>
#include <optional>
#include <string>

namespace rsa
{
	extern std::deque <rv::organization> organizations;
	extern rv::program program;

	auto parse_cmdline(int argc, char* argv[]) -> std::optional <std::string>;
}

#endif // RSA_APP_HPP_
