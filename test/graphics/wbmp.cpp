#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>
#include "stationaryorbit/graphics-wbmp/bmpimage"
using namespace zawa_ch::StationaryOrbit::Graphics;

WBMP::WbmpLoader loader;

void Read();
void Write();
void FripV();
void FripH();
void Crop();
void Resize1();
void Resize2();

void Test_BMP()
{
	std::chrono::duration<double> elapsed;
	auto start = std::chrono::system_clock::now();
	Read();
	elapsed = std::chrono::system_clock::now() - start;
	std::cout << "File read: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::system_clock::now();
	Write();
	elapsed = std::chrono::system_clock::now() - start;
	std::cout << "File write: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::system_clock::now();
	FripV();
	elapsed = std::chrono::system_clock::now() - start;
	std::cout << "Vertical frip: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::system_clock::now();
	FripH();
	elapsed = std::chrono::system_clock::now() - start;
	std::cout << "Horizonal frip: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::system_clock::now();
	Crop();
	elapsed = std::chrono::system_clock::now() - start;
	std::cout << "Cropping: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::system_clock::now();
	Resize1();
	elapsed = std::chrono::system_clock::now() - start;
	std::cout << "Shrink: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::system_clock::now();
	Resize2();
	elapsed = std::chrono::system_clock::now() - start;
	std::cout << "Expand: " << elapsed.count() << "sec." << std::endl;
}

void Read()
{
	///	読み込みを行うWindowsビットマップファイル。
	const char* ifile = "Jellyfish.bmp";
	// ファイルを開く(ファイルオープンに失敗した場合は例外をスローする)
	std::fstream istream = std::fstream(ifile, std::ios_base::openmode::_S_in | std::ios_base::openmode::_S_bin);
	if (!istream.good()) throw std::logic_error("can't read file.");
	// ビットマップをロードする
	loader = WBMP::WbmpLoader(istream);
	// この段階で物理メモリにビットマップが格納されるためストリームは閉じても問題ない
	istream.close();
}

void Write()
{
	const char* ofile = "output.bmp";
	auto& buffer = dynamic_cast<const WBMP::WbmpRGBData&>(loader.Buffer());
	auto saver = WBMP::WbmpRGBDirectSaver(buffer);
	saver.HorizonalResolution() = loader.HorizonalResolution();
	saver.VerticalResolution() = loader.VerticalResolution();
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	saver.WriteTo(ostream);
    ostream.close();
}

void FripV()
{
	const char* ofile = "output_fripv.bmp";
	auto out = BitmapSimpleConvert<uint8_t, WBMP::WbmpRGBBuffer>::FripVertical(loader.Buffer());
	auto saver = WBMP::WbmpRGBDirectSaver(out);
	saver.HorizonalResolution() = loader.HorizonalResolution();
	saver.VerticalResolution() = loader.VerticalResolution();
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	saver.WriteTo(ostream);
    ostream.close();
}

void FripH()
{
	const char* ofile = "output_friph.bmp";
	auto out = BitmapSimpleConvert<uint8_t, WBMP::WbmpRGBBuffer>::FripHorizonal(loader.Buffer());
	auto saver = WBMP::WbmpRGBDirectSaver(out);
	saver.HorizonalResolution() = loader.HorizonalResolution();
	saver.VerticalResolution() = loader.VerticalResolution();
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	saver.WriteTo(ostream);
    ostream.close();
}

void Crop()
{
	const char* ofile = "output_crop.bmp";
	auto p1 = Point(100, 100);
	auto p2 = Point(loader.Buffer().GetWidth(), loader.Buffer().GetHeight()) - Point(100, 100);
	auto out = BitmapSimpleConvert<uint8_t, WBMP::WbmpRGBBuffer>::Crop(loader.Buffer(), Rectangle(p1, p2));
	auto saver = WBMP::WbmpRGBDirectSaver(out);
	saver.HorizonalResolution() = loader.HorizonalResolution();
	saver.VerticalResolution() = loader.VerticalResolution();
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	saver.WriteTo(ostream);
    ostream.close();
}

void Resize1()
{
	const char* ofile = "output_resize1.bmp";
	const float resizefactor = 0.5f;
	auto newsize = Point(size_t(loader.Buffer().GetWidth() * resizefactor), size_t(loader.Buffer().GetHeight() * resizefactor));
	auto out = BitmapSimpleConvert<uint8_t, WBMP::WbmpRGBBuffer>::Resize(loader.Buffer(), newsize, BitmapSimpleConvert<uint8_t, WBMP::WbmpRGBBuffer>::Nearest);
	auto saver = WBMP::WbmpRGBDirectSaver(out);
	saver.HorizonalResolution() = loader.HorizonalResolution();
	saver.VerticalResolution() = loader.VerticalResolution();
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	saver.WriteTo(ostream);
    ostream.close();
}

void Resize2()
{
	const char* ofile = "output_resize2.bmp";
	const float resizefactor = 2.0f;
	auto newsize = Point(size_t(loader.Buffer().GetWidth() * resizefactor), size_t(loader.Buffer().GetHeight() * resizefactor));
	auto out = BitmapSimpleConvert<uint8_t, WBMP::WbmpRGBBuffer>::Resize(loader.Buffer(), newsize, BitmapSimpleConvert<uint8_t, WBMP::WbmpRGBBuffer>::Nearest);
	auto saver = WBMP::WbmpRGBDirectSaver(out);
	saver.HorizonalResolution() = loader.HorizonalResolution();
	saver.VerticalResolution() = loader.VerticalResolution();
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	saver.WriteTo(ostream);
    ostream.close();
}
