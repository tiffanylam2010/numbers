#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Piece.h"

#define TAG_PROGRESS_BACK 1
#define TAG_PROGRESS_FRONT 2

#define PIECE_TOTAL_NUM 15
#define PIECE_LINE_NUM 3
#define MAX_NUM 6

class HelloWorld : public cocos2d::Layer
{
    
private:
    void startTimer();
    void callbackProgressEnd();
 	int curIdx;// 当前猜到那个数字
	int maxIdx; // 最大是那个数值
    void onClick(cocos2d::Ref* pSender, int idx);
    cocos2d::Vector <Piece *> pieces;
    //cocos2d::Map<int, Piece *> piecemap;
    void genRandomValue();
    std::vector<int> randomVector;
    
    std::map<int, std::vector<int> > posConfig = {
        {4, {2,3,7,8}},
        {5, {2,3,7,8,9}},
        {6, {1,2,3,6,7,8}},
        {15,{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14}}
    };
    
    cocos2d::MenuItemImage* restartItem;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // a selector callback
    void menuStartGameCallback(cocos2d::Ref* pSender);

	bool guessNum(int value); // 猜数值, 返回是否猜对
	void initData();// 初始化,设置最大数值
	bool isFinished();
    
    void gameStart();
    void reset();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
