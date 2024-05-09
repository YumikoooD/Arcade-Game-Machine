/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IDLLoader
*/

#ifndef IDLLOADER_HPP_
    #define IDLLOADER_HPP_

#include <string>
#include <memory>
#include "IDLLoader.hpp"

// Load a library that has a fonction to create a pointer using new
template <typename T>
class IDLLoader{
    public:
        // @brief Close the library and delete the pointer returned in getInstance
        virtual ~IDLLoader() = default;
        // @brief Return a pointer to an instance of @c T created using the `name` fonction
        // @note IT IS AUTOMATICALLY FREED, DO NOT DELETE IT
        // @param name The name of the fonction that creates a @c T instance using new
        // @return The pointer to the instance
        virtual T *getInstance(const std::string &name) = 0;
};

// Load a library that has a fonction to create a pointer using new
template <typename T, typename A>
class ADLLoader : public IDLLoader<T>{
    public:
        virtual ~ADLLoader() = default;
    protected:
        // The pointer to the return value of getInstance
        std::unique_ptr<T> instance = NULL;
        // The lib that has been opened
        A _lib;
};

#endif /* !IDLLOADER_HPP_ */
