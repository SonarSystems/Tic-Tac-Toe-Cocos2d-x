#pragma once

#include "cocos2d.h"
#include "AI.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
private:
    // called when the touch first begins
    bool onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event );
    // called when the user moves their finger
    void onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *event );
    // called when the user lifts their finger
    void onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *event );
    // called when the device goes to another application such as a phone call
    void onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *event );
    
    // Setup the grid rects so we can detect which space the user has clicked
    void InitGridRects( );
    void InitGridPieces( );
    
    // check if the user has clicked an empty grid space, if so place their piece
    void CheckAndPlacePiece( cocos2d::Touch *touch );
    // check if the user has won
    void CheckWin( int x, int y );
    // check a particular set of pieces
    void Check3PiecesForMatch( int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck );
    
    cocos2d::Sprite *gridSprite;
    cocos2d::Rect gridSpaces[3][3];
    cocos2d::Sprite *gridPieces[3][3];
    int gridArray[3][3];
    
    int turn;
    
    int gameState;
    
    AI *ai;
    
};