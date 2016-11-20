#ifndef __ATGAECOMMON_H__
#define __ATGAECOMMON_H__
#include "ATlib/com/ATlibCommon.h"
#include "ATlib/math/ATlibMatrix.h"
#include "ATlib/math/ATlibVector2.h"
#include "ATlib/math/ATlibVector3.h"
#include "ATlib/math/ATlibVector4.h"
#include "ATgae/debugger/ATgaeLog.h"

/**
 * Declare.
 */
#define ATCOLOR_ARGB(a, r, g, b)  ((ATColor)((((a)&0x000000FF)<<24)|(((r)&0x000000FF)<<16)|(((g)&0x000000FF)<<8)|((b)&0x000000FF)))
#define ATCOLOR_RGBA(r, g, b, a)  ATCOLOR_ARGB(a, r, g, b)

#define ATCOLOR_A(color)          (int)(color >> 24 & 0x000000FF)
#define ATCOLOR_R(color)          (int)(color >> 16 & 0x000000FF)
#define ATCOLOR_G(color)          (int)(color >> 8 & 0x000000FF)
#define ATCOLOR_B(color)          (int)(color & 0x000000FF)

#define ATCOLOR_AF(color)         (float)(ATCOLOR_A(color) / 255.0f)
#define ATCOLOR_RF(color)         (float)(ATCOLOR_R(color) / 255.0f)
#define ATCOLOR_GF(color)         (float)(ATCOLOR_G(color) / 255.0f)
#define ATCOLOR_BF(color)         (float)(ATCOLOR_B(color) / 255.0f)

#define ATCOLOR_RED               ATCOLOR_ARGB(255, 255, 0, 0)
#define ATCOLOR_GREEN             ATCOLOR_ARGB(255, 0, 255, 0)
#define ATCOLOR_BLUE              ATCOLOR_ARGB(255, 0, 0, 255)
#define ATCOLOR_YELLOW            ATCOLOR_ARGB(255, 255, 255, 0)
#define ATCOLOR_WHITE             ATCOLOR_ARGB(255, 255, 255, 255)
#define ATCOLOR_BLACK             ATCOLOR_ARGB(255, 0, 0, 0)
#define ATCOLOR_PINK              ATCOLOR_ARGB(255, 255, 192, 203)
#define ATCOLOR_ORANGE            ATCOLOR_ARGB(255, 255, 165, 0)
#define ATCOLOR_GRAY              ATCOLOR_ARGB(255, 128, 128, 128)
#define ATCOLOR_BROWN             ATCOLOR_ARGB(255, 165, 42, 42)
#define ATCOLOR_VIOLET            ATCOLOR_ARGB(255, 238, 130, 238)

/**
 * Macro.
 */

// Print information log.
#define LOGI(...)  ATLog::getInstance()->log(LOG_LEVEL_INFO, __VA_ARGS__)
// Print warning log.
#define LOGW(...)  ATLog::getInstance()->log(LOG_LEVEL_WARN, __VA_ARGS__)
// Print error log.
#define LOGE(...)  ATLog::getInstance()->log(LOG_LEVEL_ERROR, __VA_ARGS__)
// Print debug log.
#define LOGD(...)  ATLog::getInstance()->log(LOG_LEVEL_DEBUG, __VA_ARGS__)

/**
 * Engine type.
 */
enum EngineType {
  EngineType_OpenGL,
  EngineType_DirectX
};

#endif // __ATGAECOMMON_H__
