#include "itemgraphic.h" 

ItemGraphic::ItemGraphic(float xpos, float ypos, string c) {
    x = xpos;
    y = ypos;
    color = c; 
}

ItemGraphic::~ItemGraphic(){ }

float ItemGraphic::getX(){ return x; }
float ItemGraphic::getY(){ return y; }
string ItemGraphic::getColor(){ return color; }
void ItemGraphic::setX(float xcoor){ x = xcoor; }  
void ItemGraphic::setY(float ycoor){ y = ycoor;}
void ItemGraphic::setColor(string c){ color = c; }