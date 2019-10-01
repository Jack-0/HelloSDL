//
// Created by jack on 31/05/19.
//

#include "PlayState.h"


const std::string PlayState::s_playID = "PLAY";


void PlayState::update()
{
    if(gameOver)
    {
        Player *pPlayerCast = dynamic_cast<Player*>(pPlayer);
        pPlayerCast->kill(); // set player alive to dead
        TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
        return;
    }

    // if escape is pressed enter the pause state
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());

    // add a new balloon, if the maximum is not reached
    if(m_gameObjects.size() < MAX_GAMEOBJECTS)
        addEnemy();

    // update projectile handler
    pProjectileHandler->update();

    // update player
    pPlayer->update();

    // update all game objects
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        // check to see if the enemy is alive, if not remove it
        if(!checkAlive(static_cast<SDLGameObject*>(m_gameObjects[i])))
        {
            m_gameObjects[i]->clean();
            m_gameObjects.erase(m_gameObjects.begin() + i);
        }
        m_gameObjects[i]->update();
    }

    // update the visible score
    scoreText->changeText(std::to_string(score));
}


void PlayState::render()
{
    if(!gameOver)
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
        pPlayer->draw();
        pProjectileHandler->draw();
    }

    scoreText->draw();
}


bool PlayState::onEnter()
{
    initTextures();

    // create a Player and assign it to the pPlayer (pointer to player)
    pPlayer = new Player(new LoaderParams(TheGame::Instance()->getScreenWidth()/2,TheGame::Instance()->getScreenHeight()/2,38,52,"head",1));

    // add projectile handler
    pProjectileHandler = new ProjectileHandler();

    scoreText = new Text( TheGame::Instance()->getScreenWidth() - 100, 0, std::to_string(score));

    // Setup a thead for handling collisions
    // give the player a pointer to the projectile handler
    Player *pPlayerCast = dynamic_cast<Player*>(pPlayer); // dynamic due to hierarchies and inheritance
    pPlayerCast->addProjectileManager(pProjectileHandler);
    // create a thread for collisions (massive performance boost)
    m_collisionThread = std::thread(&PlayState::checkAllCollisions, this);
    // detach this thread (don't wait for it, let it run parallel)
    m_collisionThread.detach();

    std::cout << "Entering play state\n";
    return true;
}


void PlayState::initTextures()
{
    // load needed textures into TheTextureManager
    TheTextureManager::Instance()->load("../res/mob/head.png", "head", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("../res/mob/tail.png", "tail", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("../res/mob/hat.png", "hat", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("../res/mob/projectile.png", "projectile", TheGame::Instance()->getRenderer());
    m_textureIDs.push_back("head");
    m_textureIDs.push_back("tail");
    m_textureIDs.push_back("hat");
    m_textureIDs.push_back("projectile");

    // generate colours for balloons.. note red is not pure red; green is not pure green; etc.
    SDL_Color red;
    SDL_Color green;
    SDL_Color blue;
    red.r = 200; red.g = 0; red.b = 120; red.a = 0;
    green.r = 0; green.g = 200; green.b = 120; green.a = 0;
    blue.r = 0; blue.g = 120; blue.b = 200; blue.a = 0;
    // Generate red green and blue textures from default pink head image
    m_textureIDs.push_back("head_r");
    m_textureIDs.push_back("head_g");
    m_textureIDs.push_back("head_b");
    TheTextureManager::Instance()->loadWithNewColour("../res/mob/head.png", "head_r", TheGame::Instance()->getRenderer(), red);
    TheTextureManager::Instance()->loadWithNewColour("../res/mob/head.png", "head_g", TheGame::Instance()->getRenderer(), green);
    TheTextureManager::Instance()->loadWithNewColour("../res/mob/head.png", "head_b", TheGame::Instance()->getRenderer(), blue);
}


/**
 * PlayState::checkCollisions() is a threaded method.
 * While the player is alive:
 *  Checks collisions between the player and enemies
 *  Checks collisions between enemies and projectiles
 *
 * if there is a player collision the game-over state is applied
 */
void PlayState::checkAllCollisions()
{
    // dynamically cast the pPlayer pointer to a Player to use needed methods
    Player *pPlayerCast = dynamic_cast<Player*>(pPlayer);

    // wait 300 ms for objects to initialise properly. Due to thread checking before full init
    SDL_Delay(500); // TODO could be a better way of checking that objects are initialised

    // the player is alive
    while(pPlayerCast->alive())
    {
        if(!m_gameObjects.empty())
        {
            for(int i = 0; i <m_gameObjects.size(); i++)
            {
                // check for player collisions with enemies
                if(checkPlayerEnemyCollision(static_cast<SDLGameObject *>(m_gameObjects[i])))
                {
                    gameOver = true;
                }

                // check index game object against all projectiles O(n^2)
                if(pProjectileHandler->collision(static_cast<SDLGameObject*>(m_gameObjects[i])))
                    score+=1;
            }
        }
    }
}


bool PlayState::onExit()
{
    // order matters here due to threading, the projectile handler is removed first to prevent it looking at a
    // gameObject that is currently being cleaned.
    pProjectileHandler->clean();

    // clean all game objects
    for(int i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->clean();

    // remove all game objects from the vector
    m_gameObjects.clear();

    // remove textures for TheTextureManager
    for (int i = 0; i < m_textureIDs.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDs[i]);

    // clean the player last
    pPlayer->clean();

    std::cout << "Exiting play state\n";
    return true;
}


bool PlayState::checkPlayerEnemyCollision(SDLGameObject *enemy)
{
    SDLGameObject* player = dynamic_cast<SDLGameObject*>(pPlayer);

    int leftA, leftB, rightA, rightB;
    int topA, topB, bottomA, bottomB;

    leftA = player->getPosition().getX();
    rightA = player->getPosition().getX() + player->getWidth();
    topA = player->getPosition().getY();
    bottomA = player->getPosition().getY() + player->getHeight();

    leftB = enemy->getPosition().getX();
    rightB = enemy->getPosition().getX() + enemy->getWidth();
    topB = enemy->getPosition().getY();
    bottomB = enemy->getPosition().getY() + enemy->getHeight();

    if(bottomA <= topB) {return false;}
    if(topA >= bottomB) {return false;}
    if(rightA <= leftB) {return false;}
    if(leftA >= rightB) {return false;}

    return true;
}


void PlayState::addEnemy(){
    // the head_type is the textureID that will be assigned to the balloon
    std::string head_type = "";

    // randomly assign a head textureID
    switch(TheGame::Instance()->getRandom(0,2))
    {
        case 0: head_type = "head_r"; break;
        case 1: head_type = "head_g"; break;
        case 2: head_type = "head_b"; break;
    }
    // create and add balloon to game objects (balloon type based on the random balloon choice)
    auto SCREEN_HEIGHT = TheGame::Instance()->getScreenHeight();
    m_gameObjects.push_back(new Enemy(new LoaderParams(-70, TheGame::Instance()->getRandom(-10, SCREEN_HEIGHT -51) ,38, 52, head_type, 1)));
}


bool PlayState::checkAlive(SDLGameObject *p)
{
    return p->alive();
}
