/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_TEXTURE_SFML_HPP_
#define GRADE_DE_TEXTURE_SFML_HPP_

/*  ---- INCLUDES ---- */
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "GradeDe/Error.hpp"
#include "GradeDe/Vector.hpp"

/*  ---- CLASS ---- */
namespace gd
{
    class Texture
    {
        public:
            Texture() = default;
            ~Texture() = default;
            void loadFromFile(const std::string &path);
            void *getTexture();
            gd::Vector<int> getSize() const;

        private:
            sf::Texture _texture;
    };
} // namespace gd

#endif /* !GRADE_DE_TEXTURE_SFML_HPP_ */
