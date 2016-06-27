//
//  UI.cpp
//  TicTacToePractise
//
//  Created by Sonar Systems on 22/03/2016.
//
//

#include "UI.h"
#include "SonarFrameworks.h"
#include "Definitions.h"
#include "GameScene.h"
#include "MainMenuScene.h"

UI::UI( cocos2d::Layer *layer, int &gameState )
{
    this->gameState = &gameState;
    
    Size screenSize = Director::getInstance( )->getVisibleSize( );
    Vec2 origin = Director::getInstance( )->getVisibleOrigin( );

    MenuItemSprite *pauseItem = MenuItemSprite::create( Sprite::create( PAUSE_BUTTON ), Sprite::create( PAUSE_BUTTON_PRESSED ), Sprite::create( PAUSE_BUTTON_PRESSED ), CC_CALLBACK_1( UI::PauseGame, this ) );
    pauseItem->setPosition( Vec2( screenSize.width - ( pauseItem->getContentSize( ).width / 2 ) + origin.x, screenSize.height - ( pauseItem->getContentSize( ).height / 2 ) + origin.y ) );
    
    Menu *menuButtons = Menu::create( pauseItem, NULL );
    menuButtons->setPosition( Vec2::ZERO );
    layer->addChild( menuButtons );
    
    pausebackground = Sprite::create( PAUSE_BACKGROUND );
    pausebackground->setPosition( SonarCocosHelper::UI::GetScreenCenter( ) );
    pausebackground->setOpacity( 0 );
    layer->addChild( pausebackground );
    
    
    MenuItemImage *overlayPauseWindowItem = MenuItemImage::create( PAUSE_WINDOW, PAUSE_WINDOW, PAUSE_WINDOW, NULL );
    MenuItemSprite *resumeItem = MenuItemSprite::create( Sprite::create( RESUME_BUTTON ), Sprite::create( RESUME_BUTTON_PRESSED ), Sprite::create( RESUME_BUTTON ), CC_CALLBACK_1( UI::PauseGame, this ) );
    resumeItem->setPosition( Vec2( -overlayPauseWindowItem->getContentSize( ).width / 4, resumeItem->getPositionY( ) ) );
    MenuItemSprite *mainMenuItem = MenuItemSprite::create( Sprite::create( HOME_BUTTON ), Sprite::create( HOME_BUTTON_PRESSED ), Sprite::create( HOME_BUTTON_PRESSED ), CC_CALLBACK_1( UI::GoToMainMenu, this ) );
    mainMenuItem->setPosition( Vec2( overlayPauseWindowItem->getContentSize( ).width / 4, mainMenuItem->getPositionY( ) ) );
    
    pauseMenu = Menu::create( overlayPauseWindowItem, resumeItem, mainMenuItem, NULL );
    pauseMenu->setPosition( Vec2( SonarCocosHelper::UI::GetScreenCenter( ).x, SonarCocosHelper::UI::GetScreenCenter( ).y + screenSize.height ) );
    layer->addChild( pauseMenu );
}

void UI::ShowGameOver( cocos2d::Layer *layer )
{
    Size screenSize = Director::getInstance( )->getVisibleSize( );

    Sprite *background = Sprite::create( GAME_OVER_BACKGROUND );
    background->setPosition( SonarCocosHelper::UI::GetScreenCenter( ) );
    background->setOpacity( 0 );
    layer->addChild( background );
    background->runAction( Sequence::create( DelayTime::create( PIECE_FADE_IN_TIME * 2.5 ), FadeIn::create( GAME_OVER_BACKGROUND_FADE_IN_TIME ), NULL ) );
    
    MenuItemImage *overlayWindowItem = MenuItemImage::create( GAME_OVER_WINDOW, GAME_OVER_WINDOW, GAME_OVER_WINDOW, NULL );
    MenuItemSprite *retryItem = MenuItemSprite::create( Sprite::create( RETRY_BUTTON ), Sprite::create( RETRY_BUTTON_PRESSED ), Sprite::create( RETRY_BUTTON ), CC_CALLBACK_1( UI::Retry, this ) );
    retryItem->setPosition( Vec2( overlayWindowItem->getContentSize( ).width / 4, retryItem->getPositionY( ) ) );
    MenuItemSprite *mainMenuItem = MenuItemSprite::create( Sprite::create( HOME_BUTTON ), Sprite::create( HOME_BUTTON_PRESSED ), Sprite::create( HOME_BUTTON_PRESSED ), CC_CALLBACK_1( UI::GoToMainMenu, this ) );
    mainMenuItem->setPosition( Vec2( -overlayWindowItem->getContentSize( ).width / 4, mainMenuItem->getPositionY( ) ) );
    
    
    Menu *menu = Menu::create( overlayWindowItem, retryItem, mainMenuItem, NULL );
    menu->setPosition( Vec2( SonarCocosHelper::UI::GetScreenCenter( ).x, SonarCocosHelper::UI::GetScreenCenter( ).y + screenSize.height ) );
    layer->addChild( menu );
    

    EaseBounceOut *menuActionEasing = EaseBounceOut::create( MoveTo::create( MENU_MOVE_BOUNCE_DURATION, SonarCocosHelper::UI::GetScreenCenter( ) ) );
    Sequence *menuShowSeq = Sequence::create( DelayTime::create( PIECE_FADE_IN_TIME * 2.5 ), menuActionEasing, NULL );
    menu->runAction( menuShowSeq );
}

void UI::Retry( cocos2d::Ref *pSender )
{
    Scene *scene = GameScene::createScene( );
    TransitionFade *transition = TransitionFade::create( SCENE_TRANSITION_TIME, scene );
    
    Director::getInstance( )->replaceScene( transition );
}

void UI::GoToMainMenu( cocos2d::Ref *pSender )
{
    Scene *scene = MainMenuScene::createScene( );
    TransitionFade *transition = TransitionFade::create( SCENE_TRANSITION_TIME, scene );
    
    Director::getInstance( )->replaceScene( transition );
}

void UI::PauseGame( cocos2d::Ref *pSender )
{
    Size screenSize = Director::getInstance( )->getVisibleSize( );
    
    if ( STATE_PLAYING == *gameState )
    {
        *gameState = STATE_PAUSED;
        pausebackground->runAction( FadeIn::create( PAUSE_BACKGROUND_FADE_TIME ) );
        
        EaseBounceOut *menuActionEasing = EaseBounceOut::create( MoveTo::create( MENU_MOVE_BOUNCE_DURATION, SonarCocosHelper::UI::GetScreenCenter( ) ) );
        pauseMenu->runAction( menuActionEasing );
    }
    else if ( STATE_PAUSED == *gameState )
    {
        *gameState = STATE_PLAYING;
        pausebackground->runAction( FadeOut::create( PAUSE_BACKGROUND_FADE_TIME ) );
        
        EaseBounceOut *menuActionEasing = EaseBounceOut::create( MoveTo::create( MENU_MOVE_BOUNCE_DURATION, Vec2( SonarCocosHelper::UI::GetScreenCenter( ).x, SonarCocosHelper::UI::GetScreenCenter( ).y + screenSize.height ) ) );
        pauseMenu->runAction( menuActionEasing );
    }
}