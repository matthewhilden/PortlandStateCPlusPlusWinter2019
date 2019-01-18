#include <iostream>
#include <ostream>
#include <vector>
#include <cstring>

using namespace std;

const int ONE_BYTE = 1;				// For reading one byte
const int TWO_BYTES = 2;			// For reading two bytes
const int FOUR_BYTES = 4;			// For reading four bytes

const int HEADER_ONE = 14;			// Header one size
const int HEADER_TWO = 40;			// Header two size
const int HEADER_THREE = 84;			// Header three size

class Bitmap
{
	private:
		
		int size;			// Size of bitmap
		int width;			// Width of bitmap in pixels
		int height;			// Height of bitmap in pixels
		int colorDepth;			// Color depth of bitmap
		int compressionMode;		// The compression mode of the bitmap
		int pixelPadding;		// Pixel padding if using RGB color depth
		int redPixelOffset;		// Offset of pixel's red value
		int greenPixelOffset;		// Offset of pixel's green value
		int bluePixelOffset;		// Offset of pixel's blue value

		vector<char> _headerOne;		// First file header
		vector<char> _headerTwo;		// Second file header
		vector<char> _headerThree;		// Third file header
		vector<uint8_t> _data;			// Pixel data
		
		friend istream & operator >> (istream & in, Bitmap & b);		// For reading bitmap data
    		friend ostream & operator << (ostream & out, const Bitmap & b);		// For writing bitmap data

	public:

    		Bitmap();				// Default constructor
    		Bitmap(const Bitmap&);			// Copy constructor
    		Bitmap operator=(const Bitmap&);	// Assignment operator
   		Bitmap(Bitmap&&);			// Move constructor
    		~Bitmap();				// Destructor

		int get_height();			// Get height of bitmap
		int get_width();			// Get width of bitmap

		int get_red(int, int);			// Get red pixel (x, y) value
		int get_green(int, int);		// Get green pixel (x, y) value
		int get_blue(int, int);			// Get blue pixel (x, y) value

		void set_red(int, int, int);		// Set red pixel (x, y) value
		void set_green(int, int, int);		// Set green pixel (x, y) value
		void set_blue(int, int, int);		// Set blue pixel (x, y) value

		void dump_pixels();			// **USED FOR TESTING**
};


void cellShade(Bitmap & b);
void grayscale(Bitmap & b);
void pixelate(Bitmap & b);
void blur(Bitmap & b);
/*
void rot90(Bitmap& b);
void rot180(Bitmap& b);
void rot270(Bitmap& b);
void flipv(Bitmap& b);
void fliph(Bitmap& b);
void flipd1(Bitmap& b);
void flipd2(Bitmap& b);
void scaleUp(Bitmap& b);
void scaleDown(Bitmap& b);
*/
