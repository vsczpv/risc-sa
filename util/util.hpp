#ifndef RSA_UTIL_UTIL_HPP_
#define RSA_UTIL_UTIL_HPP_

#include <tuple>
#include <vector>
#include <limits>

#include <iostream>

#define VT_BOLD      "\033[1m"
#define VT_UNDERLINE "\033[4m"

#define VT_END       "\033[0m"

namespace util
{
	template <typename T> class lookup_table
	{
	private:
		std::vector <T> m_elements;
	public:
		lookup_table(void) {}
		lookup_table(std::initializer_list<std::tuple<T, std::size_t>> elems, T def, std::size_t highest_item)
		{

			std::size_t highest = std::numeric_limits<std::size_t>::min();

			for (auto& e : elems)
			{
				auto& [first, second] = e;
				highest = highest < second ? second : highest;
			}

			this->m_elements.resize(highest_item);

			for (std::size_t i = 0; i < highest; i++) this->m_elements[i] = def;

			for (auto& e : elems)
			{
				auto& [first, second] = e;
				this->m_elements[second] = first;
			}

		}
		~lookup_table() = default;

		T& operator[] (unsigned long long int i) { return this->m_elements[i]; }
	};
}

#endif // RSA_UTIL_UTIL_HPP_
