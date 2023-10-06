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

#include <rv/optimize.hpp>
#include <app.hpp>

using namespace rsa;

void rsa::characterize(void)
{

	for (auto& o : rsa::organizations) rsa::results.push_back
	(
		rsa::program.characterize_against(o)
	);

	for (auto& r : rsa::results) r.print();

	std::cout << std::endl;

	for (auto& a : rsa::results) for (auto& b : rsa::results)
	{
		if (a.source_id == b.source_id) continue;
		if (b.seen)                     continue;

		auto comp = rv::compare_results(a, b);

		std::printf
		(
			"%02i vs %02i : Organization %02i is better by a factor of %g.\n",
			a.source_id, b.source_id,
			comp.second.source_id, comp.first
		);

		a.seen = true;
	}

}


static auto push = [] (int amnt, int where)
{
	auto& c = rsa::program.mut_instructions();
	while (amnt --> 0)
	{
		c.emplace(c.begin()+where, rv::instruction(rv::NOP_INSTRUCTION));
	}
};


static void insert_only(bool foward = false)
{

	auto o2c = rsa::rv::opcode2clobber::get();

	std::size_t isz;

	for (std::size_t i = 0; i < (isz = rsa::program.instructions().size()); i++)
	{

		auto this_clbr = o2c[rsa::program.instructions()[i].OP()];

		if (foward)
		{
			if (! (rsa::program.instructions()[i].OP() == rv::LOAD_OP) ) continue;
		}

		else
		{
			if (!this_clbr.RD()) continue;
		}

		auto which_rd  = rsa::program.instructions()[i].RD();

		/* x0 is constant */
		if (which_rd == 0) continue;

		std::optional <rsa::rv::clobber> fwd1_clbr, fwd2_clbr;

		if (i < isz-2) fwd2_clbr = o2c[rsa::program.instructions()[i+2].OP()];
		if (i < isz-1) fwd1_clbr = o2c[rsa::program.instructions()[i+1].OP()];

		if (fwd1_clbr)
		{

			auto which_rs1 =  rsa::program.instructions()[i+1].RS1();
			auto which_rs2 =  rsa::program.instructions()[i+1].RS2();
			auto uses_rsx  =  fwd1_clbr->RS1()
							|| fwd1_clbr->RS2();

			if (uses_rsx) if (which_rs1 == which_rd || which_rd == which_rs2) { push(2, i+1); continue; }
		}

		if (fwd2_clbr)
		{
			auto which_rs1 =  rsa::program.instructions()[i+2].RS1();
			auto which_rs2 =  rsa::program.instructions()[i+2].RS2();
			auto uses_rsx  =  fwd2_clbr->RS1()
							|| fwd2_clbr->RS2();

			if (uses_rsx) if (which_rs1 == which_rd || which_rd == which_rs2) { push(1, i+2); continue; }
		}

	}

}

static void reorder(void)
{

}

void rsa::optimize(void)
{

	switch (rsa::hzmode)
	{
		case rsa::InsertOnly: insert_only();            break;
		case rsa::Foward:     insert_only(FOWARD);      break;
		case rsa::Reorder:    reorder(); insert_only();
		default:
			break;
	}

	for (auto& i : rsa::program.instructions())
	{
		std::cout << i.string() << std::endl;
	}

}
