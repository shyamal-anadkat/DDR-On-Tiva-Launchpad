#include "arrow.h"

// Converts an integer between 0-3 into an arrow_dir_t
// If invalid integer is passed in this function will return 4
arrow_dir_t convert_int_to_arrow(uint16_t integer) {
	switch(integer) {
		case 0:
			return ARROW_DIR_UP;
		case 1:
			return ARROW_DIR_DOWN;
		case 2: 
			return ARROW_DIR_LEFT;
		case 3:
			return ARROW_DIR_RIGHT;
		default:
			return 4;
	}
}