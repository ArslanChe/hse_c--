#include "ray.h"

#include "line.h"
#include "segment.h"
namespace geometry {

Ray::Ray() : Ray(Point(0, 0), Point(0, 0)) {
}

Ray::Ray(Point start, Point end) : start_(start), end_(end) {
}

Ray& Ray::Move(const Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}
Ray* Ray::Clone() const {
    return new Ray(*this);
}

Point Ray::GetStart() const {
    return start_;
}

Point Ray::GetEnd() const {
    return end_;
}

bool Ray::ContainsPoint(const Point& point) const {
    if (Segment(start_, end_).ContainsPoint(point)) {
        return true;
    }
    if (!Line(GetStart(), GetEnd()).ContainsPoint(point)) {
        return false;
    }
    return Length(point - end_) <= Length(point - start_);
}

bool Ray::CrossesSegment(const Segment& segment) const {
    auto this_seg = Segment(GetStart(), GetEnd());
    if (ContainsPoint(segment.GetStart()) || ContainsPoint(segment.GetEnd())) {
        return true;
    }
    if (this_seg.CrossesSegment(segment)) {
        return true;
    }
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
    return false;
}
}  // namespace geometry