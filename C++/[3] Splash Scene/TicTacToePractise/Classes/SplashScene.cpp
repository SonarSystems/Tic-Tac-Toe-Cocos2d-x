#include "SplashScene.h"
#include "SonarFrameworks.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    SonarCocosHelper::GameCenter::signIn( );
    
    Size screenSize = Director::getInstance( )->getVisibleSize( );
    Vec2 origin = Director::getInstance( )->getVisibleOrigin( );
    
    Sprite *backgroundSprite = Sprite::create( SPLASH_SCENE_BACKGROUND_FILEPATH );
    backgroundSprite->setPosition( Vec2( screenSize.width / 2 + origin.x, screenSize.height / 2 + origin.y ) );
    this->addChild( backgroundSprite );
    
    scheduleOnce( schedule_selector( SplashScene::SwitchToMainMenu ), SPLASH_SCENE_SHOW_TIME );
    
    return true;
}

void SplashScene::SwitchToMainMenu( float dt )
{
    Scene *scene = MainMenuScene::createScene( );
    TransitionFade *transition = TransitionFade::create( SCENE_TRANSITION_TIME, scene );
    
    Director::getInstance( )->replaceScene( transition );
}