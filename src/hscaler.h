#ifndef __HSCALER_H_
#define __HSCALER_H_

#include "systemc.h"

// replace with corret working set
#include "scaler_def.h"
#include "scaler_intr.h"

using namespace std;

#ifdef SIM
using namespace sc_core;
#endif

SC_MODULE(hscaler)
{

    sc_in<bool> clk;
    sc_in<bool> rst_n;
    sc_in<bool> clear;
    sc_in<bool> start;
    
#ifdef SIM
    // TODO: replace fifo interface with P2P
    sc_port<sc_fifo_in_if<YUV_T> > yuvi;
    sc_port<sc_fifo_out_if<YUV_T> > yuvo;
#endif

    // internal sigs

    // output from fifo
    sc_signal<bool> yvalid;
    sc_signal<bool> uvalid;
    sc_signal<bool> vvalid;
    sc_signal<sc_uint<Y_WIDTH> > yo;
    sc_signal<sc_uint<U_WIDTH> > uo;
    sc_signal<sc_uint<V_WIDTH> > vo;

    // shift regs used by interpolator
    sc_signal<sc_uint<Y_WIDTH> > hywin[NHYTAPS];
    sc_signal<sc_uint<U_WIDTH> > huwin[NHUTAPS];
    sc_signal<sc_uint<U_WIDTH> > huwin[NHUTAPS];

    // output from interpolator
    sc_signal<sc_uint<Y_WIDTH> > yhpo;
    sc_signal<sc_uint<Y_WIDTH> > ylpo;
    sc_signal<sc_uint<U_WIDTH> > upo;
    sc_signal<sc_uint<V_WIDTH> > uvo;
    sc_signal<bool> yldone;
    sc_signal<bool> yhdone;
    sc_signal<bool> udone;
    sc_signal<bool> vdone;

    // output from gather
    sc_signal<bool> sended;
    
    SC_CTOR(hscaler) {
        SC_CTHREAD(bhscaler, clk.pos());
        async_reset_singal_is(rst_n, false);
        reset_signal_is(clear, true);
        
        SC_CTHREAD(bfifo, clk.pos());
        async_reset_singal_is(rst_n, false);
        reset_signal_is(clear, true);
    }


    void bfifo();
    void shift_hywin(uint t);
    void shift_huwin(uint t);
    void shift_hvwin(uint t);

    void hyinterp();
    void huinterp();
    void hvinterp();
    
    void hscale();
    void gather();

};

#endif
