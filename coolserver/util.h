#ifndef __COOLSERVER_UTIL_H__
#define __COOLSERVER_UTIL_H__

#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/syscall.h>
#include<stdio.h>
#include <stdint.h>
namespace coolserver{

pid_t GetThreadId();
uint32_t GetFiberId();
}
#endif