/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   btree.hpp
 * Author: julio
 *
 * Created on 28 de marzo de 2016, 18:04
 */

#ifndef BTREE_HPP
#define BTREE_HPP

struct node {
    int key_value;
    std::string pregunta;
    std::string respuesta1;
    std::string respuesta2;
    node *left;
    node *right;
};

class btree {
public:
    btree();
    btree(const btree& orig);
    virtual ~btree();

    void insert(int key, std::string pregunta, std::string r1, std::string r2);
    node *search(int key);
    void destroy_tree();
    node *nextNode(node *leaf, int dir);
private:
    void destroy_tree(node *leaf);
    void insert(int key, node *leaf, std::string pregunta, std::string r1, std::string r2);
    node *search(int key, node *leaf);

    node *root;
};

#endif /* BTREE_HPP */

