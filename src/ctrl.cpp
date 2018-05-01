#include "systemc.h"
#include "ctrl.h"

void ctrl::bfsm()
{

    // reset
    state = IDlE;
    line_timeout = 0;
    
    vscaler_en = false;
    hscaler_en = false;

    wait();

    // TODO: find a suitable place for local assignment
    // assign to local vars
    bool clear_tmp, start_tmp,
    

    while(1) {

        }
        // TODO: 

        switch(state) {
            case IDLE:
                if(clear_tmp) state = IDLE;
                else if(start_tmp) state = INIT;
                else state = IDLE;
                break;

            case INIT:
                if(clear_tmp) state = IDLE;
                else if(init_done) state = SCALING;
                else state = INIT;
                break;

            case SCALING:
                if(clear_tmp) state = IDLE;
                else if(hcnt == owidth && vcnt == oheight) {
                    if(start_tmp) state = INIT;
                    else if(line_timeout == LINE_TIMEOUT)
                        state = IDLE;
                }

            case ERROR:
                if(clear_tmp) {
                    if(start_tmp) state = INIT;
                    else state = 
                }
        }

        wait();
    }

}
