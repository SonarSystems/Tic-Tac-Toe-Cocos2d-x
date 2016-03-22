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

UI::UI( cocos2d::Layer *layer )
{
    
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