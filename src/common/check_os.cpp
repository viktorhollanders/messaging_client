#include "common/check_os.h"

bool check_os(){
    #ifdef ON_WINDOWS
        WSADATA wsa_data;
        if(WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0){
            cout << "failed at WSAStartup()" << endl;
            return false;
        }
    #endif
    return true;
}
