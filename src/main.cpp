#include <pixelrain.h>
#include <pixelrain_defaults.h>
#include <SOIL.h>
#include <string>

template <typename PixelRain>
void saveResult(const PixelRain* pixelRain, const std::string& fileName)
{
	int width = pixelRain->getWidth();
	int height = pixelRain->getHeight();
	std::vector<Vect4f> result = pixelRain->getRGBResult();
	std::vector<unsigned char> data(width * height * 4);
	for (size_t i = 0; i < result.size(); ++i)
	{
		data[4 * i] = (unsigned char)(result[i].x * 255);
		data[4 * i + 1] = (unsigned char)(result[i].y * 255);
		data[4 * i + 2] = (unsigned char)(result[i].z * 255);
		data[4 * i + 3] = (unsigned char)(result[i].w * 255);
	}
	SOIL_save_image(fileName.c_str(), SOIL_SAVE_TYPE_BMP, width, height, 4, data.data());
}

int main(int argc, char* argv[])
{
	//create a rgb version
	typedef PixelRain<Type_Color3, Comparator_Color3, ConverterRGB, Random_Color3> PixelRain_t;
	PixelRain_t pixelRain(500, 2000, Comparator_Color3(), ConverterRGB(), Random_Color3(0, 1, 0, 0.2f, 0, 0.2f));

	//add seed in the middle
	pixelRain.addSeed(250, 250);

	//compute
	pixelRain.compute(CoutProgressListener());

	//save
	saveResult(&pixelRain, "test1.bmp");
}