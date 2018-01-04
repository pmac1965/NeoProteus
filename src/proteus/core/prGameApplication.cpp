/**
 * prGameApplication.cpp
 *
 *  Copyright 2016 Paul Michael McNab
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


#include "core/prTypes.h"


#if 0
#include <proteus/core/prGameApplication.h>


prGameApplication::prGameApplication()
	: mRoot			(nullptr)
	, mWindow		(nullptr)
	, mSceneMgr		(nullptr)
	, mCamera		(nullptr)
	, mInputManager (nullptr)
	, mMouse		(nullptr)
	, mKeyboard		(nullptr)
	, mResourcesCfg	(Ogre::StringUtil::BLANK)
	, mPluginsCfg	(Ogre::StringUtil::BLANK)
{
}


prGameApplication::~prGameApplication()
{
	// Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);

	delete mRoot;
}


bool prGameApplication::go()
{
#ifdef _DEBUG
  mResourcesCfg = "resources_d.cfg";
  mPluginsCfg   = "plugins_d.cfg";
#else
  mResourcesCfg = "resources.cfg";
  mPluginsCfg   = "plugins.cfg";
#endif
 
	mRoot = new Ogre::Root(mPluginsCfg);

	// Set resource paths
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	Ogre::String name, locType;
	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();
	while (secIt.hasMoreElements())
	{
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;
	
		for (it = settings->begin(); it != settings->end(); ++it)
		{
			locType = it->first;
			name = it->second;
			std::cerr << "LOCTYPE: " << locType << ", NAME: " << name << std::endl;

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
		}
	}


	// Configure the render system
	// Add exception if false
	if(!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
		return false;

	mWindow = mRoot->initialise(true, "prGameApplication Render Window");

	// Init resources
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


	// Set scene maanger
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);


	// Set main camera
	mCamera = mSceneMgr->createCamera("MainCam");
	mCamera->setPosition(0, 0, 80);
	mCamera->lookAt(0, 0, -300);
	mCamera->setNearClipDistance(5);

	// Add view port
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
 
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
 
	mCamera->setAspectRatio(
	  Ogre::Real(vp->getActualWidth()) / 
	  Ogre::Real(vp->getActualHeight()));

//// Ogre head
//Ogre::Entity* ogreEntity = mSceneMgr->createEntity("ogrehead.mesh");
// 
//Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
//ogreNode->attachObject(ogreEntity);
// 
//mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
// 
//Ogre::Light* light = mSceneMgr->createLight("MainLight");
//light->setPosition(20, 80, 50);


//CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
//  CEGUI::Font::setDefaultResourceGroup("Fonts");
 // CEGUI::Scheme::setDefaultResourceGroup("Schemes");
 // CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
 // CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
 
 // CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
 // CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");
 
//  CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
 
 // context.setDefaultFont("DejaVuSans-10");
//  context.getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
 

    // Setup OIS
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
 
    OIS::ParamList pl;
    size_t windowHandle = 0;
    std::ostringstream windowHandleStr;
 
    mWindow->getCustomAttribute("WINDOW", &windowHandle);
    windowHandleStr << windowHandle;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));
 
    mInputManager = OIS::InputManager::createInputSystem(pl);
 
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, false));
    mMouse    = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, false));
    mKeyboard->setEventCallback(this);
    mMouse->setEventCallback(this);


    // win events
	windowResized(mWindow);
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);


	//// Render loop
	//while(true)
	//{
	//  Ogre::WindowEventUtilities::messagePump();
 //
	//  if(mWindow->isClosed()) return false;
 //
	//  if(!mRoot->renderOneFrame()) return false;
	//}
	mRoot->addFrameListener(this);
	mRoot->startRendering();

    return true;
}


bool prGameApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if (mWindow->isClosed())
        return false;
 
    // Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();
 
    if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
        return false;
 
    return true;
}


void prGameApplication::windowResized(Ogre::RenderWindow* rw)
{
  int left, top;
  unsigned int width, height, depth;
 
  rw->getMetrics(width, height, depth, left, top);
 
  const OIS::MouseState& ms = mMouse->getMouseState();
  ms.width = width;
  ms.height = height;
}

 
void prGameApplication::windowClosed(Ogre::RenderWindow* rw)
{
  if(rw == mWindow)
  {
    if(mInputManager)
    {
      mInputManager->destroyInputObject(mMouse);
      mInputManager->destroyInputObject(mKeyboard);
 
      OIS::InputManager::destroyInputSystem(mInputManager);
      mInputManager = 0;
    }
  }
}


bool prGameApplication::keyPressed(const OIS::KeyEvent& ke)
{
	return true;
}

bool prGameApplication::keyReleased(const OIS::KeyEvent& ke)
{
	return true;
}
 
	//
bool prGameApplication::mouseMoved(const OIS::MouseEvent& me)
{
	return true;
}

bool prGameApplication::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id)
{
	return true;
}


bool prGameApplication::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id)
{
	return true;
}


//void prGameApplication::createScene(void)
//{
//    // Create your scene here :)
//}
//

#endif
