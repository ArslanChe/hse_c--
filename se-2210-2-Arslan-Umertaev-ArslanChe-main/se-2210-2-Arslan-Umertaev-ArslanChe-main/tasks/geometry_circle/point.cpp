#include "point.h"

#include "segment.h"
namespace geometry {

int64_t Point::GetX() const {
    return x_coord_;
}

int64_t Point::GetY() const {
    return y_coord_;
}

void Point::SetX(int64_t x) {
    x_coord_ = x;
}

void Point::SetY(int64_t y) {
    y_coord_ = y;
}

Point& Point::Move(const Vector& vector) {
    x_coord_ += vector.GetX();
    y_coord_ += vector.GetY();
    return *this;
}

bool Point::ContainsPoint(const Point& point) const {
    return x_coord_ == point.x_coord_ && y_coord_ == point.y_coord_;
}

bool Point::CrossesSegment(const Segment& segment) const {
    //    int64_t dxs = x_coord_ - segment.GetStart().GetX();
    //    int64_t dys = y_coord_ - segment.GetStart().GetY();
    //    int64_t dxe = x_coord_ - segment.GetEnd().GetX();
    //    int64_t dye = y_coord_ - segment.GetEnd().GetY();
    int64_t mx = x_coord_;
    int64_t my = y_coord_;
    auto ax = segment.GetStart().GetX();
    auto ay = segment.GetStart().GetY();
    auto bx = segment.GetEnd().GetX();
    auto by = segment.GetEnd().GetY();
    if ((mx - ax) * (by - ay) == (bx - ax) * (my - ay)) {
        if (std::min(ay, by) <= my && (std::max(ay, by) >= my) && std::min(ax, bx) <= mx && std::max(ax, bx) >= mx) {
            return true;
        }
    }
    return false;
}

Point* Point::Clone() const {
    return new Point(x_coord_, y_coord_);
}

Vector Point::operator-(Point other) const {
    return Vector(x_coord_ - other.x_coord_, y_coord_ - other.y_coord_);
}
Point::Point(int64_t x, int64_t y) : x_coord_(x), y_coord_(y) {
}
}  // namespace geometry
