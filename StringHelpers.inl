/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StringHelpers.inl
 * Author: julio
 *
 * Created on 19 de febrero de 2016, 17:18
 */


template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}