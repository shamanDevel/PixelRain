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
	//typedef PixelRain<Type_Color3, Comparator_Color3, ConverterRGB, Random_Color3> PixelRain_t;
	//PixelRain_t pixelRain(500, 500, Comparator_Color3(), ConverterRGB(), Random_Color3(0, 1, 0, 0.2f, 0, 0.2f));

	//create a hcl version, settings are for a 'fire'-effect
	//typedef PixelRain<Type_Color3, Comparator_Color3, ConverterHCL, Random_Color3> PixelRain_t;
	//PixelRain_t pixelRain(2000, 5000, Comparator_Color3(6, 1, 0.2f), ConverterHCL(), Random_Color3(-0.05f, 0.1f, 0.6f, 0.9f, 0.05f, 1.0f));

	//create a hcl version, settings are for a green/blue-effect
	//typedef PixelRain<Type_Color3, Comparator_Color3, ConverterHCL, Random_Color3> PixelRain_t;
	//PixelRain_t pixelRain(400, 400, Comparator_Color3(1.5f, 1, 0.2f), ConverterHCL(), Random_Color3(0.4f, 0.6f, 0.6f, 0.9f, 0.05f, 0.9f));

	//create a mixture for an autumn effect
	typedef PixelRain<Type_Color3, HueComparator_Color3, ConverterHCL, MixtureRandom_Color3> PixelRain_t;
	MixtureRandom_Color3 mr;
	mr.addGenerator(Random_Color3(0.25f, 0.4f, 0.6f, 0.9f, 0.05f, 0.9f), 2); //green
	mr.addGenerator(Random_Color3(0.0f, 0.1f, 0.6f, 0.9f, 0.05f, 0.6f), 0.5f); //brown/red
	mr.addGenerator(Random_Color3(0.1f, 0.2f, 0.3f, 0.9f, 0.05f, 0.9f), 1); //yellow
	mr.normalize();
	PixelRain_t pixelRain(500, 500, HueComparator_Color3(0.1f, 1, 0.2f), ConverterHCL(), mr);

	//add seed in the middle
	pixelRain.addSeed(pixelRain.getWidth()/6, pixelRain.getHeight()/6);
	//pixelRain.addSeed(pixelRain.getWidth() / 2 - 5, pixelRain.getHeight() / 2 - 5);
	//pixelRain.addSeed(pixelRain.getWidth() / 2 - 5, pixelRain.getHeight() / 2 + 5);
	//pixelRain.addSeed(pixelRain.getWidth() / 2 + 5, pixelRain.getHeight() / 2 - 5);
	//pixelRain.addSeed(pixelRain.getWidth() / 2 + 5, pixelRain.getHeight() / 2 + 5);

	//compute
	pixelRain.compute(CoutProgressListener());

	//save
	saveResult(&pixelRain, "test1.bmp");
}