#include "SetOfSegments.h"

SetOfSegments::Segment::Segment(sf::Vector2f a, sf::Vector2f b): a(a), b(b) {}

bool SetOfSegments::intersect(Ray ray, sf::Vector2f& p) {
    bool fl = false;
    float anst;
    for (int i = 0; i < (int)segments.size(); ++i) {
        Segment s = segments[i];
        float t, l;
        if (LinEqSystem2::solve(ray.v, s.a - s.b, s.a - ray.p, t, l) && 0 <= t && 0 <= l && l <= 1) {
            if (!fl ||t < anst) {
                fl = true;
                anst = t;
            }
        }
    }
    if (!fl) return false;
    p = ray.p + ray.v * anst;

    return true;
}
