//
//  Piece.cpp
//  MyCppGame
//
//  Created by Tiffany Lam on 15-2-23.
//
//

#include "Piece.h"
USING_NS_CC;



Piece* Piece::create(const std::string &normalImage, const std::string &selectedImage,
                                              const std::string &disabledImage, const cocos2d::ccMenuCallback callback)
{
    Piece *pRet = new Piece();
    if (pRet && pRet->init(normalImage, selectedImage, disabledImage, callback))
    {
        pRet->autorelease();
    }
    else
    {
        delete pRet;
        pRet = NULL;
    }
    return pRet;
    
}

bool Piece::init(const std::string &normalImage, const std::string &selectedImage,
                 const std::string &disabledImage, const cocos2d::ccMenuCallback callback)
{
    if (!MenuItemImage::initWithNormalImage(normalImage, selectedImage, disabledImage,  callback)){
        return false;
    }
   // auto *label =LabelTTF::create(std::to_string(0), "Arial", 24);
   // this->addChild(label, 1, TAG_LABEL);
    return true;

}
/*

void Piece::setValue(int value)
{
    this->_value = value;
}
*/
void Piece::showValue(bool ok)
{
    this->removeChildByTag(TAG_LABEL);
    this->setDisabledImage(cocos2d::Sprite::create("show.png"));
    
    auto *label =LabelTTF::create(cocos2d::StringUtils::toString(this->getTag()), "Arial", 24);
    this->addChild(label, 1, TAG_LABEL);
    label->setColor(cocos2d::Color3B(0, 0, 0));
    
    label->setPosition(Vec2(50,50));
    
    if (!ok)
    {
        log("gameover!");
        this->setDisabledImage(cocos2d::Sprite::create("show_wrong.png"));
    }
    this->setVisible(true);
    this->setEnabled(false);
}


void Piece::hideValue()
{
    this->setEnabled(true);
    this->removeChildByTag(TAG_LABEL);
   
}
/*
void Piece::onClick()
{
    log("on click, value:%d", this->_value);
    this->setEnabled(false);
    auto *label = this->getChildByTag(TAG_LABEL);
    label->setVisible(true);
    
}*/