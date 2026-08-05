#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include "engine/primitives.hpp"
#include <vector>
class Physics{
    public:
        Physics() = delete;
        ~Physics() = delete;
        Physics(const Physics& other) = delete;
        Physics(Physics&& other) noexcept = delete;
        Physics& operator=(const Physics& other) = delete;
        Physics& operator=(Physics&& other) noexcept = delete;

        struct Bounding{
            int _sizeX;
            int _sizeY;
            int _posX;
            int _posY;
            Bounding(int sizeX, int sizeY, int posX, int posY): _sizeX(sizeX), _sizeY(sizeY), _posX(posX), _posY(posY){}
        };

        static bool _AABBSimpleCollision(const Bounding& a_bounding, const Bounding& b_bounding) {
            if (a_bounding._posX < b_bounding._posX + b_bounding._sizeX &&
                a_bounding._posX + a_bounding._sizeX > b_bounding._posX &&
                a_bounding._posY < b_bounding._posY + b_bounding._sizeY && // Corrigé : _sizeY au lieu de _sizeX
                a_bounding._posY + a_bounding._sizeY > b_bounding._posY)   // Corrigé : _sizeY au lieu de _sizeX
            {
                return true;
            }
            return false;
        }

        static const Bounding GetBouding(Square& p){
            return Bounding(p.GetSize(), p.GetSize(), p.GetPosX(), p.GetPosY());
        }
        static const Bounding GetBouding(Rectangle& p){
            return Bounding(p.GetSizeX(), p.GetSizeY(), p.GetPosX(), p.GetPosY());
        }

        /*
            T is Primitives
            U is Primitives
        */
        template <typename T, typename U>
        static bool SimpleCollision(T& a, U& b){
            Bounding a_bounding = GetBouding(a);
            Bounding b_bounding = GetBouding(b);

            return _AABBSimpleCollision(a_bounding, b_bounding);
        }
};
#endif