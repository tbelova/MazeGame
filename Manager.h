#ifndef __MANAGER__
    #define __MANAGER__

    #include <iostream>
    #include <unordered_set>
    #include <type_traits>

    template<class T>
    class Manager {
      static_assert(std::has_virtual_destructor<T>::value,
                    "Template argument of Manager must have a virtual destructor!");

      public:
        class Object : public T {
          Manager<T> &mMgr;

          public:
            Object(Manager<T> &aMgr)
            : T(), mMgr(aMgr) {
              mMgr.mObjects.insert(this);
            }

            Object(const Object& obj): T(obj), mMgr(obj.mMgr) {
                mMgr.mObjects.insert(this);
            }

            Object& operator = (const Object&) = delete;

            virtual ~Object() {
              mMgr.mObjects.erase(this);
            }
        };

      private:
        std::unordered_set<Object*> mObjects;

      public:
        Manager() = default;
        Manager(const Manager&) = delete;
        Manager& operator = (const Manager&) = delete;

        void draw(sf::RenderTarget &target) {
            for (auto it = mObjects.begin(); it != mObjects.end(); ++it) {
                target.draw(**it, sf::RenderStates());
            }
        }

        decltype(mObjects.begin()) begin() {
          return mObjects.begin();
        }

        decltype(mObjects.end()) end() {
          return mObjects.end();
        }
    };

#endif // __MANAGER__
