#ifndef __ATGAECOMMON_H__
#define __ATGAECOMMON_H__
#include "ATlib/com/ATlibCommon.h"
#include "ATgae/debugger/ATgaeLog.h"

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
