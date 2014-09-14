#include "ControllerPackage.h"

ControllerPackage* ControllerPackage::activeControllerPackage = nullptr;

ControllerPackage::ControllerPackage(GraphicsManager* const graphicsManager, InputManager* const inputManager, SoundManager* const soundManager)
: graphicsManager(graphicsManager),
inputManager(inputManager),
soundManager(soundManager)
{
	
}

ControllerPackage::~ControllerPackage()
{
	delete this->graphicsManager;
	delete this->inputManager;
	delete this->soundManager;
        delete this->resourceManager;
}

GraphicsManager* ControllerPackage::GetGraphicsManager()
{
	return this->graphicsManager;
}


InputManager* ControllerPackage::GetInputManager()
{
	return this->inputManager;
}

SoundManager* ControllerPackage::GetSoundManager()
{
	return this->soundManager;
}

ResourceManager* ControllerPackage::GetResourceManager()
{
    return this->resourceManager;
}

void ControllerPackage::Activate()
{
    ControllerPackage::activeControllerPackage = this;
}

ControllerPackage* ControllerPackage::GetActiveControllerPackage()
{
    return ControllerPackage::activeControllerPackage;
}
