#include "segment.h"

namespace geometry {
Segment::Segment() : start_(0, 0), end_(0, 0) {
}

Segment::Segment(Point start, Point end) : start_(start), end_(end) {
}

Point Segment::GetStart() const {
    return start_;
}

Point Segment::GetEnd() const {
    return end_;
}
}  // namespace geometry
