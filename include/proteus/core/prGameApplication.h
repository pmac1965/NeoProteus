// File: prGameApplication.h
/**
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


#pragma once
//#ifndef _PRGAMEAPPLICATION_H
//#define _PRGAMEAPPLICATION_H


#include <OgreRoot.h>
#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>


//#include <CEGUI/CEGUI.h>
//#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>


class prGameApplication : public Ogre::WindowEventListener
                        , public Ogre::FrameListener
                        , public OIS::KeyListener
                        , public OIS::MouseListener
{
public:
    prGameApplication();
    virtual ~prGameApplication();

    bool go();

private:
    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;

    // Ogre::WindowEventListener
    virtual void windowResized(Ogre::RenderWindow* rw) override;
    virtual void windowClosed(Ogre::RenderWindow* rw) override;

    //
    virtual bool keyPressed(const OIS::KeyEvent& ke) override;
    virtual bool keyReleased(const OIS::KeyEvent& ke) override;
 
    //
    virtual bool mouseMoved(const OIS::MouseEvent& me) override;
    virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id) override;
    virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id) override;

    //
    Ogre::Root*         mRoot;
    Ogre::RenderWindow* mWindow;
    Ogre::SceneManager* mSceneMgr;
    Ogre::Camera*       mCamera;
    OIS::InputManager*  mInputManager;
    OIS::Mouse*         mMouse;
    OIS::Keyboard*      mKeyboard;
    Ogre::String        mResourcesCfg;
    Ogre::String        mPluginsCfg;
};


//#endif // _PRGAMEAPPLICATION_H
