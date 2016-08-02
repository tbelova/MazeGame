#ifndef __MONSTER__
    #define __MONSTER__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Maze.h"
    #include "Consts.h"
    #include "Character.h"

    using namespace std;

    class Monster: public Managable<sf::Drawable>, public Managable<Updatable> {
    private:

        vector<sf::Vector2f> pathInGame;
        vector<sf::Vector2<int> > pathInMaze;
        vector<sf::Vector2<int> > dir = {sf::Vector2<int>(0, 1),
                                         sf::Vector2<int>(1, 0),
                                         sf::Vector2<int>(0, -1),
                                         sf::Vector2<int>(-1, 0)};
        vector<vector<bool> > used;
        vector<vector<int> > number;
        unsigned int cur;
        sf::Vector2f curPos, nextPos, lastSeenPoint = sf::Vector2f(-1, -1);
        sf::RectangleShape rect;
        const float speed = 1.5 * WallSize;
        const float eps = 1e-5;
        Character& character;

        const unsigned int SEEZONE = 20;

        void dfs(sf::Vector2<int> pos, Maze& maze) {
            used[pos.x][pos.y] = 1;
            pathInMaze.push_back(pos);

            auto curDir = dir;
            random_shuffle(curDir.begin(), curDir.end());
            for (auto d: curDir) {
                auto to = pos + d;
                if (maze.isInMaze(to) && !used[to.x][to.y] && maze.getCell(to)) {
                    dfs(to, maze);
                //    pathInMaze.push_back(pos);
                }
            }
        }

        vector<sf::Vector2<int> > bfs(sf::Vector2<int> pos, sf::Vector2<int> finish, Maze& maze) {
            vector<vector<bool> > visited;
            visited.resize(maze.getWidth(), vector<bool>(maze.getHeight(), 0));

            vector<vector<sf::Vector2<int> > > parent;
            parent.resize(maze.getWidth(), vector<sf::Vector2<int> >(maze.getHeight(), sf::Vector2<int>(-1, -1)));
            parent[pos.x][pos.y] = pos;

            queue<sf::Vector2<int> > q;

            q.push(pos);
            visited[pos.x][pos.y] = 1;

            while (!q.empty()) {
                sf::Vector2<int> v = q.front();
                q.pop();

                if (v == finish) {
                    vector<sf::Vector2<int> > curPath;
                    while (parent[v.x][v.y] != v) {
                        curPath.push_back(v);
                        v = parent[v.x][v.y];
                    }
                    reverse(curPath.begin(), curPath.end());
                    return curPath;
                }

                for (auto curDir: dir) {
                    auto to = v + curDir;
                    if (maze.isInMaze(to) && maze.getCell(to) && !visited[to.x][to.y]) {
                        visited[to.x][to.y] = 1;
                        parent[to.x][to.y] = v;
                        q.push(to);
                    }
                }
            }
        }

        unsigned nextStep(unsigned int step) {
            if (step == pathInGame.size() - 1) return 0;
            return step + 1;
        }

    public:

        Monster(Maze& maze, Manager<sf::Drawable>& mng, Manager<Updatable>& updMng, Character& character):
            Manager<sf::Drawable>::Object(mng), Manager<Updatable>::Object(updMng),
            character(character) {

            used.resize(maze.getWidth(), vector<bool>(maze.getHeight(), 0));
            number.resize(maze.getWidth(), vector<int>(maze.getHeight(), -1));

            dfs(sf::Vector2<int>(1, 1), maze);
            pathInMaze.push_back(pathInMaze[0]);
            for (int i = 0; i < (int)pathInMaze.size() - 1; ++i) {
                auto newPath = bfs(pathInMaze[i], pathInMaze[i + 1], maze);
                for (auto cell: newPath) {
                    pathInGame.push_back(FromMazeToGame(cell));
                }
            }

            //go(sf::Vector2<int>(1, 1), maze);
            //pathInMaze.pop_back();
            //for (auto cell: pathInMaze) {
            //    pathInGame.push_back(FromMazeToGame(cell));
            //}
            for (int i = 0; i < (int)pathInGame.size(); ++i) {
                number[FromGameToMaze(pathInGame[i]).x][FromGameToMaze(pathInGame[i]).y] = i;
            }

            cur = 0;
            nextPos = curPos = pathInGame[0];

            rect.setSize(sf::Vector2f(MonsterSize, MonsterSize));
            rect.setOrigin(MonsterSize / 2, MonsterSize / 2);
            rect.setPosition(sf::Vector2f(0, 0));
            rect.setFillColor(sf::Color::Blue);

        }

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            states.transform = sf::Transform().translate(curPos) * states.transform;
            target.draw(rect, states);
        }

        void justGo(sf::Time time) {
            nextPos = pathInGame[nextStep(cur)];
            goToPoint(time);
        }

        void runForTheCharacter(sf::Time time) {
            nextPos = lastSeenPoint;
            goToPoint(time);
            sf::Vector2<int> posCharacter = FromGameToMaze(lastSeenPoint);
            cur = number[posCharacter.x][posCharacter.y];
            if (curPos == lastSeenPoint) lastSeenPoint = sf::Vector2f(-1, -1);
        }

        void goToCenter(sf::Time time) {
            nextPos = pathInGame[cur];
            goToPoint(time);
        }

        void goToPoint(sf::Time time) {
            float distance = time.asSeconds() * speed;
            if (distance > Length(nextPos - curPos)) {
                curPos = nextPos;
                cur = nextStep(cur);
            } else {
                curPos += distance * (nextPos - curPos) / Length(nextPos - curPos);
            }
        }

        bool seeCharacter() {

            rect.setFillColor(sf::Color::Blue);

            sf::Vector2<int> posCharacter = FromGameToMaze(character.getPos());
            sf::Vector2<int> posMonster = FromGameToMaze(curPos);

            if (posCharacter.x != posMonster.x
             && posCharacter.y != posMonster.y) return false;

            if (abs(posCharacter.x - posMonster.x) > SEEZONE) return false;
            if (abs(posCharacter.y - posMonster.y) > SEEZONE) return false;

            for (int z = posCharacter.x + 1; z < posMonster.x; ++z) {
                if (number[z][posCharacter.y] == -1) return false;
            }
            for (int z = posMonster.x + 1; z < posCharacter.x; ++z) {
                if (number[z][posMonster.y] == -1) return false;
            }
            for (int z = posCharacter.y + 1; z < posMonster.y; ++z) {
                if (number[posCharacter.x][z] == -1) return false;
            }
            for (int z = posMonster.y + 1; z < posCharacter.y; ++z) {
                if (number[posMonster.x][z] == -1) return false;
            }

            rect.setFillColor(sf::Color::Yellow);

            //if (Length(curPos - FromMazeToGame(posMonster)) > eps) return false;

            return true;

        }

        virtual void update(sf::Time time) override {
            if (seeCharacter()) lastSeenPoint = FromMazeToGame(FromGameToMaze(character.getPos()));
            if (lastSeenPoint.x == -1)
                justGo(time);
            else
                runForTheCharacter(time);
        }

        virtual ~Monster() = default;

    };


#endif
