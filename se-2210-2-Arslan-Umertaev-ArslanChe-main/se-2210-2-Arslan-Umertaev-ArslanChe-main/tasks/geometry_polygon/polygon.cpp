#include "polygon.h"

#include "point.h"
#include "segment.h"
namespace geometry {
Polygon::Polygon() : points_(std::vector<Point>{}), num_points_(0) {
}
Polygon::Polygon(std::vector<Point> points) : points_(points), num_points_(points.size()) {
}
Polygon& Polygon::Move(const Vector& vector) {
    for (auto& point : points_) {
        point.Move(vector);
    }
    return *this;
}

bool Polygon::ContainsPoint(const Point& point) const {
    int64_t ans = 0;
    if (GetPoints().empty()) {
        return false;
    }
    for (size_t i = 0; i < GetPoints().size(); ++i) {
        const Point p1 = GetPoints()[i];
        const Point p2 = GetPoints()[(i + 1) % GetPoints().size()];

        if (Segment(p1, p2).ContainsPoint(point)) {
            return true;
        }
        if ((p1.GetY() > point.GetY()) != (p2.GetY() > point.GetY()) &&
            point.GetX() < (p2.GetX() - p1.GetX()) * (point.GetY() - p1.GetY()) / (p2.GetY() - p1.GetY()) + p1.GetX()) {
            ++ans;
        }
    }
    return (ans % 2 == 1);
}
bool Polygon::CrossesSegment(const Segment& segment) const {

    if (GetPoints().empty()) {
        return false;
    }
    if (Segment(GetPoints()[0], GetPoints()[GetPoints().size() - 1]).CrossesSegment(segment)) {
        return true;
    }
    for (size_t i = 0; i < GetPoints().size() - 1; ++i) {
        auto dop = Segment(GetPoints()[i], GetPoints()[i + 1]);
        if (dop.CrossesSegment(segment)) {
            return true;
        }
    }
    return false;
}

Polygon* Polygon::Clone() const {
    return new Polygon(*this);
}

}  // namespace geometry