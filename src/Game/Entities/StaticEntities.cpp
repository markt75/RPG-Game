#include "StaticEntities.h"

StaticEntities::StaticEntities(int ox, int oy, string overworldPath) : Entity(ox, oy, 180, 180, overworldPath){
    this->overworldPath = overworldPath;
}

void StaticEntities::renderOverworld(){
    overworldSprite.draw(renderX, renderY, ow, oh);
}


