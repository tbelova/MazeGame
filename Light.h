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

            for (auto wall: walls) {
                sf::Vector2f pos = wall.getPos();

                vector<sf::Vector2f> p;
                p.push_back(pos);
                p.push_back(pos + sf::Vector2f(WallSize, 0));
                p.push_back(pos + sf::Vector2f(WallSize, WallSize));
                p.push_back(pos + sf::Vector2f(0, WallSize));
                p.push_back(p[0]);

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

            }

            vector<sf::Vector2f> p;
            p.push_back(ViewPos);
            p.push_back(ViewPos + sf::Vector2f(0, ViewSize.y));
            p.push_back(ViewPos + ViewSize);
            p.push_back(ViewPos + sf::Vector2f(ViewSize.x, 0));
            p.push_back(p[0]);

            for (int i = 0; i < 4; ++i) {
                segments.Add(p[i], p[i + 1]);

                points.push_back(p[i]);

                sf::Vector2f v = p[i + 1] - p[i];
                sf::Vector2f eps = v / Length(v) * (float)0.1;

                points.push_back(p[i] + eps);
                points.push_back(p[i] - eps);

            }

        }

        void setCenter(sf::Vector2f pos) {
            center = pos;
        }

        void makeLight(sf::RenderTarget &target) {
            shape.clear();
            for (auto p: points) {
                shape.push_back(segments.intersect(center, p - center).point);
            }

            vector<sf::Vector2f> rays;
            for (auto point: shape) {
                rays.push_back(point - center);
            }
            sort(rays.begin(), rays.end(), cmp<float>);
            rays.push_back(rays[0]);


            for (int i = 0; i < (int)rays.size() - 1; ++i) {
                if (rays[i] == rays[i + 1]) continue;

                sf::VertexArray triangle(sf::Triangles, 3);
                triangle[0].position = sf::Vector2f(center);
                triangle[1].position = sf::Vector2f(center + rays[i]);
                triangle[2].position = sf::Vector2f(center + rays[i + 1]);

                triangle[0].color = sf::Color::White;
                triangle[1].color = sf::Color::Cyan;
                triangle[2].color = sf::Color::Magenta;

                target.draw(triangle);
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
