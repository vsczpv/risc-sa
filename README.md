# RISC-SA

RISC-SA is a RISC-V RV32I static performance analyzer made with the intention of
being university homework, more specifically towards our Computer Architecture
classes at University of Itajaí Vale, SC, Brazil. This program has no legal ties to
said university.

It takes an RISC-V program and, given an "organization" (in this program and in class
defined as the specific implementation of any set architecture), characterizes it
in a benchmark that:

1. Counts how many clock cycles it takes to execute the program;
2. Times how long it would take to execute the program;
3. Displayes the "Cycles per Instruction" of the choosen program/organization combo.

Adjencently, you can also compare multiple organizations against each other, showing
ther "performance factor", which was a requirement from the homework's spec.

Note that RISC-SA *does not* run the program and such, cannot evaluate branches.
The supplied program should, preferably, be supplied as a historic of runned instructions,
so that it can correctly evaluate said branches, as otherwise they'll be treated as
"always false". An external program must be used to expand said execution history.

Programs should be loaded as text files, with the instructions encoded in binary.
For example, the following program:

```
        addi s0, t2, 0x123
        beq  s0, t2, .foo
        sll  x1, x2, x3
.foo:   sub  ra, t4, s2
```

Should be encoded as:

```
00010010001100111000010000010011
00000000011101000000010001100011
00000000001100010001000010110011
01000001001011101000000010110011
```

More examples are available in the `examples` directory.

# Dependencies

A compiler which supports C++20 and meson. Linux is implied.

This program has been tested under Archlinux 18/08/2023, meson 1.2.1 and gcc 13.2.1.

# Compilation

This program uses meson as it's build system. A convenience script is provided to build it.

To compile, run `meta/build`.

Alternatively, you can manually run `meson setup build/` and `meson compile -C build/`.

# Running

From the source folder, test the program running:

```
build/risc-sa examples/example3.txt -o 2:2:5:4:3:3:2.25 -o 5:4:5:4:4:5:0.5
```

The output should be the following:

```
Organization 01 : Program ran 59 cycles, with total time elapsed of 132.75ns @ 2.68182 CPI.
Organization 02 : Program ran 98 cycles, with total time elapsed of 49ns @ 4.45455 CPI.

01 vs 02 : Organization 02 is better by a factor of 2.70918.
```

# Usage

This prompt is also available in the program itself with `risc-sa --help`.

```
RV32I static analyzer
Usage: build/risc-sa [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -c,--characterize-against TEXT Excludes: --hazard

                              Specifies which organization(s) to use in the benchmark;

                              The format specified must be in the following format:

                                  R:I:S:B:U:J:L:TCLK

                              Where all but TCLK are integer values of how much clockcycles the referred ins-
                              truction format takes to execute, and TCLK is a decimal value of how long it takes
                              for a clock to cycle, in nanoseconds. For example:

                                  2:2:5:4:3:3:3:2.25

                              Will specify an organization which takes 2.25 nanoseconds per clock, 2 clocks for
                              R type, 2 for I type, 5 for S type, 4 for B type, 3 for U type, 3 for J type and 3 for L type.

                              Also note that the ficticious format "L" is actually the format I, but from LOAD
                              instructions, as these use a different amount of cycles from normal I operations in
                              certain organizations.

                              You must specify atleast one organization.

  -z,--hazard ENUM:INT in [0 - 3] Needs: --output Excludes: --characterize-against
                              Parse pipeline hazards and dump a new file with NOPs and reorded instructions.
                              This option must be used in conjunction to -t.
                              Valid options are: 0 (insertonly), 1 (forward), 2 (reorder), 3 (both).

  -f,--file TEXT:FILE REQUIRED
                              The program to be analyzed
  -o,--output TEXT Needs: --hazard
                              Output file for optimization mode.
  --version                   Displays version and copyright information.

```

# Contact

Written by Vinícius Schütz Piva <vinicius.vsczpv@outlook.com>.

Started on 18/08/2023, last updated 06/10/2023.

# License

risc-sa is licensed under GNU GPL-3-or-later; files under `thirdparty` licensed under their respective licenses.

Full license is available in COPYING file, or alternitively at <https://www.gnu.org/licenses/>.

