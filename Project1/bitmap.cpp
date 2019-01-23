#include "bitmap.h"

// Cell shading
// Adjusts individual pixel component values to nearest value of {0, 128, 255}
// INPUT: Takes a reference to a bitmap object as input
// OUTPUT: Does not return
void cellShade(Bitmap & b)
{
	int height = b.get_height();			// Get height
	int width = b.get_width();			// Get width

	for (int i = 0; i < height; i++)		
	{
		for (int j = 0; j < width; j++)
		{
			int redComponent = b.get_red(j, i);				// Get red component

			if (redComponent >= 0 && redComponent <= 64)			// Set red component
			{
				b.set_red(j, i, 0);
			}
			else if (redComponent > 64 && redComponent <= 192)
			{
				b.set_red(j, i, 128);
			}
			else
			{
				b.set_red(j, i, 255);
			}

			int greenComponent = b.get_green(j, i);				// Get green component

			if (greenComponent >= 0 && greenComponent <= 64)		// Set green component
			{
				b.set_green(j, i, 0);
			}
			else if (greenComponent > 64 && greenComponent <= 192)
			{
				b.set_green(j, i, 128);
			}
			else
			{
				b.set_green(j, i, 255);
			}

			int blueComponent = b.get_blue(j, i);				// Get blue component

			if (blueComponent >= 0 && blueComponent <= 64)			// Set blue component
			{
				b.set_blue(j, i, 0);
			}
			else if (blueComponent > 64 && blueComponent <= 192)
			{
				b.set_blue(j, i, 128);
			}
			else
			{
				b.set_blue(j, i, 255);
			}
		}
	}
}

// Gray scale
// Sets pixel component values to the average of the RGB components of the pixel
// INPUT: Takes a refernce to a bitmap object as input
// OUTPUT: Does not return
void grayscale(Bitmap & b)
{
	int height = b.get_height();			// Get height
	int width = b.get_width();			// Get width

	for (int i = 0; i < height; i++)		// Traverse all bitmap (x, y) pairs
	{
		for (int j = 0; j < width; j++)
		{
			int value = (b.get_red(j, i) + b.get_green(j, i) + b.get_blue(j, i)) / 3;	// Average component values

			b.set_red(j, i, value);		// Set component values
			b.set_green(j, i, value);
			b.set_blue(j, i, value);
		}
	}
}

// Pixelate 16x16
// Averages the pixel component values across a 16x16 block of pixels
// INPUT: Takes a reference to a bitmap object as input
// OUTPUT: Does not return
void pixelate(Bitmap & b)
{
	int height = b.get_height();
	int width = b.get_width();

	int redSum = 0;									// Storage for sums
	int greenSum = 0;
	int blueSum = 0;

	int redAverage = 0;								// Storage for averages
	int greenAverage = 0;
	int blueAverage = 0;

	for (int y = 0; y <= height - 16; y+=16)					// Traverse all 16x16 blocks of pixels
	{
		for (int x = 0; x <= width - 16; x+=16)
		{
			for (int i = 0; i < 16; i++)					// Collect 16x16 block
			{
				for (int j = 0; j < 16; j++)
				{	
					redSum += b.get_red(x + j, y + i);		// Update sums
					greenSum += b.get_green(x + j, y + i);
					blueSum += b.get_blue(x + j, y + i);
				}
			}

			redAverage = redSum / 256;					// Calculate averages
			greenAverage = greenSum / 256;
			blueAverage = blueSum / 256;

			for (int k = 0; k < 16; k++)					// Traverse 16x16 block
			{
				for (int l = 0; l < 16; l++)
				{	
					b.set_red(x + k, y + l, redAverage);		// Set component values
					b.set_green(x + k, y + l, greenAverage);
					b.set_blue(x + k, y + l, blueAverage);
				}
			}
			
			redSum = 0;							// Reset sums
			greenSum = 0;
			blueSum = 0;

			redAverage = 0;							// Reset averages
			greenAverage = 0;
			blueAverage = 0;
		}
	}
}

// Gaussian Blurring
// Sets the pixel component values to the sum of the gaussian matrix
// for the surrounding 5x5 block of pixels
// INPUT: Takes a reference to a bitmap object as input
// OUTPUT: Does not return
void blur(Bitmap & b)
{
	int denominator = 256;

	int numerator[25] = {1, 4, 6, 4, 1, 4, 16, 24, 16, 4, 6, 24, 36, 24, 6, 4, 16, 24, 16, 4, 1, 4, 6, 4, 1};
	
	int height = b.get_height();
	int width = b.get_width();

	double redBlur = 0.0;								// Storage for blur values
	double greenBlur = 0.0;
	double blueBlur = 0.0;

	for (int y = 2; y <= height - 2 - 1; y += 5)					// Traverse all 5x5 blocks of pixels
	{
		for (int x = 2; x <= width - 2 - 1; x += 5)
		{
			int index = 0;							// Index for matrix access

			for (int i = y - 2; i <= y + 2; i++)				// Collect 5x5 block
			{
				for (int j = x - 2; j <= x + 2; j++)
				{
					redBlur += ((b.get_red(j, i) * numerator[index]) / denominator);		// Add calculated blur values to sum
					greenBlur += ((b.get_green(j, i) * numerator[index]) / denominator);
					blueBlur += ((b.get_blue(j, i) * numerator[index]) / denominator);
					index++;									// Increment index
				}
			}

			if (redBlur < 0.0)						// Constrain red, gree, blue to 0 - 255
			{
				redBlur = 0.0;
			}
			else if (redBlur > 255.0)
			{
				redBlur = 255.0;
			}
			if (greenBlur < 0.0)
			{
				greenBlur = 0.0;
			}
			else if (greenBlur > 255.0)
			{
				greenBlur = 255.0;
			}
			if (blueBlur < 0.0)
			{
				blueBlur = 0.0;
			}
			else if (blueBlur > 255.0)
			{
				blueBlur = 255.0;
			}

			for (int i = y - 2; i <= y + 2; i++)				// Traverse 5x5 block
			{
				for (int j = x - 2; j <= x + 2; j++)
				{
					b.set_red(j, i, (int) redBlur);			// Set red, green, blue values
					b.set_green(j, i, (int) greenBlur);
					b.set_blue(j, i, (int) blueBlur);
				}
			}

			index = 0;		// Reset index

			redBlur = 0.0;		// Reset blur values
			greenBlur = 0.0;
			blueBlur = 0.0;
		}
	}
}

// Returns the height of the bitmap
// INPUT: Does not take input parameters
// OUTPUT: Returns an integer
int Bitmap::get_height()
{
	return height;
}

// Returns the width of the bitmap
// INPUT: Does not take input parameters
// OUTPUT: Returns an integer
int Bitmap::get_width()
{
	return width;
}

// Get the red component of the pixel at (x, y)
// Using a zero based index
// INPUT: Takes two integers as input
// OUTPUT: Returns an integer, -1 if get unsuccessful
int Bitmap::get_red(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)				// Error check
	{
		int location;
	
		if (colorDepth == 24)
		{
			location = (width * y + x) * 3;					// RGB
		}
		else
		{
			location = (width * y + x) * 4;					// RGBs
		}

		location += redPixelOffset;						// Add offset for red component

		return (int) _data.at(location);
	}
	else
	{
		return -1;								// Denote error
	}
}

// Get the green component of the pixel at (x, y)
// Using a zero based index
// INPUT: Takes two integers as input
// OUTPUT: Returns an integer, -1 if get unsuccessful
int Bitmap::get_green(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)				// Error check
	{
		int location;
	
		if (colorDepth == 24)
		{
			location = (width * y + x) * 3;					// RGB
		}
		else
		{
			location = (width * y + x) * 4;					// RGBs
		}

		location += greenPixelOffset;						// Add offset for green component
	
		return (int) _data.at(location);
	}
	else
	{
		return -1;								// Denote error
	}
}

// Get the blue component of the pixel at (x, y)
// Using a zero based index
// INPUT: Takes two integers as input
// OUTPUT: Returns an integer, -1 if get unsuccessful
int Bitmap::get_blue(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)				// Error check
	{
		int location;

		if (colorDepth == 24)
		{
			location = (width * y + x) * 3	;				// RGB
		}
		else
		{
			location = (width * y + x) * 4;					// RGBs
		}

		location += bluePixelOffset;						// Add offset for blue component

		return (int) _data.at(location);
	}
	else
	{
		return -1;								// Denote error
	}
}

// Set the red component of the pixel at (x, y) to the specified value
// Using a zero based index
// INPUT: Takes three integer values as input
// OUTPUT: Returns an integer, -1 if set unsuccessful
int Bitmap::set_red(int x, int y, int value)
{
	if (value <= 255 && value >= 0 && x >= 0 && x < width && y >= 0 && y < height)		// Error check
	{
		int location;
	
		if (colorDepth == 24)
		{
			location = (width * y + x) * 3;					// RGB
		}
		else
		{
			location = (width * y + x) * 4;					// RGBs
		}

		location += redPixelOffset;						// Add offset for red component

		_data.at(location) = value;						// Set value in vector
		return value;
	}
	else
	{
		return -1;								// Denotes error
	}
}

// Set the green component of the pixel at (x, y) to the specified value
// Using a zero based index
// INPUT: Takes three integers as input
// OUTPUT: Returns an integer, -1 if set unsuccessful
int Bitmap::set_green(int x, int y, int value)
{
	if (value <= 255 && value >= 0 && x >= 0 && x < width && y >= 0 && y < height)		// Error check
	{
		int location;
	
		if (colorDepth == 24)
		{
			location = (width * y + x) * 3;					// RGB
		}
		else
		{
			location = (width * y + x) * 4;					// RGBs
		}

		location += greenPixelOffset;						// Add offset for green component

		_data.at(location) = value;						// Set value in vector
		return value;
	}
	else
	{
		return -1;								// Denotes error
	}
}

// Set the blue component of the pixel at (x, y) to the specified value
// Using a zero based index
// INPUT: Takes three integers as input
// OUTPUT: Returns an integer, -1 if set unsuccessful
int Bitmap::set_blue(int x, int y, int value)
{
	if (value <= 255 && value >= 0 && x >= 0 && x < width && y >= 0 && y < height)		// Error check
	{
		int location;
	
		if (colorDepth == 24)
		{
			location = (width * y + x) * 3;					// RGB
		}
		else
		{
			location = (width * y + x) * 4;					// RGBs
		}

		location += bluePixelOffset;						// Add offset for blue component

		_data.at(location) = value;						// Set value in vector
		return value;
	}
	else
	{
		return -1;								// Denotes error
	}
}

// Set height of bitmap to input value
// INPUT: Takes an integer value as input
// OUTPUT: Does not return
void Bitmap::set_height(int value)
{
	height = value;
}

// Set width of bitmap to input value
// INPUT: Takes an integer value as input
// OUTPUT: Does not return
void Bitmap::set_width(int value)
{
	width = value;
}

// Dump Pixel contents to standard out
// **USED FOR TESTING PURPOSES***
void Bitmap::dump_pixels()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << "(" << get_red(j, i) << ", " << get_green(j, i) << ", " << get_blue(j, i) << ")" << endl;
		}
	}
}

// Extraction operator overloaded to read in bitmap data from a file
// INPUT: Takes an input stream and a bitmap object
// OUTPUT: Returns an input stream
istream & operator >> (istream & in, Bitmap & b)
{
	char tag[TWO_BYTES];								// Read BM tag
	in.read(tag, TWO_BYTES);

	if (tag[0] != 'B' && tag[1] != 'M')						// Error Check
	{
		std::cout << "Invalid bitmap tag. Must be BM! Exiting program." << endl;
		return in;
	}
	
	for (char c : tag)								// Push BM tag to header one
	{
		b._headerOne.push_back(c);
	}

	in.read((char *) & b.size, FOUR_BYTES);						// Read size in uint32_t

	char size[FOUR_BYTES];								// Convert size to char
	size[0] = b.size;
	size[1] = b.size >> 8;
	size[2] = b.size >> 16;
	size[3] = b.size >> 24;

	for (char c : size)								// Push char size to header one
	{
		b._headerOne.push_back(c);
	}

	char tempHeaderOne[8];
	in.read((char *) & tempHeaderOne, 8);						// Read remainder of header one

	for (char c : tempHeaderOne)							// Push remainder of header one
	{
		b._headerOne.push_back(c);
	}

	char headerTwoSize[FOUR_BYTES];
	in.read((char *) & headerTwoSize, FOUR_BYTES);					// Read header two size

	for (char c : headerTwoSize)							// Push header two size into header two
	{
		b._headerTwo.push_back(c);
	}
	
	in.read((char *) & b.width, FOUR_BYTES);					// Read bitmap width

	char width[FOUR_BYTES];
	width[0] = b.width;								// Convert width to char
	width[1] = b.width >> 8;
	width[2] = b.width >> 16;
	width[3] = b.width >> 24;

	for (char c : width)								// Push width to header two
	{
		b._headerTwo.push_back(c);
	}
	
	in.read((char *) & b.height, FOUR_BYTES);					// Read bitmap height

	char height[FOUR_BYTES];
	height[0] = b.height;								// Convert height to char
	height[1] = b.height >> 8;
	height[2] = b.height >> 16;
	height[3] = b.height >> 24;

	for (char c : height)								// Push height to header two
	{
		b._headerTwo.push_back(c);
	}

	int16_t colorPlanes;
	in.read((char *) & colorPlanes, TWO_BYTES);					// Read color planes

	if (colorPlanes != 1)								// Error check
	{
		std::cout << "Color planes must be 1! Exiting program." << endl;
		return in;
	}

	char tempColorPlanes[TWO_BYTES];	
	tempColorPlanes[0] = colorPlanes;						// Convert color planes to char
	tempColorPlanes[1] = colorPlanes >> 8;

	for (char c : tempColorPlanes)							// Push color planes to header two
	{
		b._headerTwo.push_back(c);
	}

	in.read((char *) & b.colorDepth, TWO_BYTES);					// Read color depth

	if (b.colorDepth != 24 && b.colorDepth != 32)					// Error check
	{
		std::cout << "Color depth must be 24 (RGB) or 32 (RGBs)! Exiting program." << endl;
		return in;
	}

	char tempColorDepth[TWO_BYTES];
	tempColorDepth[0] = b.colorDepth;						// Convert color depth to char
	tempColorDepth[1] = b.colorDepth >> 8;

	for (char c : tempColorDepth)							// Push color depth to header two
	{
		b._headerTwo.push_back(c);
	}

	if (b.colorDepth == 24)								// Check color depth
	{
		b.pixelPadding = b.width % 4;						// Calculate padding
	}
	else
	{
		b.pixelPadding = 0;							// Set padding to zero
	}

	in.read((char *) & b.compressionMode, FOUR_BYTES);				// Read compression mode

	if (b.compressionMode != 0 && b.compressionMode != 3)				// Error check
	{
		std::cout << "Compression mode must be 0 or 3! Exiting program." << endl;
		return in;
	}

	char tempCompressionMode[FOUR_BYTES];
	tempCompressionMode[0] = b.compressionMode;					// Convert compression mode to char
	tempCompressionMode[1] = b.compressionMode >> 8;
	tempCompressionMode[2] = b.compressionMode >> 16;
	tempCompressionMode[3] = b.compressionMode >> 24;

	for (char c : tempCompressionMode)						// Push compression mode to header two
	{
		b._headerTwo.push_back(c);
	}

	char tempHeaderTwo[20];
	in.read((char *) & tempHeaderTwo, 20);						// Read remainder of header two

	for (char c : tempHeaderTwo)							// Push remainder of header two to header two
	{
		b._headerTwo.push_back(c);
	}

	if (b.compressionMode == 0)							// RGB
	{
		b.redPixelOffset = 2;							// Set pixel offsets
		b.greenPixelOffset = 1;
		b.bluePixelOffset = 0;
	}
	else										// RGBs
	{
		uint32_t redMask;
		in.read((char *) & redMask, FOUR_BYTES);				// Read in red mask as int

		char redMaskChars[4];							// Convert red mask to char
		redMaskChars[0] = redMask;
		redMaskChars[1] = redMask >> 8;
		redMaskChars[2] = redMask >> 16;
		redMaskChars[3] = redMask >> 24;

		for (int i = 0; i < 4; i++)
		{
			if (redMask == 255)
			{
				b.redPixelOffset = i;					// Determine red offset
			}
			redMask /= 256;
			b._headerThree.push_back(redMaskChars[i]);			// Push to header three
		}

		uint32_t greenMask;
		in.read((char *) & greenMask, FOUR_BYTES);				// Read in green mask as int
	
		char greenMaskChars[4];							// Convert green mask to char
		greenMaskChars[0] = greenMask;
		greenMaskChars[1] = greenMask >> 8;
		greenMaskChars[2] = greenMask >> 16;
		greenMaskChars[3] = greenMask >> 24;

		for (int i = 0; i < 4; i++)
		{
			if (greenMask == 255)
			{
				b.greenPixelOffset = i;					// Determine green offset
			}
			greenMask /= 256;
			b._headerThree.push_back(greenMaskChars[i]);			// Push to header three
		}

		uint32_t blueMask;
		in.read((char *) & blueMask, FOUR_BYTES);				// Read in blue mask as int

		char blueMaskChars[4];
		blueMaskChars[0] = blueMask;						// Convert blue mask to char
		blueMaskChars[1] = blueMask >> 8;
		blueMaskChars[2] = blueMask >> 16;
		blueMaskChars[3] = blueMask >> 24;

		for (int i = 0; i < 4; i++)
		{
			if (blueMask == 255)
			{
				b.bluePixelOffset = i;					// Determine blue mask offset
			}
			blueMask /= 256;
			b._headerThree.push_back(blueMaskChars[i]);			// Push to header three
		}

		char tempHeaderThree[72];
		in.read((char *) & tempHeaderThree, 72);				// Read remainder of header three

		for (char c : tempHeaderThree)						// Push remainder of header three to header three
		{
			b._headerThree.push_back(c);
		}
	}

	uint8_t temp;
	int iterations = b.size - HEADER_ONE - HEADER_TWO;				// Determine remaining characters to read
	
	if (b.compressionMode == 3)
	{
		iterations -= HEADER_THREE;						// Decrememnt for header three if necessary
	}

	for (int i = 0; i < iterations; i++)
	{
		
		in.read((char *) & temp, ONE_BYTE);					// Read character
		b._data.push_back(temp);						// Push character to pixel data
	}

	return in;									
}

// Insertion operator overloaded to write bitmap data to a file
// INPUT: Takes an output stream and a bitmap object as inputs
// OUTPUT: Returns an output stream
ostream & operator << (ostream & out, const Bitmap & b)
{
	for (char c : b._headerOne)							// Write header one
	{
		out.write((char *) & c, ONE_BYTE);
	}

	for (char c : b._headerTwo)							// Write header two
	{
		out.write((char *) & c, ONE_BYTE);
	}

	for (char c : b._headerThree)							// Write header three
	{
		out.write((char *) & c, ONE_BYTE);
	}

	for (char c : b._data)								// Write pixel data
	{
		out.write((char *) & c, ONE_BYTE);
	}

	return out;
}

Bitmap::Bitmap()									// Default constructor
{
}

Bitmap::~Bitmap()									// Destructor
{
}

Bitmap::Bitmap(const Bitmap & b)							// Copy constructor
{
	size = b.size;
	width = b.width;
	height = b.height;
	colorDepth = b.colorDepth;
	compressionMode = b.compressionMode;
	pixelPadding = b.pixelPadding;
	redPixelOffset = b.redPixelOffset;
	greenPixelOffset = b.greenPixelOffset;
	bluePixelOffset = b.bluePixelOffset;

	for (char c : b._headerOne)
	{
		_headerOne.push_back(c);
	}

	for (char c : b._headerTwo)
	{
		_headerTwo.push_back(c);
	}

	for (char c : b._headerThree)
	{
		_headerThree.push_back(c);
	}

	for (uint8_t i : b._data)
	{
		_data.push_back(i);
	}
}

Bitmap::Bitmap(Bitmap && b)								// Move constructor
{
}
