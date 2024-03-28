#include "segment.h"

#include "point.h"
namespace geometry {

Segment::Segment() : Segment(Point(0, 0), Point(0, 0)) {
}

Segment::Segment(Point start, Point end) : start_(start), end_(end) {
}

Point Segment::GetStart() const {
    return start_;
}

Point Segment::GetEnd() const {
    return end_;
}

double Segment::Distance(Point pt) const {
    double a = static_cast<double>(start_.GetY() - end_.GetY());
    double b = static_cast<double>(end_.GetX() - start_.GetX());
    double c = static_cast<double>((start_.GetX() - end_.GetX()) * start_.GetY() +
                                   (end_.GetY() - start_.GetY()) * start_.GetX());
    double pt_x = static_cast<double>(pt.GetX());
    double pt_y = static_cast<double>(pt.GetY());
    double ans = (a * pt_x + b * pt_y + c) / sqrt(a * a + b * b);
    return std::fabs(ans);
}
bool Segment::Degenerate() const {
    return start_.GetX() == end_.GetX() && start_.GetY() == end_.GetY();
}

Segment& Segment::Move(const Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

bool Segment::ContainsPoint(const Point& point) const {
    return point.CrossesSegment(*this);
}
Segment* Segment::Clone() const {
    return new Segment(*this);
}

bool Segment::CrossesSegment(const Segment& segment) const {
    Vector stst = segment.GetStart() - start_;
    Vector sten = end_ - segment.GetStart();
    Vector enst = segment.GetEnd() - start_;
    Vector enen = end_ - segment.GetEnd();
    int64_t vector_mult1 = VectorMult(stst, sten);
    int64_t vector_mult2 = VectorMult(enst, enen);
    int64_t vector_mult3 = VectorMult(sten, -enen);
    int64_t vector_mult4 = VectorMult(-stst, enst);

    if (vector_mult1 * vector_mult2 > 0 || vector_mult3 * vector_mult4 > 0) {
        return false;
    }
    if (vector_mult1 * vector_mult2 < 0 && vector_mult3 * vector_mult4 < 0) {
        return true;
    }

    if (GetStart().CrossesSegment(segment) || GetEnd().CrossesSegment(segment) ||
        segment.GetStart().CrossesSegment(*this) || segment.GetEnd().CrossesSegment(*this)) {
        return true;
    }
    return false;
}

};  // namespace geometry