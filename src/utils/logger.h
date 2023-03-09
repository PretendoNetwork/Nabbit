#pragma once
#include <cstring>
#include <coreinit/debug.h>
#include <whb/log.h>

#define __FILENAME__ ({                                \
    const char *__filename = __FILE__;                 \
    const char *__pos      = strrchr(__filename, '/'); \
    if (!__pos) __pos = strrchr(__filename, '\\');     \
    __pos ? __pos + 1 : __filename;                    \
})

#define LOG_APP_TYPE "L"
#define LOG_APP_NAME "Nabbit"

#define LOG_EX(FILENAME, FUNCTION, LINE, LOG_LEVEL, LINE_END, FMT, ARGS...)                                                                      \
    do {                                                                                                                                         \
        OSReport("[(%s)%18s][%23s]%30s@L%04d: " LOG_LEVEL "" FMT "" LINE_END, LOG_APP_TYPE, LOG_APP_NAME, FILENAME, FUNCTION, LINE, ##ARGS);     \
        WHBLogPrintf("[(%s)%18s][%23s]%30s@L%04d: " LOG_LEVEL "" FMT "" LINE_END, LOG_APP_TYPE, LOG_APP_NAME, FILENAME, FUNCTION, LINE, ##ARGS); \
    } while (0)

#define LOG_EX_DEFAULT(LOG_LEVEL, LINE_END, FMT, ARGS...) LOG_EX(__FILENAME__, __FUNCTION__, __LINE__, LOG_LEVEL, LINE_END, FMT, ##ARGS)

#define DEBUG_FUNCTION_LINE(FMT, ARGS...)      LOG_EX_DEFAULT("##INFO## ", "\n", FMT, ##ARGS)
#define DEBUG_FUNCTION_LINE_ERR(FMT, ARGS...)  LOG_EX_DEFAULT("##ERROR## ", "\n", FMT, ##ARGS)
#define DEBUG_FUNCTION_LINE_WARN(FMT, ARGS...) LOG_EX_DEFAULT("##WARNING## ", "\n", FMT, ##ARGS)

void initLogging();
void deinitLogging();