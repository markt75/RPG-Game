#include "Entity.h"

Entity::Entity(int ox, int oy, int ow, int oh, string overworldPath) {
    this->ox = ox;
    this->oy = oy;
    this->oh = oh;
    this->ow = ow;
    
    overworldSprite.load(overworldPath);
}

void Entity::renderOverworld() {
    overworldSprite.draw(ox, oy, ow, oh);
}

ofRectangle Entity::getBounds(){
    return ofRectangle(ox, oy, ow, oh);
}

ofRectangle Entity::getBounds(int ox, int oy){
    return ofRectangle(ox, oy, ow, oh);
}

bool Entity::collides(Entity* entity){     
    return this->getBounds().intersects(entity->getBounds());
}
