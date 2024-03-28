#include "chocolate.h"

bool CanBreakSlices(int height, int width, int slices_amount) {
    return (height * width > slices_amount) && (slices_amount % height == 0 || slices_amount % width == 0);
}