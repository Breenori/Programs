#include "bmp.h"
#include "pfc-mini.hpp"
#include <fstream>

void graphics::create(graphics::bitmap_type& bmp, long_type const width, long_type const height)
{
	clear(bmp);

	// (18/4) --> aufrunden --> *4;
	bmp.m_size_scan_line = (int)ceil(bmp.m_size_pixel * width * 0.25) * 4;

	bmp.m_info_header.size = sizeof(info_header_type);
	bmp.m_info_header.width = width;
	bmp.m_info_header.height = height;
	bmp.m_info_header.size_image = bmp.m_size_scan_line * height;

	bmp.m_file_header.offset = sizeof(file_header_type) + sizeof(info_header_type);
	bmp.m_file_header.size = bmp.m_file_header.offset + bmp.m_info_header.size_image;

	bmp.m_p_data = new byte_type[bmp.m_info_header.size_image];
	
	for (uint32_type i(0); i < bmp.m_info_header.size_image; i++)
	{
		bmp.m_p_data[i] = pfc::get_random_uniform(0x00, 0xff);
	}
}

void graphics::clear(graphics::bitmap_type& bmp)
{
	bmp.m_file_header.signature[0] = 'B';
	bmp.m_file_header.signature[1] = 'M';
	bmp.m_file_header.size = 0;
	bmp.m_file_header.reserved_1 = 0;
	bmp.m_file_header.reserved_2 = 0;
	bmp.m_file_header.offset = 0;

	bmp.m_info_header.size = 0;
	bmp.m_info_header.width = 0;
	bmp.m_info_header.height = 0;
	bmp.m_info_header.planes = 1;
	bmp.m_info_header.bit_count = 24;
	bmp.m_info_header.compression = 0;
	bmp.m_info_header.size_image = 0;
	bmp.m_info_header.x_pels_pm = 0;
	bmp.m_info_header.y_pels_pm = 0;
	bmp.m_info_header.clr_used = 0;
	bmp.m_info_header.clr_important = 0;

	if (bmp.m_p_data != nullptr)
	{
		delete[] bmp.m_p_data;
		bmp.m_p_data = nullptr;
	}

	bmp.m_size_scan_line = 0;
	bmp.m_size_pixel = 3;
}

bool graphics::write_to_file(bitmap_type const& bmp, std::string const& file_name)
{
	std::ofstream out(file_name, std::ios_base::binary);
	bool ok = true;

	if (out)
	{
		if (pfc::write(out, bmp.m_file_header) &&
			pfc::write(out, bmp.m_info_header) &&
			pfc::write_ptr(out, bmp.m_p_data, bmp.m_info_header.size_image))
		{

		}
		else
		{
			std::cout << "ERROR" << std::endl;
			ok = false;
		}
	}

	out.close();
	return ok;
}

