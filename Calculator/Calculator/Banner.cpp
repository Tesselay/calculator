#include "Banner.h"

class Banner {
private:
	// Declaration
	std::string finishedBanner;
	std::string name;
	std::string possibleSigns;
	int offsetX;
	int height;
	int borderThiccness;


	// Get length of string
	int lengthOf(std::string x) {
		int length = x.size();

		return length;
	}

	// Gets random ID from possibleSigns
	int rngID(std::string signs) {
		int randomID;
		int length = lengthOf(signs);

		// Generate random number
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> randInt(0, length - 1); // distribution in range [0, 3]
		randomID = randInt(rng);

		return randomID;
	}

	// Get corresponding char to ID
	char IDtoChar(int ID, std::string signs) {
		char character = signs[ID];
		//DEBUG("ID", ID)
		return character;
	}

	// Get random char
	char randomChar() {
		return(IDtoChar(rngID(possibleSigns), possibleSigns));
	}

	// Determine width of banner
	int widthOfBanner(int lengthOfName, int offset) {
		int width = lengthOfName + (offset * 2) + 2;

		return width;
	}

	// Check height to determine if its on the top/bottom or in between
	bool topOrBottom(int currentHeight, int maxHeight, int borderthiccness = 1) {
		int bottomRow = 1;


		if (currentHeight > maxHeight - borderthiccness || currentHeight < bottomRow + borderthiccness)
			return true;
		else {
			return false;
		}
	}

	// Check if current middle row is the row for name
	bool middleRow(int currentHeight, int maxHeight) {
		int rowName;

		// Determine row for the name depending on if its an even or odd number
		if (maxHeight % 2 == 1) {
			rowName = maxHeight / 2 + 1;
		}
		else {
			rowName = (maxHeight / 2) + 1;
		}

		//DEBUG("rowName", rowName)

		if (currentHeight == rowName) {
			return true;
		}
		else {
			return false;
		}
	}


	// Create Row
	std::string createRow(int width, int maxWidth, int height, bool topOrBottom, bool middleRow, int borderThiccness) {
		std::string signs = possibleSigns;
		std::string row;

		// Top and Bottom
		if (topOrBottom) {
			for (int x = width; x != 0; x = x - 1) {
				row = row + (randomChar());
			}
		}

		// in between
		else {

			// row for name
			if (middleRow) {

				for (int x = width; x != 0; x = x - 1) {
					if (x > (maxWidth - borderThiccness) || x < (borderThiccness + 1)) { // first and last including border
						//DEBUG("x", x)
						row = row + (randomChar());
					}
					else if (x == (maxWidth - offsetX) - 1) {
						row = row + name;
						x = x - (lengthOf(name) - 1);
					}
					else {
						row = row + " ";
					}
				}
			}

			// rows in between
			else {
				for (int x = width; x != 0; x = x - 1) {
					if (x > (maxWidth - borderThiccness) || x < (borderThiccness + 1)) { // first and last including border
						//DEBUG("x", x)
						row = row + (randomChar());
					}
					else {
						row = row + " ";
					}
				}
			}
		}

		//OUTEND(height)
		return row;
	}

	// Construct the banner out of rows
	std::string constructBanner(int maxWidth, int maxHeight, int borderThiccness) {
		std::string banner;
		std::string row;
		int currentHeight = maxHeight;
		int currentWidth = maxWidth;

		// Height
		for (int y = currentHeight; y != 0; y = y - 1) {
			//DEBUG("Current Height", y)
			row = createRow(currentWidth, maxWidth, y, topOrBottom(y, maxHeight, borderThiccness), middleRow(y, maxHeight), borderThiccness);
			//std::cout << "Row " << y << ": " << row << std::endl;
			row += "\n";
			banner += row;
			row = "";
		}

		//DEBUG("Banner", banner)
		return banner;
	}


public:

	// Construct the object
	Banner(std::string name, std::string possibleSigns, int offsetX, int height, int borderThiccness) {
		this->name = name;
		this->possibleSigns = possibleSigns;
		this->offsetX = offsetX;
		this->height = height;
		this->borderThiccness = borderThiccness;
	}


	// DEPRECATED
	//void constructor(std::string name, std::string possibleSigns, int offsetX, int height, int borderThiccness) {


	//	this->name = name;
	//	this->possibleSigns = possibleSigns;
	//	this->offsetX = offsetX;
	//	this->height = height;
	//	this->borderThiccness = borderThiccness;
	//}

	// Creates Banner (main function)
	std::string createBanner() {


		finishedBanner = constructBanner((widthOfBanner(lengthOf(name), offsetX)), height, borderThiccness);

		return finishedBanner;
	}

	// DEBUG-LOG stored values
	void debug() {
		std::string dash = "------------------------------------------------"
			OUT("\n\n\n\n\n\n")
			OUTEND("            DEBUG-LOG            ")
			OUTEND(dash)
			DEBUG("Name", name)
			DEBUG("Length of Name", lengthOf(name))
			OUTEND(dash)

			DEBUG("Possible Signs", possibleSigns)
			DEBUG("Length of possible Signs", lengthOf(possibleSigns))
			OUTEND(dash)

			DEBUG("Finished Banner", finishedBanner)
			DEBUG("Length of finished Banner", lengthOf(finishedBanner))
			OUTEND(dash)

			DEBUG("OffsetX", offsetX)
			DEBUG("Width of Banner", widthOfBanner(lengthOf(name), offsetX))
			OUTEND(dash)

			DEBUG("Random Number Roll", rngID(possibleSigns))
			DEBUG("IDtoChar [Char]", IDtoChar(rngID(possibleSigns), possibleSigns))
			OUTEND(dash)

			DEBUG("Random Char", randomChar())
			OUTEND(dash)
	}
};