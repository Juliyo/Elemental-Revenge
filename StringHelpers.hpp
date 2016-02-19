/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StringHelpers.hpp
 * Author: julio
 *
 * Created on 19 de febrero de 2016, 17:17
 */

#ifndef STRINGHELPERS_HPP
#define STRINGHELPERS_HPP
#include <sstream>

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

#include <../StringHelpers.inl>


#endif /* STRINGHELPERS_HPP */

