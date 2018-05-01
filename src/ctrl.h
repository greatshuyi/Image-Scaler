#ifndef __CTRL_H__
#define __CTRL_H__

#include "systemc.h"

using namespace std;


SC_MODULE(ctrl)
{

    // TODO: improvise it
    enum STATE_T = {IDEL=0, INIT, SCALING, ERROR}; 
    enum ERROR_T = {NONE=0, HERR, VERR}

    // input
    sc_in<bool> clk;
    sc_in<bool> rst_n;
    sc_in<bool> clear;

    // control and parameters
    sc_in<bool> start;
    sc_in<sc_uint<16> > iwidth, iheight, owidth, oheight;
    sc_in<sc_uint<20> > lthreshold;

    // output 
    sc_out<ERROR_T> frame_err;
    sc_out<bool> frame_done;

    sc_out<sc_signal<STATE_T> > stateo;
    
    // states
    sc_signal<STATE_T> state;
    sc_signal<sc_uint<21> > line_cnt;

    SC_CTOR(ctrl):
        clk("clk"),
        rst_n("rst_n"),
        clear("clear"),
        start("start"),
        stateo("stateo")

    {

        SC_CTHREAD(bfsm, clk.pos());
        async_reset_signal_is(rst_n, false);
        
    }

    void bfsm();


};

#endif
