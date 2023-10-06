#include <rv/optimize.hpp>
#include <app.hpp>

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


void rsa::optimize(void)
{

	auto o2c = rsa::rv::opcode2clobber::get();

	switch (rsa::hzmode)
	{
		case rsa::InsertOnly:
		{
			/*
			for (auto& i : rsa::program.instructions()) {}
			*/

			std::size_t isz;

			for (std::size_t i = 0; i < (isz = rsa::program.instructions().size()); i++)
			{

				auto push = [] (int amnt, int where)
				{
					auto& c = rsa::program.mut_instructions();
					while (amnt --> 0)
					{
						c.emplace(c.begin()+where, rv::instruction(rv::NOP_INSTRUCTION));
					}
				};

				auto this_clbr = o2c[rsa::program.instructions()[i].OP()];
				if (!this_clbr.RD()) continue;
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
		break;
		default:
			break;
	}

	for (auto& i : rsa::program.instructions())
	{
		std::cout << i.string() << std::endl;
	}

}
