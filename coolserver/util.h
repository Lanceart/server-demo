#ifndef __COOLSERVER_UTIL_H__
#define __COOLSERVER_UTIL_H__

#include<pthread.h>
#include<sys/types.h>
#include<sys/syscall.h>

namespace coolserver{

pid_t GetThreadId();


}
#endif