#ifndef __LIGHT__
    #define __LIGHT__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Consts.h"
    #include "Wall.h"
    #include "DSU.h"
    #include "Maze.h"
    #include "Character.h"
    #include "Manager.h"
    #include "Updatable.h"
    #include "SetOfSegments.h"
    #include "Smth.h"
    #include "Monster.h"
    #include "Light.h"


    class Light {
    private:
        SetOfSegments segments;
        vector<sf::Vector2f> points, shape;
        sf::Vector2f center;
        sf::Vector2f ViewPos, ViewSize;

        bool inWindow(sf::Vector2f p) {
            return p.x >= ViewPos.x && p.y >= ViewPos.y &&
                   p.x <= ViewPos.x + ViewSize.x && p.y <= ViewPos.y + ViewSize.y;
        }

    public:

        void setView(sf::Vector2f pos, sf::Vector2f sz) {
            ViewPos = pos;
            ViewSize = sz;
        }

        void setWalls(vector<Wall>& walls) {
            segments.clear();
            points.clear();

            float eps = 0.1;
            sf::Vector2f ex(eps, 0), ey(0, eps);

            for (auto wall: walls) {
                sf::Vector2f pos = wall.getPos();

                vector<sf::Vector2f> p;
                p.push_back(pos);
                p.push_back(pos + sf::Vector2f(WallSize, 0));
                p.push_back(pos + sf::Vector2f(WallSize, WallSize));
                p.push_back(pos + sf::Vector2f(0, WallSize));
                //p.push_back(p[0]);

                bool ok0 = false;
                bool ok1 = false;
                bool ok2 = false;
                bool ok3 = false;
                if (inWindow(p[0]) || inWindow(p[1])) {
                    segments.Add(p[0] + ey, p[1] + ey);
                    if (!ok0) points.push_back(p[0] + ey + ex), ok0 = true;
                    if (!ok1) points.push_back(p[1] + ey - ex), ok1 = true;
                }
                if (inWindow(p[1]) || inWindow(p[2])) {
                    segments.Add(p[1] - ex, p[2] - ex);
                    if (!ok1) points.push_back(p[1] + ey - ex), ok1 = true;
                    if (!ok2) points.push_back(p[2] - ey - ex), ok2 = true;
                }
                if (inWindow(p[2]) || inWindow(p[3])) {
                    segments.Add(p[2] - ey, p[3] - ey);
                    if (!ok2) points.push_back(p[2] - ey - ex), ok2 = true;
                    if (!ok3) points.push_back(p[3] - ey + ex), ok3 = true;
                }
                if (inWindow(p[3]) || inWindow(p[0])) {
                    segments.Add(p[3] + ex, p[0] + ex);
                    if (!ok3) points.push_back(p[3] - ey + ex), ok3 = true;
                    if (!ok0) points.push_back(p[0] + ey + ex), ok0 = true;
                }



/*

                for (int i = 0; i < 4; ++i) {
                    if (inWindow(p[i]) || inWindow(p[i + 1])) {
                        segments.Add(p[i], p[i + 1]);

                        points.push_back(p[i]);
                        points.push_back(p[i + 1]);

                        sf::Vector2f v = p[i + 1] - p[i];
                        sf::Vector2f eps = v / Length(v) * (float)0.1;

                        points.push_back(p[i] + eps);
                        points.push_back(p[i] - eps);
                        points.push_back(p[i + 1] + eps);
                        points.push_back(p[i + 1] - eps);
                    }

                }
*/
            }

            segments.unique(eps);

            vector<sf::Vector2f> p;
            p.push_back(ViewPos + sf::Vector2f(-WallSize, -WallSize));
            p.push_back(ViewPos + sf::Vector2f(0, ViewSize.y) + sf::Vector2f(-WallSize, +WallSize));
            p.push_back(ViewPos + ViewSize + sf::Vector2f(+WallSize, +WallSize));
            p.push_back(ViewPos + sf::Vector2f(ViewSize.x, 0) + sf::Vector2f(+WallSize, -WallSize));
            p.push_back(p[0]);

            for (int i = 0; i < 4; ++i) {
                segments.Add(p[i], p[i + 1]);

         /*       points.push_back(p[i]);

                sf::Vector2f v = p[i + 1] - p[i];
                sf::Vector2f eps = v / Length(v) * (float)0.1;

                points.push_back(p[i] + eps);
                points.push_back(p[i] - eps);*/

            }

            for (auto seg: segments) {
                auto a = seg.a;
                auto b = seg.b;
                auto v = b - a;
                auto eps = v / Length(v) * (float)0.1;
                points.push_back(a);
                points.push_back(b);
                points.push_back(a + eps);
                points.push_back(b + eps);
                points.push_back(a - eps);
                points.push_back(b - eps);
            }

        }


        void setCenter(sf::Vector2f pos) {
            center = pos;
        }

        void makeLight(sf::RenderTarget &target) {

            /*sf::RectangleShape rect(sf::Vector2f(0.1, 0.1));
            rect.setOrigin(0.05, 0.05);
            rect.setFillColor(sf::Color::Yellow);
            for (auto s: segments) {
                if (s.a.x == s.b.x) {
                    rect.setPosition(s.a);
                    target.draw(rect);
                    rect.setPosition(s.b);
                    target.draw(rect);
                }
            }

            return;*/

            shape.clear();
            for (auto p: points) {
                shape.push_back(segments.intersect(center, p - center).point);
            }

            vector<sf::Vector2f> rays;
            for (auto point: shape) {
                rays.push_back(point - center);
            }
            sort(rays.begin(), rays.end(), cmpByAngle<float>);
            rays.push_back(rays[0]);


            for (int i = 0; i < (int)rays.size() - 1; ++i) {
                if (rays[i] == rays[i + 1]) continue;

                sf::VertexArray triangle(sf::Triangles, 3);
                triangle[0].position = sf::Vector2f(center);
                triangle[1].position = sf::Vector2f(center + rays[i]);
                triangle[2].position = sf::Vector2f(center + rays[i + 1]);

                triangle[0].color = sf::Color::White;
                triangle[1].color = sf::Color::White; //Cyan;
                triangle[2].color = sf::Color::White;//Magenta;

                target.draw(triangle);
            }

            int AMOUNT_OF_POINTS = 90;
            float PI = 3.1415926;
            float alpha = 2 * PI / AMOUNT_OF_POINTS;

            sf::RenderStates states;
            states.blendMode = sf::BlendMultiply;

            float radius = ViewSize.x / (float)1.4;

            for (int i = 0; i < AMOUNT_OF_POINTS; ++i) {
                sf::VertexArray triangle(sf::Triangles, 3);

                sf::Vector2f dir(sin(alpha * i), cos(alpha * i));
                sf::Vector2f nextDir(sin(alpha * (i + 1)), cos(alpha * (i + 1)));

                dir *= radius;
                nextDir *= radius;

                triangle[0].position = sf::Vector2f(center);
                triangle[1].position = sf::Vector2f(center + dir);
                triangle[2].position = sf::Vector2f(center + nextDir);

                triangle[0].color = sf::Color(150, 120, 100);
                triangle[1].color = sf::Color::Black;
                triangle[2].color = sf::Color::Black;

                target.draw(triangle, states);
            }


            /*sf::RectangleShape rect(sf::Vector2f(0.1, 0.1));
            rect.setOrigin(0.05, 0.05);
            rect.setFillColor(sf::Color::Yellow);
            for (auto s: shape) {
            //for (int i = 0; i < 500; ++i) {
                rect.setPosition(s);
                target.draw(rect);
            }*/



        }

    };


#endif // __LIGHT__
