//-----------------------------------------------------------------------------
// Lonewolff
//
// Filename:    OgreText.h
// Description: Class for simple text in Ogre (Version 040507:18.30)
//-----------------------------------------------------------------------------
 
 
#ifndef __OgreText_H__
#define __OgreText_H__


#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>
#include <Overlay/OgreTextAreaOverlayElement.h>
#include <OgreStringConverter.h>

//using namespace Ogre;

class OgreText
{
public:
    OgreText()
    {
        olm = Ogre::OverlayManager::getSingletonPtr();
        if(init==0)
        {
        panel=static_cast<Ogre::OverlayContainer*>(olm->createOverlayElement("Panel","GUI"));
            panel->setMetricsMode(Ogre::GMM_PIXELS);
            panel->setPosition(0,0);
            panel->setDimensions(1.0f,1.0f);
            overlay=olm->create("GUI_OVERLAY");
            overlay->add2D(panel);
        }
        ++(this->init);
        szElement="element_"+Ogre::StringConverter::toString(init);
        overlay=olm->getByName("GUI_OVERLAY");
        panel=static_cast<Ogre::OverlayContainer*>(olm->getOverlayElement("GUI"));
        textArea=static_cast<Ogre::TextAreaOverlayElement*>(olm->createOverlayElement("TextArea",szElement));
        panel->addChild(textArea);
        overlay->show();
    }
    ~OgreText()
    {
        szElement="element_"+Ogre::StringConverter::toString(init);
        olm->destroyOverlayElement(szElement);
        --(this->init);
        if(init==0)
        {
            olm->destroyOverlayElement("GUI");
            olm->destroy("GUI_OVERLAY");
        }
    }
    void setText(char *szString)
    {
        textArea->setCaption(szString);
        textArea->setDimensions(1.0f,1.0f);
        textArea->setMetricsMode(Ogre::GMM_RELATIVE);
        textArea->setFontName("BlueHighway");
        textArea->setCharHeight(0.03f);
    }
    void setText(Ogre::String szString) // now You can use Ogre::String as text
    {
        textArea->setCaption(szString);
        textArea->setDimensions(1.0f,1.0f);
        textArea->setMetricsMode(Ogre::GMM_RELATIVE);
        textArea->setFontName("BlueHighway");
        textArea->setCharHeight(0.03f);
    }
    void setPos(float x,float y)
    {
        textArea->setPosition(x,y);
    }
    void setCol(float R,float G,float B,float I)
    {
        textArea->setColour(Ogre::ColourValue(R,G,B,I));
    }
private:
    Ogre::OverlayManager *olm;
    Ogre::OverlayContainer *panel ;
    Ogre::Overlay *overlay;
    Ogre::TextAreaOverlayElement *textArea;
    static int init;
    Ogre::String szElement;
};
 
int OgreText::init=0;
 
#endif
