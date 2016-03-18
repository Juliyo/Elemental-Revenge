/* 
 * File:   Cargar.cpp
 * Author: alfon
 * 
 * Created on 17 de marzo de 2016, 21:25
 */

#include "Cargar.h"
#include "tinystr.h"
#include "tinyxml.h"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

Cargar::Cargar() {
    
    
}

Cargar::Cargar(const Cargar& orig) {
}

Cargar::~Cargar() {
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            delete[] _tilemap[l][y];
        }
        delete[] _tilemap[l];
    }
    delete[] _tilemap;
}

void Cargar::leerMapa(){
       /*ANADIDO*/
    if(!fond.loadFromFile("resources/background.jpg")){
        std::cerr << "Error cargando la imagen fondooo.png";
        exit(0);
    }
    
    fondo.setTexture(fond);
    /*ANADIDO*/

    TiXmlDocument doc;
    doc.LoadFile("resources/mapa2.tmx");
    TiXmlElement* map = doc.FirstChildElement("map");

    map->QueryIntAttribute("width",&_width);
    map->QueryIntAttribute("height",&_height);
    map->QueryIntAttribute("tilewidth",&_tileWidth);
    map->QueryIntAttribute("tileheight",&_tileHeigth);
    
    //Leemos las diferentes imagenes que nos sirven para hacer el rect de las texturas
    TiXmlElement *img = map->FirstChildElement("tileset");
    int numTil=0;
    while(img){
        numTil++;
        img=img->NextSiblingElement("tileset");
    }
    
                TiXmlElement *layer = map->FirstChildElement("layer");

    
    TiXmlElement *ejemplo = map->FirstChildElement("tileset");
    while(ejemplo){
        _numTilesets++;
        
        ejemplo= ejemplo->NextSiblingElement("tileset");
    }  
    
    string filename;
    string filename2;
            img = map->FirstChildElement("tileset");

    
            std::cout<<_numTilesets;
    for(int i=0; i<_numTilesets;i++){

    //while(img){
        if(img){
            
            if(i==1){
                filename=(string)img->FirstChildElement("image")->Attribute("source");
                    filenameVector.push_back(new sf::String(filename));

            }else{
                filename2=(string)img->FirstChildElement("image")->Attribute("source");
                filenameVector.push_back(new sf::String(filename2));
            }
            img=img->NextSiblingElement("tileset");
              //  printf("FDSFSA\n");
        
    //}  
        }


    TiXmlElement *layer = map->FirstChildElement("layer");

    _tilesetTexture=new sf::Texture[_numTilesets];

    _tilesetTexture[i].loadFromFile(filename);
    while(layer){
        _numLayers++;
        layer= layer->NextSiblingElement("layer");
    }  
            }
    //Reserva de memoria para saber el numnero de capas y el tamaño 
    _tilemap=new int**[_numLayers];
    for(int i=0; i<_numLayers; i++){
        _tilemap[i]=new int*[_height];
    }
    
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            _tilemap[l][y]=new int[_width];
        }
    }

    TiXmlElement *data;
    
    layer = map->FirstChildElement("layer");
    string *name=new string[_numLayers];
    int j=0;
    int l=0;
      
    while(layer){
        data= layer->FirstChildElement("data")->FirstChildElement("tile");
        name[j]= (string)layer->Attribute("name");
            while(data){
                for(int y=0; y<_height; y++){
                    for(int x=0; x<_width;x++){
                        data->QueryIntAttribute("gid",&_tilemap[l][y][x]);
                        data=data->NextSiblingElement("tile");
                    }
                }
            }
        l++;
        layer= layer->NextSiblingElement("layer");
        j++;
    }
      
       //Reserva de memoria para los sprites
    _tilemapSprite=new sf::Sprite***[_numLayers];
      
    for(int l=0; l<_numLayers; l++){
        _tilemapSprite[l]=new sf::Sprite**[_height];
    }
      
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            _tilemapSprite[l][y]= new sf::Sprite*[_width];
            for(int x=0; x<_width; x++){
                _tilemapSprite[l][y][x]=new sf::Sprite();
            }
        }
    } 
    sf::Texture aux;  
    
    //falta el corte
  
    for(int i=0; i<_numTilesets;i++){
    
    int columns = _tilesetTexture[i].getSize().x / _tileWidth;
    int rows = _tilesetTexture[i].getSize().y / _tileHeigth;
    
    cout<<columns<<" "<<rows<<endl; 

    _tilesetSprite =new sf::Sprite[columns*rows];     
    //int t=0;
    
        for(int t=0; t<_numLayers; t++){

    for(int y=0; y<rows; y++){
        for(int x=0; x<columns;x++){
              _tilesetSprite[t].setTexture(_tilesetTexture[i]);
              //_tilesetSprite[t].setTextureRect(sf::IntRect(left,top,width,height));//ojo si hay dos imagenes
              _tilesetSprite[t].setTextureRect(sf::IntRect(x*_tileWidth,y*_tileHeigth,_tileWidth,_tileHeigth));
              t++;
        }
    }
        }
    cout<<"nostas"<<endl;
    /**
    for(int y=0; y<t; y++)
    {
     cout<<_tilesetSprite[y].getTextureRect().left<<" ";
     cout<<_tilesetSprite[y].getTextureRect().top<<" ";
      cout<<_tilesetSprite[y].getTextureRect().width<<" ";
       cout<<_tilesetSprite[y].getTextureRect().height<<endl;
    }**/
    
    //cout<<t<<endl;
   
    //asignacion sprite
      
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            for(int x=0; x<_width;x++){
                int gid=_tilemap[l][y][x]-1;
                if(gid>=rows*columns){
                    cout<<gid<<endl;
                    cout<<rows<<endl;
                    cout<<columns<<endl;
                    cout<<"Error aaaa"<<endl;
                }
                else if(gid>0){   

                    _tilemapSprite[l][y][x]=new sf::Sprite(_tilesetTexture[i],_tilesetSprite[gid].getTextureRect());
                    _tilemapSprite[l][y][x]->setPosition(x*_tileWidth,y*_tileHeigth);
                }
                else{
                    _tilemapSprite[l][y][x]=NULL;
                }
            }
        }
    }
    
    }
      
    /////////////////////Resumen
    cout<<endl;
    cout<<"Resumen:"<<endl;
    cout<<"Heigth= "<<_height<<endl;
    cout<<"Width= "<<_width<<endl;
    cout<<"TileWidth= "<<_tileWidth<<endl;
    cout<<"TileHeigth= "<<_tileHeigth<<endl;
    cout<<"Numero de capas= "<<_numLayers<<endl;
    cout<<"Nombre del tileset= "<<filename[0]<<endl;
    cout<<"Nombre del tileset= "<<filename[1]<<endl;
    cout<<endl;
            std::cout<< "joddddddddd"<<std::endl;
    std::cout<< filename<<std::endl;

    std::cout<< filename2<<std::endl;

     
     /**
    cout<<"Gid de las capas"<<endl;
   for(int l=0; l<_numLayers; l++)
    {
       cout<<name[l]<<endl;
        for(int y=0; y<_height; y++)
        {
            for(int x=0; x<_width;x++)
            {    
                cout<<_tilemap[l][y][x]<<" ";

                if(x==_width-1)
                {
                    cout<<endl;
                }
            }
        }
   }**/
}


void Cargar::dibuja(sf::RenderWindow& window){
    /*ANADIDO*/
    //window.draw(fondo);
    //sf::View view=window.getView();

    //fondo.setPosition(view.getCenter().x-fond.getSize().x/2,view.getCenter().y-fond.getSize().y/2);
    window.draw(fondo);
    
    /*ANADIDO*/
    for(int t=0; t<_numLayers; t++){
        for(int y=0; y<_height; y++){
            for(int x=0; x<_width; x++){
                if(_tilemapSprite[t][y][x]!=NULL){
                    window.draw(*(_tilemapSprite[t][y][x]));
                }
            }
        }
    }

}