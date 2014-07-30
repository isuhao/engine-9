#include "Controller.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "SoundManager.h"

Controller::Controller()
{
    this->shouldExit = false;
}

void Controller::Start()
{
    // Start the main game loop on a different thread.
    std::thread gameThread(&Controller::gameLoop, this);
    this->viewLoop();
    gameThread.join();
}

static unsigned long getTimeInMilliseconds()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::system_clock::now().time_since_epoch()).count();
}

void Controller::gameLoop()
{
    GameStateManager manager;
    manager.Initialize(new InitialState());

    while(!this->shouldExit)
    {
        unsigned long startTime = getTimeInMilliseconds();

        manager.Update();
        
        while((getTimeInMilliseconds() - startTime) <= Controller::UPDATE_RATE)
        { }
    }
}

void Controller::viewLoop()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(640, 480), "Game Engine");
    //window->setFramerateLimit(1 / this->FRAMERATE); // Do we want this instead of my version?
    
    GraphicsView graphicsView(window); 
    graphicsView.Initialize();
    InputView inputView(window);
    inputView.Initialize();
    SoundView soundView;
    soundView.Initialize();
    ResourceView resourceView;
    resourceView.Initialize();

    // Actual loop
    while(!this->shouldExit)
    {
        unsigned long startTime = getTimeInMilliseconds();

        // Close program on exit
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                this->shouldExit = true;
                window->close();
            }
        }
 
        graphicsView.Update(ControllerPackage::GetActiveControllerPackage()->GetGraphicsManager());
        inputView.Update(ControllerPackage::GetActiveControllerPackage()->GetInputManager());
        soundView.Update(ControllerPackage::GetActiveControllerPackage()->GetSoundManager());
        resourceView.Update(ControllerPackage::GetActiveControllerPackage()->GetResourceManager());
        
        window->display();
        while((getTimeInMilliseconds() - startTime) <= Controller::FRAMERATE)
        { }
    }
    
    //glfwDestroyWindow(window);
    //glfwTerminate();
}

