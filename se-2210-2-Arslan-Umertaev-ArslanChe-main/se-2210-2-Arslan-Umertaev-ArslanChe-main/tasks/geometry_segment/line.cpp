#include "line.h"

#include "segment.h"
namespace geometry {

Line::Line() : start_(), end_() {
}

Line::Line(Point start, Point end) : start_(start), end_(end) {
}

int64_t Line::GetA() const {
    return end_.GetY() - start_.GetY();
}

int64_t Line::GetB() const {
    return start_.GetX() - end_.GetX();
}

int64_t Line::GetC() const {
    return end_.GetX() * start_.GetY() - start_.GetX() * end_.GetY();
}

double Line::Distance(Point point) const {
    double a = static_cast<double>(GetA());
    double b = static_cast<double>(GetB());
    double c = static_cast<double>(GetC());
    double numerator = std::abs(a * static_cast<double>(point.GetX()) + b * static_cast<double>(point.GetY()) + c);
    double denominator = std::sqrt(a * a + b * b);
    return numerator / denominator;
}

Line& Line::Move(const Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

bool Line::ContainsPoint(const Point& point) const {
    return GetA() * point.GetX() + GetB() * point.GetY() + GetC() == 0;
}
bool Line::CrossesSegment(const Segment& segment) const {

    auto product_start_seg_line = VectorMult(segment.GetStart() - start_, end_ - segment.GetStart());
    auto product_end_seg_line = VectorMult(segment.GetEnd() - start_, end_ - segment.GetEnd());

    return product_start_seg_line * product_end_seg_line <= 0;
}

Line* Line::Clone() const {
    return new Line(*this);
}

}  // namespace geometry
