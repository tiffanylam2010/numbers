//
//  Piece.h
//  MyCppGame
//
//  Created by Tiffany Lam on 15-2-23.
//
//

#ifndef MyCppGame_Piece_h
#define MyCppGame_Piece_h

#include "cocos2d.h"

#define TAG_LABEL 101

class Piece: public cocos2d::MenuItemImage
{
    //int _value;
    //void onClick();
public:
    
    // Constructor
    
    static Piece* create(const std::string &normalImage, const std::string &selectedImage,
                         const std::string &disabledImage, const cocos2d::ccMenuCallback);
    
    virtual bool init(const std::string &normalImage, const std::string &selectedImage,
                      const std::string &disabledImage, const cocos2d::ccMenuCallback);
   // void setValue(int value);
    void showValue(bool ok);
    void hideValue();
    
};
#endif
