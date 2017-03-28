#ifndef __PIXEL_RAIN__HEADER__INCLUDED__
#define __PIXEL_RAIN__HEADER__INCLUDED__

#include <vector.h>
#include <string.h>
#include <list>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <iostream>

/**
 * \brief The pixel rain class generates the
 * images. It's template parameter define the
 * properties of the algorithm
 * \tparam T the type used to store one pixel's information.
 *	It must be default constructible and assignable.
 * \tparam Comp The comparator used to compute the distance two colors.
 *	It must be valid to call it like {\code float Comp(const T& t1, const T& t2) const}
 *	\tparam Conv The converter that converts the colors of type T
 *	into a type of Vect4f storing the rgba values.
 *	Hence, it must be valid to call it like {\code Vect4f Conv(const T& t) const}
 * \tparam Random The random generator that generates the colors.
 *	It must be valid to call it like {\code T Random()}
 */
template <typename T, typename Comp, typename Conv, typename Random>
class PixelRain
{
public:
	/**
	 * \brief The type for a pixel. It is "T".
	 */
	typedef T pixel_t;
	/**
	 * \brief The type of the comparator. It is "Comp"
	 */
	typedef Comp comparator_t;
	/**
	 * \brief The type of the converter.
	 */
	typedef Conv converter_t;
	/**
	 * \brief The type of the random generator. It is "Random"
	 */
	typedef Random random_t;

private:
	const comparator_t comparator_;
	const converter_t converter_;
	random_t random_;
	const int width_;
	const int height_;
	
	struct OpenPixel
	{
		int x_;
		int y_;
		//0: x-, 1: x+, 2:y-, 3:y+
		bool neighborValid_[4];
		pixel_t neighbors_[4];
		OpenPixel() {}
		OpenPixel(int x, int y, int i, const pixel_t c)
			: x_(x), y_(y)
		{
			memset(neighborValid_, 0, sizeof(bool) * 4);
			neighborValid_[i] = true;
			neighbors_[i] = c;
		}
	};
	static const int X_MINUS = 0;
	static const int X_PLUS = 1;
	static const int Y_MINUS = 2;
	static const int Y_PLUS = 3;

	pixel_t* data_;
	bool* dataValid_;
	int remainingPixels_;
	std::list<OpenPixel> openPixels_;
	typedef typename std::list<OpenPixel>::iterator openPixelIterator_t;

	// Helper

	int L(int x, int y) const { return x + width_*y; }

	pixel_t nextPixel() { return random_(); }

	void addOpenPixel(int x, int y)
	{
		if (x < 0 || y < 0 || x >= width_ || y >= height_) return;
		OpenPixel p;
		p.x_ = x;
		p.y_ = y;
		memset(p.neighborValid_, false, sizeof(bool) * 4);
		if (x - 1 >= 0 && dataValid_[L(x - 1, y)])
		{
			p.neighborValid_[X_MINUS] = true;
			p.neighbors_[X_MINUS] = data_[L(x - 1, y)];
		}
		if (x + 1 < width_ && dataValid_[L(x + 1, y)]) {
			p.neighborValid_[X_PLUS] = true;
			p.neighbors_[X_PLUS] = data_[L(x + 1, y)];
		}
		if (y - 1 >= 0 && dataValid_[L(x, y - 1)]) {
			p.neighborValid_[Y_MINUS] = true;
			p.neighbors_[Y_MINUS] = data_[L(x, y - 1)];
		}
		if (y + 1 < height_ && dataValid_[L(x, y + 1)]) {
			p.neighborValid_[Y_PLUS] = true;
			p.neighbors_[Y_PLUS] = data_[L(x, y + 1)];
		}
		openPixels_.push_back(p);
	}

	OpenPixel findAndRemoveClosestMatch(const pixel_t& color)
	{
		openPixelIterator_t match;
		float distance = FLT_MAX;
		//find closest match
		for (auto it = openPixels_.begin(); it != openPixels_.end(); ++it)
		{
			const OpenPixel& p = *it;
			float d = FLT_MAX;
			for (int i = 0; i < 4; ++i) {
				if (!p.neighborValid_[i]) continue;
				d = std::min(d, comparator_(color, p.neighbors_[i]));
			}
			if (d < distance)
			{
				distance = d;
				match = it;
			}
		}
		//delete it
		OpenPixel result = *match;
		openPixels_.erase(match);
		return result;
	}

	openPixelIterator_t findOpenPixel(int x, int y)
	{
		for (auto it = openPixels_.begin(); it != openPixels_.end(); ++i)
		{
			if (it->x == x && it->y == y) return it;
		}
		return openPixels_.end();
	}

	void updateOpenPixels(int x, int y, const pixel_t& color)
	{
		bool xMinus = false;
		bool xPlus = false;
		bool yMinus = false;
		bool yPlus = false;
		//Check & update existing open pixels
		for (OpenPixel& op : openPixels_)
		{
			if (op.x_ == x + 1 && op.y_ == y)
			{
				op.neighborValid_[X_MINUS] = true;
				op.neighbors_[X_MINUS] = color;
				xMinus = true;
			}
			else if (op.x_ == x - 1 && op.y_ == y) {
				op.neighborValid_[X_PLUS] = true;
				op.neighbors_[X_PLUS] = color;
				xPlus = true;
			}
			else if (op.x_ == x && op.y_ == y + 1) {
				op.neighborValid_[Y_MINUS] = true;
				op.neighbors_[Y_MINUS] = color;
				yMinus = true;
			}
			else if (op.x_ == x && op.y_ == y - 1) {
				op.neighborValid_[Y_PLUS] = true;
				op.neighbors_[Y_PLUS] = color;
				yPlus = true;
			}
		}
		//create missing open pixels
		if (!xMinus && x + 1 < width_ && !dataValid_[L(x+1, y)]) openPixels_.push_back(OpenPixel(x + 1, y, X_MINUS, color));
		if (!xPlus && x - 1 >= 0 && !dataValid_[L(x-1, y)]) openPixels_.push_back(OpenPixel(x - 1, y, X_PLUS, color));
		if (!yMinus && y + 1 < height_ && !dataValid_[L(x, y+1)]) openPixels_.push_back(OpenPixel(x, y + 1, Y_MINUS, color));
		if (!yPlus && y - 1 >= 0 && !dataValid_[L(x, y-1)]) openPixels_.push_back(OpenPixel(x, y - 1, Y_PLUS, color));
	}
public:
	PixelRain(int width, int height,
		const comparator_t& comparator = comparator_t(),
		const converter_t& converter = converter_t(),
		const random_t& random = random_t())
	: comparator_(comparator)
	, converter_(converter)
	, random_(random)
	, width_(width)
	, height_(height)
	{
		data_ = new pixel_t[width * height];
		dataValid_ = new bool[width * height];
		reset();
	}

	~PixelRain()
	{
		delete[] data_;
		delete[] dataValid_;
		data_ = NULL;
		dataValid_ = NULL;
	}

	void reset()
	{
		remainingPixels_ = width_ * height_;
		memset(dataValid_, 0, sizeof(bool) * width_ * height_);
		openPixels_.clear();
	}

	const pixel_t* getRawResult() const
	{
		return data_;
	}

	/**
	 * \brief Returns the result as a linearized array of RGBA-values
	 * \return the result as RGBA array
	 */
	std::vector<Vect4f> getRGBResult() const
	{
		std::vector<Vect4f> result(width_ * height_);
		for (size_t i = 0; i < width_ * height_; ++i)
			result[i] = converter_(data_[i]);
		return result;
	}

	int getWidth() const
	{
		return width_;
	}

	int getHeight() const
	{
		return height_;
	}

	/**
	 * \brief Adds a seed pixel.
	 * All seeds must be at least 2 pixels apart from each other
	 * \param x the x position
	 * \param y the y position
	 * \param color the color of the seed
	 */
	void addSeed(int x, int y, pixel_t color)
	{
		assert(x < width_);
		assert(y < height_);
		assert(dataValid_[L(x, y)] == false);
		//set data
		data_[L(x, y)] = color;
		dataValid_[L(x, y)] = true;
		addOpenPixel(x - 1, y);
		addOpenPixel(x + 1, y);
		addOpenPixel(x, y - 1);
		addOpenPixel(x, y + 1);
		remainingPixels_--;
	}

	/**
	 * \brief Adds a new seed with a random color
	 * \param x the x position
	 * \param y the y position
	 */
	void addSeed(int x, int y)
	{
		addSeed(x, y, nextPixel());
	}

	/**
	 * \brief Computes the pixel rain.
	 * \tparam ProgressListener the progress listener.
	 *	It must be valid to call {\code ProgressListener(float percentage, int remainingPixels}
	 * \param l the listener
	 */
	template <typename ProgressListener>
	void compute(const ProgressListener& l = ProgressListener())
	{
		float startRemaining = (float) remainingPixels_;
		while (remainingPixels_ > 0)
		{
			if (openPixels_.empty())
			{
				std::cerr << "No more open pixels, but still " << remainingPixels_ << " are left" << std::endl;
				return;
			}

			//1. generate next color
			pixel_t pixel = nextPixel();
			//2. find closest match
			OpenPixel op = findAndRemoveClosestMatch(pixel);
			//3. place it
			dataValid_[L(op.x_, op.y_)] = true;
			data_[L(op.x_, op.y_)] = pixel;
			//4. update open pixels
			updateOpenPixels(op.x_, op.y_, pixel);
			//5. call listener
			remainingPixels_--;
			l(1.0f - remainingPixels_ / startRemaining, remainingPixels_);
		}
	}

private:
	PixelRain(const PixelRain& other) = delete;
	PixelRain(PixelRain&& other) = delete;
	PixelRain& operator=(const PixelRain& other) = delete;
	PixelRain& operator=(PixelRain&& other) = delete;
};


#endif