#include "bmp.h"

void main() {
	graphics::bitmap_type bmp;
	bmp.m_p_data = nullptr;
	graphics::create(bmp, 30, 50);
	graphics::write_to_file(bmp, "test.bmp");
}