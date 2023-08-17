#ifndef RSA_FILEMGT_BITSFILE_HPP_
#define RSA_FILEMGT_BITSFILE_HPP_

#include <string>
#include <fstream>
#include <string_view>

namespace rsa
{
	namespace filemgt
	{
		class bitsfile
		{
		private:
			std::ifstream m_file_backend;
			std::string   m_direct_data;

		public:
			bitsfile (std::string_view filename);
			bitsfile (bitsfile&& that);

			[[nodiscard ("getter")]] auto data(void)       const noexcept -> std::string_view;
			[[nodiscard ("pure")]]   auto has_opened(void) const noexcept -> bool;

			bitsfile& operator=(bitsfile&& that);

			~bitsfile() = default;
		};
	}
}

#endif // RSA_FILEMGT_BITSFILE_HPP_
