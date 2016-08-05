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

void SetOfSegments::Add(sf::Vector2f a, sf::Vector2f b) {
    segments.push_back(Segment(a, b));
}

void SetOfSegments::clear() {
    segments.clear();
}

std::vector<SetOfSegments::Segment>::iterator SetOfSegments::begin() {
    return segments.begin();
}

std::vector<SetOfSegments::Segment>::iterator SetOfSegments::end() {
    return segments.end();
}

bool cmpByX(SetOfSegments::Segment a, SetOfSegments::Segment b) {
    if (a.a.x == b.a.x) return a.a.y < b.a.y;
    return a.a.x < b.a.x;
}

bool cmpByY(SetOfSegments::Segment a, SetOfSegments::Segment b) {
    if (a.a.y == b.a.y) return a.a.x < b.a.x;
    return a.a.y < b.a.y;
}

void SetOfSegments::unique(float eps) {
    vector<SetOfSegments::Segment> horizontal, vertical;
    for (auto s: segments) {
        if (s.a.x == s.b.x) vertical.push_back(s);
        else horizontal.push_back(s);
    }

    for (int i = 0; i < (int)vertical.size(); ++i) {
        if (vertical[i].a.y > vertical[i].b.y)
            swap(vertical[i].a, vertical[i].b);
    }
    for (int i = 0; i < (int)horizontal.size(); ++i) {
        if (horizontal[i].a.x > horizontal[i].b.x)
            swap(horizontal[i].a, horizontal[i].b);
    }

    sort(vertical.begin(), vertical.end(), cmpByX);
    sort(horizontal.begin(), horizontal.end(), cmpByY);

    sf::Vector2f ex(eps, 0), ey(0, eps);

    vector<SetOfSegments::Segment> localVertical, localHorizontal;
    for (int i = 0; i < (int)vertical.size(); ++i) {
        if (i > 0 && Equal(vertical[i - 1].a.x, vertical[i].a.x) && Equal(vertical[i - 1].b.y, vertical[i].a.y)) {
            localVertical.back().b = vertical[i].b;
        } else {
            localVertical.push_back(vertical[i]);
        }
    }
    for (int i = 0; i < (int)horizontal.size(); ++i) {
        if (i > 0 && Equal(horizontal[i - 1].a.y, horizontal[i].a.y) && Equal(horizontal[i - 1].b.x, horizontal[i].a.x)) {
            localHorizontal.back().b = horizontal[i].b;
        } else {
            localHorizontal.push_back(horizontal[i]);
        }
    }

    segments.clear();
    for (auto s: localVertical) {
        segments.push_back(SetOfSegments::Segment(s.a + ey, s.b - ey));
    }
    for (auto s: localHorizontal) {
        segments.push_back(SetOfSegments::Segment(s.a + ex, s.b - ex));
    }
}

