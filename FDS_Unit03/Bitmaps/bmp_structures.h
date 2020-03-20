#if !defined BMP_STRUCTURES_H
#define BMP_STRUCTURES_H
#include<cstdint>

typedef uint_fast8_t byte_type;
typedef uint_fast32_t long_type;
typedef uint_fast32_t uint32_type;
typedef uint16_t uint16_type;

namespace graphics {
	// pragma = komprimieren. char + int in struct würde so aussehen:
	// char + 3 leere byte (weil char = 1 byte) und int (4 byte)
	// > leere bytes weglassen
	// Pragma pack push 1 = keinen platz verschenken. keine freien bytes zwischen char und int
#pragma pack (push, 1)
	struct file_header_type {
		union {
			byte_type signature[2]; // file type; must be ’BM’
			uint16_type type; // file type; must be 0x4d42
		};
		uint32_type size; // size, in bytes, of the bitmap file
		uint16_type reserved_1; // reserved; must be 0
		uint16_type reserved_2; // reserved; must be 0
		uint32_type offset; // offset, in bytes, from the beginning of the ’file_header_t’ to the bitmap bits
	};
#pragma pack(pop)

#pragma pack (push, 1)
	struct info_header_type {
		uint32_type size; // number of bytes required by the structure
		long_type width; // width of the bitmap, in pixels
		long_type height; // height of the bitmap, in pixels
		uint16_type planes; // number of planes for the target device; must be 1
		uint16_type bit_count; // number of bits per pixel
		uint32_type compression; // type of compression; 0 for uncompressed RGB
		uint32_type size_image; // size, in bytes, of the image
		long_type x_pels_pm; // horizontal resolution, in pixels per meter
		long_type y_pels_pm; // vertical resolution, in pixels per meter
		uint32_type clr_used; // number of color indices in the color table
		uint32_type clr_important; // number of color indices that are considered important
	};
#pragma pack (pop)
}



#endif
