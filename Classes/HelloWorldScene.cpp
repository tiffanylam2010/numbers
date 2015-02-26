#include "HelloWorldScene.h"

USING_NS_CC;



Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::createWithItem(closeItem);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    // 重新开始游戏的按钮
    this->restartItem = MenuItemImage::create("hide.png",
                                             "hdie_sel.png",
                                             CC_CALLBACK_1(HelloWorld::menuStartGameCallback, this));
    this->restartItem->setPosition(Vec2((visibleSize.width-this->restartItem->getContentSize().width/2)/2,
                                        this->restartItem->getContentSize().height/2)
                                        );
    menu->addChild(this->restartItem);
    
    auto tmplabel = LabelTTF::create("restart", "Arial", 24);
    tmplabel->setColor(Color3B(0,0,0));
    this->restartItem->addChild(tmplabel);
    tmplabel->setPosition(Vec2(50,50));
    
    
    this->pieces =  cocos2d::Vector<Piece *>{PIECE_TOTAL_NUM};
    
    int perline = PIECE_TOTAL_NUM/PIECE_LINE_NUM;// 15/3=5;
    
    int imgwidth = 100;
    int imgheight = 100;
    int deltawidth = 10;
    int deltaheight = 10;
    int start_x = (visibleSize.width-imgwidth*perline-deltawidth*(perline-1))/2;
    int start_y = (origin.y + 100 + imgheight*PIECE_LINE_NUM + deltaheight*(PIECE_LINE_NUM-1));
    
    for( int i=0; i<PIECE_TOTAL_NUM; i++)
    {
        Piece * piece = Piece::create("hide.png", "hide_sel.png", "show.png", CC_CALLBACK_1(HelloWorld::onClick,this, i));
        int x = start_x + i%perline*(imgwidth+deltawidth);
        int y = start_y - ((int)i/perline) *(imgheight+deltaheight) ;
        piece->setPosition(Vec2(x, y));
        this->pieces.pushBack(piece);
        menu->addChild(piece);
        piece->setVisible(false);
      //  piece->setTag(i+1);
       // piece->showValue(true);
    }
    

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
    
    //auto s = Director::getInstance()->getWinSize();
    

    this->reset();
    
      
    return true;
}

void HelloWorld::reset()
{
    this->maxIdx = 4;
    this->removeChildByTag(TAG_PROGRESS_BACK);
    this->removeChildByTag(TAG_PROGRESS_FRONT);
    gameStart();
}

void HelloWorld::gameStart()
{
    this->restartItem->setVisible(false);
    this->curIdx = 1;
    
    this->genRandomValue();
    
    std::vector<int> v = this->posConfig[this->maxIdx];
    int idx = 0;

    for(int i=0;i<this->pieces.size();i++)
    {
        auto p = pieces.at(i);
        
        if( find(v.begin(), v.end(), i) != v.end())
        {
            p->setTag(this->randomVector[idx++]);
            p->showValue(true);
        }
        else{
            p->setTag(0);
            p->setVisible(false);
        }
        
    }
    
    startTimer();
    
    
}

void HelloWorld::genRandomValue()
{
    this->randomVector.clear();
    
    srand(time(nullptr));
    
    std::vector<int> tmpVector;
    for(int i=0; i<this->maxIdx; i++)
    {
        tmpVector.push_back(i+1);
    }
    
    int left=this->maxIdx;
    for(int i=0; i<this->maxIdx; i++)
    {
        int idx = rand()%left;
        left--;
        this->randomVector.push_back(tmpVector[idx]);
        tmpVector.erase(tmpVector.begin()+idx);
    }
    
    
    for(int i=0; i<this->randomVector.size();i++)
    {
        log("random:%d", this->randomVector[i]);
    }
    
    
}

void HelloWorld::startTimer()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // 进度条的背景
    auto back = Sprite::create("progress_back.png");
    Vec2 progressPos = Vec2(visibleSize.width/4, visibleSize.height*6/7);
    this->addChild(back, 1, TAG_PROGRESS_BACK);
    back->setPosition(progressPos);
    
    auto front = ProgressTimer::create(Sprite::create("progress_front.png"));
    front->setType(ProgressTimer::Type::BAR);
    //    Setup for a bar starting from the left since the midpoint is 0 for the x
    front->setMidpoint(Vec2(0,0));
    //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    front->setBarChangeRate(Vec2(1, 0));
    this->addChild(front,1, TAG_PROGRESS_FRONT);
    front->setPosition(progressPos);

    auto * funcall= CallFunc::create(CC_CALLBACK_0(HelloWorld::callbackProgressEnd,this));
    auto to1 = Sequence::create(ProgressTo::create(5, 100),  funcall, NULL);
    
    front->runAction(to1);
    log("showTimer:%d", this->maxIdx);

}

void HelloWorld::callbackProgressEnd()
{
    // 进度条的背景
    
    this->removeChildByTag(TAG_PROGRESS_BACK);
    this->removeChildByTag(TAG_PROGRESS_FRONT);

    log("callbackProgressEnd");
    
    for(int i=0;i<this->pieces.size();i++)
    {
        auto p = pieces.at(i);
        if (p->getTag()!=0)
        {
            p->hideValue();
        }
    }
    
    
    
}

void HelloWorld::menuStartGameCallback(Ref* pSender)
{
    log("on start callback");
    this->reset();
    // 切换到另外一个场景
    return;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();
    //this->showTimer();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
    
#endif
}

bool HelloWorld::guessNum(int value)
{
	if (this->curIdx == value)
	{
		this->curIdx++;
		return true;
	}
	else
	{
		return false;
	}
    
}

void HelloWorld::initData()
{
	this->curIdx = 1;
}

bool HelloWorld::isFinished()
{
	return (this->curIdx > this->maxIdx);
}

                                     
void HelloWorld::onClick(Ref* pSender, int idx)
{
    auto *p = this->pieces.at(idx);
    if(p->getTag()==this->curIdx)
    {
        this->curIdx++;
        p->showValue(true);
        
        if (this->curIdx>this->maxIdx)
        {
            this->maxIdx++;
            if (this->maxIdx>MAX_NUM)
            {
                this->restartItem->setVisible(true);
            }
            else{
                // 需要稍微停留0.5秒
                gameStart();
            }
        }
    }
    else{
        this->restartItem->setVisible(true);
        p->showValue(false);
        for(int i=0;i<this->pieces.size();i++)
        {
            auto p = pieces.at(i);
            
            if (p->getTag()>0 && p->isEnabled())
            {
                p->showValue(true);
            }
            
        }
    }

}
