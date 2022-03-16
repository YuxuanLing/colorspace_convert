#ifndef _TIMER_H_
#define _TIMER_H_

#include <windows.h>

#define  TRACE_QUERY_START                  LARGE_INTEGER startTime;   \
                                            LARGE_INTEGER endTime;     \
                                            LARGE_INTEGER lastTime;    \
                                            LARGE_INTEGER frequency;   \
                                            double cpuFrequency;       \
                                            double elapsedTimeInMS = 0.0f; \
                                            QueryPerformanceFrequency(&frequency);        \
                                            cpuFrequency = (double)(frequency.QuadPart);  \
                                            QueryPerformanceCounter(&startTime);          \
                                            QueryPerformanceCounter(&lastTime);


#define  TRACE_QUERY_FROM_START(fmt, ...)   QueryPerformanceCounter(&endTime);                  \
                                            elapsedTimeInMS = (double)(endTime.QuadPart - startTime.QuadPart) * 1000.0f / cpuFrequency;   \
                                            simple_logger(fmt , __VA_ARGS__);  \
                                            QueryPerformanceCounter(&lastTime);

#define  TRACE_QUERY_FROM_LAST(fmt, ...)    QueryPerformanceCounter(&endTime);                  \
                                            elapsedTimeInMS = (double)(endTime.QuadPart - lastTime.QuadPart) * 1000.0f / cpuFrequency;   \
                                            simple_logger(fmt , __VA_ARGS__);  \
                                            QueryPerformanceCounter(&lastTime);


#endif // _TIMER_H
