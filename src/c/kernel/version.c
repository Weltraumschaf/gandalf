#include "version.h"

void gandalf_version(int *major, int *minor, int *revision) {
    *major = GANDALF_VERSION_MAJOR;
    *minor = GANDALF_VERSION_MINOR;
    *revision = GANDALF_VERSION_REVISION;
}