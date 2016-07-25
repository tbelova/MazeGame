#include "SetOfSegments.h"

SetOfSegments::Segment::Segment(): a(sf::Vector2f(0, 0)), b(sf::Vector2f(0, 0)) {}

SetOfSegments::Segment::Segment(sf::Vector2f a, sf::Vector2f b): a(a), b(b) {}

SetOfSegments::HZ SetOfSegments::intersect(sf::Vector2f p, sf::Vector2f v) {
    bool fl = false;
    float anst;
    HZ hz;
    for (int i = 0; i < (int)segments.size(); ++i) {
        Segment s = segments[i];
        float t, l;
        if (LinEqSystem2::solve(v, s.a - s.b, s.a - p, t, l) && 0 <= t && 0 <= l && l <= 1) {
            if (!fl ||t < anst) {
                fl = true;
                anst = t;
                hz.segment = s;
            }
        }
    }
    if (!fl) {
        hz.intersect = false;
    } else {
        hz.point = p + v * anst;
        hz.intersect = true;
    }

    return hz;
}

void SetOfSegments::Add(Segment s) {
    segments.push_back(s);
}
