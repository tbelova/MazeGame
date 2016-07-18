#include "SetOfSegments.h"

SetOfSegments::Segment::Segment(sf::Vector2f a, sf::Vector2f b): a(a), b(b) {}

SetOfSegments::SetOfSegments(Maze& maze) {

    for (int i = 0; i < maze.getWidth(); ++i) {
        for (int j = 0; j < maze.getHeight(); ++j) {
            if (!maze.getCell(sf::Vector2<int>(i, j))) {
                segments.push_back(Segment(sf::Vector2f(i, j), sf::Vector2f(i + 1, j)));
                segments.push_back(Segment(sf::Vector2f(i + 1, j), sf::Vector2f(i + 1, j + 1)));
                segments.push_back(Segment(sf::Vector2f(i + 1, j + 1), sf::Vector2f(i, j + 1)));
                segments.push_back(Segment(sf::Vector2f(i, j + 1), sf::Vector2f(i, j)));
            }
        }
    }

    segments.push_back(Segment(sf::Vector2f(0, 0), sf::Vector2f(0, maze.getWidth())));
    segments.push_back(Segment(sf::Vector2f(0, 0), sf::Vector2f(maze.getHeight(), 0)));
    segments.push_back(Segment(sf::Vector2f(maze.getWidth(), 0), sf::Vector2f(maze.getHeight(), maze.getWidth())));
    segments.push_back(Segment(sf::Vector2f(0, maze.getHeight()), sf::Vector2f(maze.getHeight(), maze.getWidth())));

}

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
