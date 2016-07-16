#ifndef __SEGMENT__
    #define __SEGMENT__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>

    class Segment {
    public:
        sf::Vector2f a, b;
        Segment(sf::Vector2f a, sf::Vector2f b): a(a), b(b) {}
    };

    class Equality {
    private:
        sf::Vector2f a, b, c;
        float cross_product(sf::Vector2f v1, sf::Vector2f v2) {
            return v1.x * v2.y - v1.y * v2.x;
        }

    public:
        Equality(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c): a(a), b(b), c(c) {}
        bool solve(float& t, float& l) {
            if (cross_product(a, b) != 0) {
                t = cross_product(c, b) / cross_product(a, b);
                l = cross_product(c, a) / cross_product(b, a);
            } else {
                return false;
            }

            return true;
        }

    };

    class Ray {
    private:
        sf::Vector2f a, b;

    public:
        Ray(sf::Vector2f a, sf::Vector2f b): a(a), b(b) {}

        bool intersect(std::vector<Segment> &segments, sf::Vector2f& p) {

            bool fl = false;
            float anst;
            for (int i = 0; i < (int)segments.size(); ++i) {
                Segment s = segments[i];
                Equality q(b - a, s.a - s.b, s.a - a);
                float t, l;
                if (q.solve(t, l) && 0 <= t && 0 <= l && l <= 1) {
                    if (t < anst || !fl) {
                        fl = true;
                        anst = t;
                    }
                }
            }
            if (!fl) return false;
            p = a + anst * (b - a);
            return true;
        }


    };


#endif // __SEGMENT__
