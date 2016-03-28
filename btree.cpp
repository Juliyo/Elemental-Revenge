/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   btree.cpp
 * Author: julio
 * 
 * Created on 28 de marzo de 2016, 18:04
 */

#include <string>
#include <iostream>
#include "btree.hpp"

btree::btree() {
    root = NULL;
}

btree::btree(const btree& orig) {
}

btree::~btree() {
    destroy_tree();
}
void btree::destroy_tree(node *leaf)
{
  if(leaf!=NULL)
  {
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);
    delete leaf;
  }
}

void btree::insert(int key, node *leaf, std::string pregunta_p, std::string r1, std::string r2)
{
  if(key< leaf->key_value)
  {
    if(leaf->left!=NULL)
     insert(key, leaf->left,pregunta_p,r1,r2);
    else
    {
      leaf->left=new node;
      leaf->left->key_value=key;
      leaf->left->pregunta=pregunta_p;
      leaf->left->respuesta1=r1;
      leaf->left->respuesta2=r2;
      leaf->left->left=NULL;    //Sets the left child of the child node to null
      leaf->left->right=NULL;   //Sets the right child of the child node to null
    }  
  }
  else if(key>=leaf->key_value)
  {
    if(leaf->right!=NULL)
      insert(key, leaf->right,pregunta_p,r1,r2);
    else
    {
      leaf->right=new node;
      leaf->right->key_value=key;
      leaf->right->pregunta=pregunta_p;
      leaf->right->respuesta1=r1;
      leaf->right->respuesta2=r2;
      leaf->right->left=NULL;  //Sets the left child of the child node to null
      leaf->right->right=NULL; //Sets the right child of the child node to null
    }
  }
}

node *btree::search(int key, node *leaf)
{
  if(leaf!=NULL)
  {
    if(key==leaf->key_value)
      return leaf;
    if(key<leaf->key_value)
      return search(key, leaf->left);
    else
      return search(key, leaf->right);
  }
  else return NULL;
}

void btree::insert(int key,std::string pregunta, std::string r1, std::string r2)
{
  if(root!=NULL)
    insert(key, root, pregunta,r1,r2);
  else
  {
    root=new node;
    root->key_value=key;
    root->pregunta=pregunta;
    root->respuesta1=r1;
    root->respuesta2=r2;
    root->left=NULL;
    root->right=NULL;
  }
}

node *btree::search(int key)
{
  return search(key, root);
}

void btree::destroy_tree()
{
  destroy_tree(root);
}