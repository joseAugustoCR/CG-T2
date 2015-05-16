#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <SCV/SCV.h>
#include "Widget.h"

extern bool buttonAccelerate;
extern bool buttonBreak;

class Application : public scv::Kernel {
public:
   ///////////////////////////////////////////////////////////
   Application(void);
   virtual ~Application(void);
   ///////////////////////////////////////////////////////////

   void init(void);

   //SCVCallbacks
   ///////////////////////////////////////////////////////////
 /*  virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold (const scv::MouseEvent &evt);
   virtual void onMouseOver (const scv::MouseEvent &evt);
   virtual void onMouseUp   (const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);
   virtual void onPositionChange(void);
   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp     (const scv::KeyEvent &evt);*/
   virtual void onKey(const scv::KeyEvent &evt);

   virtual void onSizeChange(void);
  
   ///////////////////////////////////////////////////////////

protected:
   static const int s_defaultWindowWidth = 1280;
   static const int s_defaultWindowHeight = 720;
   scv::Panel *_mainPanel;
private:
};

#endif //__APPLICATION_H__
