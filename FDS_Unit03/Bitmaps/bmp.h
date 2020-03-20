#if !defined BMP_H
#define BMP_H
#include "bmp_structures.h"
#include<string>

namespace graphics {
	struct bitmap_type {
		file_header_type m_file_header;
		info_header_type m_info_header;

		byte_type* m_p_data;

		size_t m_size_scan_line;
		size_t m_size_pixel;
	};

	void create(bitmap_type& bmp, long_type const width, long_type const height);
	void clear(bitmap_type& bmp);
	bool write_to_file(bitmap_type const& bmp, std::string const& file_name);
}

#endif