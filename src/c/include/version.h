#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define GANDALF_VERSION "1.0.0"
#define GANDALF_VERSION_MAJOR 1
#define GANDALF_VERSION_MINOR 0
#define GANDALF_VERSION_REVISION 0

void gandalf_version(int *major, int *minor, int *revision);

#ifdef __cplusplus
}
#endif