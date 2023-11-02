#include <LibRobus.h>

bool CheckWhistle(){
    if(analogRead(A0) >= 330)
    {
        return true;
    }
    else {
    return false;}
}
