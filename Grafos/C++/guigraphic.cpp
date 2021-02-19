#include "guigraphic.h" 

GuiGraphic::GuiGraphic(string xpos, string ypos, string c) {
    x = std::stof(xpos);
    y = std::stof(ypos);
    color = c; 
}


GuiGraphic::~GuiGraphic(){ }