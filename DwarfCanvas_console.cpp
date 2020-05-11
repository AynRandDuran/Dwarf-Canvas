#include <iostream>
#include <iomanip>
#include <bitset>
#include "DwarfCanvas.hpp"

int main(int argc, char* argv[]) {
	try{
		if(argc < 3)
			throw std::invalid_argument("Argument error : missing args\nUsage : canvas <input>.bmp <output>");

		DwarfCanvasReader dcr(argv[1], argc);
		if(dcr.metadata().signature[0]+dcr.metadata().signature[1] != 66+77)
			throw std::logic_error("File error: input file lacks valid BMP signature\nExpected 'BM'");
		if(dcr.metadata().bmp_height != 2 || dcr.metadata().bmp_width != 8)
			throw std::logic_error("File error: input file is not a valid DF palette (2x8 px)");

		std::cout << "Here's the bitmap I read:\n";
		for(int b = 0; b < dcr.metadata().image_size; b++) {
			if(b%(dcr.raw_image().pixel_width)==0)
				std::cout << "\n";
			std::cout << std::hex << std::setw(3) << std::setfill(' ') << std::left
			<< ((std::bitset<8>)dcr.raw_image().pixels[b]).to_ulong() << " ";
		}

		DwarfCanvasFormatter dcf(dcr.raw_image());
		DwarfCanvasWriter dcw(argv[2], dcf);
		std::cout << "\ndone!" << std::endl;

	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
