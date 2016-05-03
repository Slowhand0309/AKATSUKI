
#include "ATgae/engine/window/ATgaeWindowInfo.h"

/**
 * Constructor.
 */
ATWindowInfo::ATWindowInfo()
  : ml_nHeight(0)
  , ml_nWidth(0)
  , ml_nDispHeight(0)
  , ml_nDispWidth(0)
  , ml_szWindowTitle(_T(""))
  , ml_bWindowMode(true)
{

}

/**
 * Destructor.
 */
ATWindowInfo::~ATWindowInfo() {
}

/**
 * Get height size for client window.
 *
 * @return size
 */
unsigned int ATWindowInfo::getHeight()
{
  return ml_nHeight;
}

/**
 * Set height size for client window.
 *
 * @param unsigned int nHeight size
 */
void ATWindowInfo::setHeight(unsigned int height)
{
  ml_nHeight = height;
}

/**
 * Get width size for client window.
 *
 * @return size
 */
unsigned int ATWindowInfo::getWidth()
{
  return ml_nWidth;
}

/**
 * Set width size for client window.
 *
 * @param size
 */
void ATWindowInfo::setWidth(unsigned int width)
{
  ml_nWidth = width;
}

/**
 * Get height size for display window.
 *
 * @return size
 */
unsigned int ATWindowInfo::getDispHeight()
{
  return ml_nDispHeight;
}

/**
 * Set height size for client window.
 *
 * @param size
 */
void ATWindowInfo::setDispHeight(unsigned int dispHeight)
{
  ml_nDispHeight = dispHeight;
}

/**
 * Get width size for display window.
 *
 * @return size
 */
unsigned int ATWindowInfo::getDispWidth()
{
  return ml_nDispWidth;
}

/**
 * Set width size for client window.
 *
 * @param size
 */
void ATWindowInfo::setDispWidth(unsigned int dispWidth)
{
  ml_nDispWidth = dispWidth;
}

/**
 * Get width title.
 *
 * @return title string
 */
TString ATWindowInfo::getWindowTitle()
{
  return ml_szWindowTitle;
}

/**
 * Set width title.
 *
 * @param title string
 */
void ATWindowInfo::setWindowTitle(const TString &windowTitle)
{
  ml_szWindowTitle = windowTitle;
}

/**
 * Get width mode.
 *
 * @return true : window / false : fullscreen
 */
bool ATWindowInfo::isWindowMode()
{
  return ml_bWindowMode;
}

/**
 * Set width mode.
 *
 * @param true : window / false : fullscreen
 */
void ATWindowInfo::setWindowMode(bool windowMode)
{
  ml_bWindowMode = windowMode;
}
