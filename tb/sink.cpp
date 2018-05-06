#include "sink.h"


void sink::recv() {

    // reset
    
    wait();

    while(1) {

        YUV_T tmp;
        int i = 0
        while (i < 300) {
            if ( rand() % 2 == 1)
            {
                tmp = ififo.read(tmp);
                i++;
            }

            wait();
        }

        __STOP_SIM__ = true;
        wait();
    }
}
