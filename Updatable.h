#ifndef __UPDATABLE__
    #define __UPDATABLE__

    #include <SFML/Graphics.hpp>

    class Updatable {
    public:
        virtual void update(sf::Time time) = 0;
        virtual ~Updatable() = default;
    };

#endif // __UPDATABLE__
