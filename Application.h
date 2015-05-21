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
   virtual void onKey(const scv::KeyEvent &evt);
   virtual void onSizeChange(void);

protected:
   static const int s_defaultWindowWidth = 1280;
   static const int s_defaultWindowHeight = 720;
   scv::Panel *_mainPanel;
private:
};

#endif //__APPLICATION_H__
