#ifndef RSA_RV_OPCODE_HPP_
#define RSA_RV_OPCODE_HPP_

#include <util/util.hpp>

#include <tuple>

namespace rsa
{
	namespace rv
	{

		enum InstructionType
		{
			InsT_R = 1,
			InsT_I = 2,
			InsT_S = 3,
			InsT_B = 4,
			InsT_U = 5,
			InsT_J = 6,
			InsT_Inval
		};

		// Incrementing InsT_Inval is undefined behaviour
		InstructionType operator++(InstructionType& type);
		InstructionType operator++(InstructionType& type, int);

		class opcode2type
		{
		private:

			static constexpr std::size_t HIGHEST_ITEM = 0b1111111;

			util::lookup_table <InstructionType> m_opcodes;

			inline static opcode2type* instance = nullptr;

			opcode2type(std::initializer_list <std::tuple <InstructionType, std::size_t>> ops) : m_opcodes(ops, InsT_Inval, HIGHEST_ITEM) {}

		public:

			InstructionType& operator[] (unsigned long long int i) { return this->m_opcodes[i]; }

			opcode2type(void) {}
			static opcode2type& get(void)
			{
				if (instance != nullptr) return *instance; else return
				*(
					instance =  new opcode2type
					({
						{InsT_I, 0b0000011}, // LOAD
						//       0b0000111   // LOAD-FP     [InsT_I]
						//       0b0001011   // custom-0    [undef]
						{InsT_I, 0b0001111}, // MISC-MEM
						{InsT_I, 0b0010011}, // OP-IMM
						{InsT_U, 0b0010111}, // AUIPC
						//       0b0011011   // OP-IMM-32   [InsT_I]
						//       0b0011111   // 48b
						{InsT_S, 0b0100011}, // STORE
						//       0b0100111   // STORE-FP    [InsT_S]
						//       0b0101011   // custom-1    [undef]
						//       0b0101111   // AMO         [InsT_R]
						{InsT_R, 0b0110011}, // OP
						{InsT_U, 0b0110111}, // LUI
						{InsT_R, 0b0111011}, // OP-32
						//       0b0111111   // 64b
						//       0b1000011   // MADD        [ext]
						//       0b1000111   // MSUB        [ext]
						//       0b1001011   // MNSUB       [ext]
						//       0b1001111   // MNADD       [ext]
						//       0b1010011   // OP-FP       [InsT_R]
						//       0b1010111   // reserved
						//       0b1011011   // custom-2/rv128
						//       0b1011111   // 48b:80b
						{InsT_B, 0b1100011}, // BRANCH
						{InsT_I, 0b1100111}, // JALR
						//       0b1101011   // reserved
						{InsT_J, 0b1101111}, // JAL
						{InsT_I, 0b1110011}, // SYSTEM
						//       0b1110111   // reserved
						//       0b1111011   // custom-3/rv128
						//       0b1111111   // 48b:80b
					})
				);
			}

		};
	}
}

#endif // RSA_RV_OPCODE_HPP_
