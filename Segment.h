#ifndef __SEGMENT__
    #define __SEGMENT__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>

    class Segment {
    public:
        sf::Vector2f a, b;
        Segment(sf::Vector2f a, sf::Vector2f b): a(a), b(b) {}
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

                sf::Vector2f c = b - a, d = s.a - s.b, e = s.a - a;

                float l, t;

                if (d.x * c.y != d.y * c.x) {
                    l = (e.x * c.y - e.y * c.x) / (d.x * c.y - d.y * c.x);
                    if (c.x != 0)
                        t = (e.x + l * d.x) / c.x;
                    else
                        t = (e.y + l * d.y) / c.y;
                    if (0 <= l && l <= 1) {
                        if (t >= 0 && (t < anst || !fl)) {
                            fl = true;
                            anst = t;
                        }
                    }

                } else if (e.x * c.y == e.y * c.x) {
                    if (c.x != 0)
                        t = std::min(e.x, e.x + d.x) / c.x;
                    else
                        t = std::min(e.y, e.y + d.y) / c.y;
                    if (t >= 0 && (t < anst || !fl)) {
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
