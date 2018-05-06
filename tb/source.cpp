#include "source.h"


void source::emit() {


    // reset
    yuv yuv422(16, 16, YUV422);
    yuv yuv420(16, 16, YUV420);
    yuv yuv444(16, 16, YUV444);
    wait();

    while(1) {

        int i=0;
        yuv422.initialize();
        cout << "Source: begin YUV422 transfer"
        while (i < yuv422.groups()) {
            YUV_T tmp = yuv422.get(i);

            // replace with P2P
            if ( rand() % 2 == 0) {
                if (ofifo.nb_put(tmp)) i++;

            wait();
        }

        cout << "Source: end of transfer YUV422"

        i = 0;
        yuv420.initialize();
        cout << "Source: begin YUV420 transfer"
        while (i < yuv420.groups()) {
            YUV_T tmp = yuv422.get(i);

            // replace with P2P
            if ( rand() % 2 == 0) {
                if (ofifo.nb_put(tmp)) i++;

            wait();
        }

        cout << "Source: end of transfer YUV420"


        wait();
    }

}
