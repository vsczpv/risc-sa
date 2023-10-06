/*
 * This file is part of risc-sa, an RISC-V RV32I static performance analyzer,
 * made with intention of being university homework. This program has no legal
 * ties to the University of Itajaí Vale, SC, Brazil.
 *
 * Copyright © 2023 Vinícius Schütz Piva
 *
 * risc-sa is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>
 *
 */

#include <app.hpp>
#include <util/util.hpp>

#include <rv/program.hpp>
#include <rv/benchdata.hpp>

#include <optional>
#include <string>
#include <cstring>

#include <thirdparty/CLI11.hpp>

using namespace rsa;

std::deque <rv::result>       rsa::results;
std::deque <rv::organization> rsa::organizations;
rv::program                   rsa::program;
rv::program                   rsa::output;
rsa::Mode                     rsa::mode;
rsa::HazardsMode              rsa::hzmode;

void version(std::int64_t)
{
	std::cout <<
			"risc-sa, version " VERSION "\n"
	       "Copyright (C) 2023 Vinícius Schütz Piva\n"
		   "Licensed under GNU GPL-3.0-or-later <http://gnu.org/licenses/gpl.html>\n"
		   "\n"
		   "This is free software; you are free to change and redistribute it.\n"
		   "There is NO WARRANTY, to the extent permitted by law."
	<< std::endl;

	exit(0);
}

[[nodiscard]] auto rsa::parse_cmdline(int argc, char* argv[]) -> std::optional <std::string>
{

	CLI::App app {"RV32I static analyzer"};

	std::string org_doc =
		"\n"
		"Specifies which organization(s) to use in the benchmark;\n"
		"\n"
		"The format specified must be in the following format:\n"
		"\n"
		"    R:I:S:B:U:J:L:TCLK\n"
		"\n"
		"Where all but TCLK are integer values of how much clockcycles the referred ins-\n"
		"truction format takes to execute, and TCLK is a decimal value of how long it takes\n"
		"for a clock to cycle, in nanoseconds. For example:\n"
		"\n"
		"    2:2:5:4:3:3:3:2.25\n"
		"\n"
		"Will specify an organization which takes 2.25 nanoseconds per clock, 2 clocks for\n"
		"R type, 2 for I type, 5 for S type, 4 for B type, 3 for U type, 3 for J type and 3 for L type.\n"
		"\n"
		"Also note that the ficticious format \"L\" is actually the format I, but from LOAD\n"
		"instructions, as these use a different amount of cycles from normal I operations in\n"
		"certain organizations.\n"
		"\n"
		"You must specify atleast" VT_BOLD " one " VT_END "organization.\n";


	auto orgs     = std::vector <std::string> ();
	auto orgs_opt = app.add_option("-c,--characterize-against", orgs, org_doc)
		->expected(0,1);

	std::string hazard_doc =
		"Parse pipeline hazards and dump a new file with NOPs and reorded instructions.\n"
		"This option must be used in conjunction to -t.\n"
		"Valid options are: 0 (insertonly), 1 (forward), 2 (reorder), 3 (both).\n";

	HazardsMode hazard;
	auto hazard_opt = app.add_option("-z,--hazard", hazard, hazard_doc)
		->expected(0,1)
		->check   (CLI::Range(0, 3));

	std::string filename;
	app.add_option("-f,--file", filename, "The program to be analyzed")
		->required()
		->expected(0,1)
		->check   (CLI::ExistingFile);

	std::string output;
	auto output_opt = app.add_option("-o,--output", output, "Output file for optimization mode.")
		->expected(0,1);

	auto version_doc = "Displays version and copyright information.";
	app.add_flag_function("--version", version, version_doc);

	orgs_opt->excludes(hazard_opt);

	hazard_opt->needs(output_opt);
	output_opt->needs(hazard_opt);

	try { app.parse(argc, argv); } catch (const CLI::ParseError &e)
	{
		app.exit(e); return "";
	}

	rsa::program = rv::program (filename);

	if (!rsa::program.has_opened()) return "Error: Could not open specified program.";

	if (orgs_opt->count() == 0 && hazard_opt->count() == 0) return "Error: Must specify atleas one mode";

	if (orgs_opt->count()) rsa::mode = Characterize;
	else                   rsa::mode = Optimize;

	if (rsa::mode == Characterize)
	{

		for (std::size_t org_id = 0; org_id < orgs.size(); org_id++)
		{
			rsa::organizations.push_back
			(
				rsa::rv::organization (std::string(orgs[org_id]), org_id+1)
			);
			if (!rsa::organizations[org_id].is_valid()) return "Error: Could not parse specified organization.";
		};

	}

	else
	{
		rsa::output = rv::program (output, rv::NoParse);
		rsa::hzmode = hazard;
	}

	return std::nullopt;
}
