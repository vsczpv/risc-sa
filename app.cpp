#include <app.hpp>

#include <rv/program.hpp>
#include <rv/benchdata.hpp>

#include <optional>
#include <string>

using namespace rsa;

std::deque <rv::organization> rsa::organizations;
rv::program                   rsa::program;

auto parse_cmdline(int argc, char* argv[]) -> std::optional <std::string>
{

	/*
	 * risc-sa -o ORG PRG.txt
	 */
	if (argc < 4) return "Not enough arguments";

	enum CmdState
	{
		OnProgramExpect,
		OnDashArgument,
		OnOrgExtract
	}
	state = OnProgramExpect;

	bool running = true;
	int  index   = 1;


	while (running)
	{
		switch (state)
		{
			case OnProgramExpect:
			{

			}
			case OnDashArgument:
			case OnOrgExtract:
				running = false;
				break;
		}
		break;
	}

	return std::nullopt;
}
