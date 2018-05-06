#ifndef __SOURCE_H__
#define __SOURCE_H__

#include <cstdlib>
#include <cstdio>

#include "systemc.h"

// design
#include "scaler_def.h"
#include "scaler_intr.h"

// verification
#include "sim_def.h"
#include "yuv.h"

using namespace std;

SC_MODULE(source)
{

    sc_in<bool> clk;
    sc_in<bool> rst_n;

    // replace with P2P
    sc_port<sc_fifo_out_if<YUV_T> > ofifo;

    SC_CTOR(source) {
        SC_CTREAD(emit, clk.pos());
        async_reset_signal_is(rst_n, false);
    }

    void emit();

};

#endif
