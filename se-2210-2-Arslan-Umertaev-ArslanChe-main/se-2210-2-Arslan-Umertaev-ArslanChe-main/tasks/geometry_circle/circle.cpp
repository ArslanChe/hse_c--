#include "circle.h"

#include "line.h"
#include "point.h"
#include "segment.h"
namespace geometry {

Circle::Circle() : Circle(Point(0, 0), 0) {
}

Circle::Circle(Point point, int64_t radius) : centre_(point), radius_(radius) {
}

Circle& Circle::Move(const Vector& vector) {
    centre_.Move(vector);
    return *this;
}
Circle* Circle::Clone() const {
    return new Circle(*this);
}

int64_t Circle::GetRadius() const {
    return radius_;
}

Point Circle::GetCenter() const {
    return centre_;
}

bool Circle::ContainsPoint(const Point& point) const {
    return Length(Vector(GetCenter() - point)) <= static_cast<double>(GetRadius());
}

bool Circle::CrossesSegment(const Segment& segment) const {
    Vector dop1 = segment.GetStart() - GetCenter();
    Vector dop2 = segment.GetEnd() - GetCenter();
    Line dop_line(segment.GetStart(), segment.GetEnd());
    Vector dop = segment.GetEnd() - segment.GetStart();

    if (Length(dop2) == static_cast<double>(GetRadius()) || Length(dop1) == static_cast<double>(GetRadius())) {
        return true;
    }
    if (Length(dop2) < static_cast<double>(GetRadius()) && Length(dop1) < static_cast<double>(GetRadius())) {
        return false;
    }
    if (Length(dop2) < static_cast<double>(GetRadius()) || Length(dop1) < static_cast<double>(GetRadius())) {
        return true;
    }
    if (dop_line.Distance(GetCenter()) - static_cast<double>(GetRadius()) > std::numeric_limits<double>::epsilon()) {
        return false;
    }
    if (sqrt(Length(dop2) - dop_line.Distance(GetCenter()) * dop_line.Distance(GetCenter())) - Length(dop) >
        std::numeric_limits<double>::epsilon()) {
        return false;
    }
    return true;
}

}  // namespace geometry