#include "MainMenuScene.h"
#include "GameScene.h"
#include "SonarCocosHelperCPP/SonarFrameworks.h"
#include "Definitions.h"

#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC_EXT;
using namespace ui;

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size screenSize = Director::getInstance( )->getVisibleSize( );
    Vec2 origin = Director::getInstance( )->getVisibleOrigin( );
    
    SonarCocosHelper::UI::AddCentredBackground( MAIN_MENU_BACKGROUND_FILEPATH, this );
    
    Sprite *title = Sprite::create( MAIN_MENU_TITLE_FILEPATH );
    title->setPosition( Vec2( screenSize.width / 2 + origin.x, screenSize.height * 0.75 + origin.y ) );
    this->addChild( title );
    
    Button *playButton = Button::create( MAIN_MENU_PLAY_BUTTON, MAIN_MENU_PLAY_BUTTON_PRESSED );
    playButton->setPosition( SonarCocosHelper::UI::GetScreenCenter( ) );
    this->addChild( playButton );
    
    playButton->addTouchEventListener( CC_CALLBACK_2( MainMenuScene::touchEvent, this ) );
    playButton->setTag( TAG_MAIN_MENU_PLAY_BUTTON );
    
    Sprite *playButtonOuter = Sprite::create( MAIN_MENU_PLAY_BUTTON_OUTER );
    playButtonOuter->setPosition( SonarCocosHelper::UI::GetScreenCenter( ) );
    this->addChild( playButtonOuter );
    
    SonarCocosHelper::UI ui;
    
    ui.AddAudioToggle( SOUND_ON_BUTTON, SOUND_ON_BUTTON_PRESSED, SOUND_OFF_BUTTON, SOUND_OFF_BUTTON_PRESSED, this, SonarCocosHelper::UIButtonPosition::eBottomRight );
    
    Button *achievementsButton = Button::create( ACHIEVEMENTS_BUTTON, ACHIEVEMENTS_BUTTON_PRESSED );
    achievementsButton->setPosition( SonarCocosHelper::UI::GetScreenCorner( SonarCocosHelper::UIButtonPosition::eBottomLeft, achievementsButton ) );
    this->addChild( achievementsButton );
    
    achievementsButton->addTouchEventListener( CC_CALLBACK_2( MainMenuScene::touchEvent, this ) );
    achievementsButton->setTag( TAG_ACHIEVEMENTS_BUTTON );
    
    return true;
}

void MainMenuScene::touchEvent( Ref *sender, Widget::TouchEventType type )
{
    Node *node = ( Node * )sender;
    
    switch ( type )
    {
        case Widget::TouchEventType::BEGAN:
            // code to handle when the button is first clicked
            break;
            
        case Widget::TouchEventType::MOVED:
            // code to handle when the user is moving their finger/cursor whilst clicking the button
            break;
            
        case Widget::TouchEventType::ENDED:
            // code to handle when the button click has ended (e.g. finger is lifted off the screen)
            if ( TAG_MAIN_MENU_PLAY_BUTTON == node->getTag( ) )
            {
                Scene *scene = GameScene::createScene( );
                TransitionFade *transition = TransitionFade::create( SCENE_TRANSITION_TIME, scene );
                
                Director::getInstance( )->replaceScene( transition );
            }
            else if ( TAG_ACHIEVEMENTS_BUTTON == node->getTag( ) )
            {
                SonarCocosHelper::GameCenter::showAchievements( );
                SonarCocosHelper::GooglePlayServices::showAchievements( );
            }
            
            break;
            
        case Widget::TouchEventType::CANCELED:
            // code to handle when the button click has been cancelled,  this is usually handled the same way as ENDED in most applications (e.g. another application takes control of the device)
            break;
            
        default:
            break;
    }
}