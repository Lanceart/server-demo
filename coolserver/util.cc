#include "util.h"
namespace coolserver{

pid_t GetThreadId(){
    return syscall(SYS_gettid);
}
uint32_t getFiberId(){
    return 0; 
}
}