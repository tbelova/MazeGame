#ifndef __MONSTER__
    #define __MONSTER__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Maze.h"
    #include "Consts.h"

    using namespace std;

    class Monster: public Managable<sf::Drawable>, public Managable<Updatable> {
    private:

        vector<sf::Vector2f> path;
        vector<sf::Vector2<int> > dir = {sf::Vector2<int>(0, 1),
                                         sf::Vector2<int>(1, 0),
                                         sf::Vector2<int>(0, -1),
                                         sf::Vector2<int>(-1, 0)};
        vector<vector<bool> > used;
        unsigned int cur;
        sf::Vector2f curPos;
        sf::RectangleShape rect;
        const float speed = 3 * WallSize;

        void dfs(sf::Vector2<int> pos, Maze& maze) {
            used[pos.x][pos.y] = 1;
            path.push_back((sf::Vector2f)pos * WallSize + sf::Vector2f(WallSize / 2, WallSize / 2));

            auto curDir = dir;
            random_shuffle(curDir.begin(), curDir.end());
            for (auto d: curDir) {
                auto to = pos + d;
                if (maze.isInMaze(to) && !used[to.x][to.y] && maze.getCell(to)) {
                    dfs(to, maze);
                    path.push_back((sf::Vector2f)pos * WallSize + sf::Vector2f(WallSize / 2, WallSize / 2));
                }
            }
        }

        unsigned nextStep(unsigned int step) {
            if (step == path.size() - 1) return 0;
            return step + 1;
        }

    public:

        Monster(Maze& maze, Manager<sf::Drawable>& mng, Manager<Updatable>& updMng):
            Manager<sf::Drawable>::Object(mng), Manager<Updatable>::Object(updMng) {

            used.resize(maze.getWidth(), vector<bool>(maze.getHeight(), 0));
            dfs(sf::Vector2<int>(1, 1), maze);
            path.pop_back();

            cur = 0;
            curPos = path[0];

            rect.setSize(sf::Vector2f(MonsterSize, MonsterSize));
            rect.setOrigin(MonsterSize / 2, MonsterSize / 2);
            rect.setPosition(sf::Vector2f(0, 0));
            rect.setFillColor(sf::Color::Blue);

        }

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            states.transform = sf::Transform().translate(curPos) * states.transform;
            target.draw(rect, states);
        }

        virtual void update(sf::Time time) override {
            sf::Vector2f nextPos = path[nextStep(cur)];

            float distance = time.asSeconds() * speed;

            if (distance > Length(nextPos - curPos)) {
                curPos = nextPos;
                cur = nextStep(cur);
            } else {
                curPos += distance * (nextPos - curPos) / Length(nextPos - curPos);
            }

        }

        virtual ~Monster() = default;

    };


#endif
