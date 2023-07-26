#include "util.h"
namespace coolserver{

pid_t GetThreadId(){
    return syscall(SYS_gettid);
}

}