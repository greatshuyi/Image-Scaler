
#include <cstdlib>
#include <cstdio>

#include "systemc.h"


// design
#include "scaler_def.h"
#include "scaler_intr.h"

// verification
#include "sim_def.h"
#include "source.h"
#include "monior.h"


using namespace std;


int sc_main(int argc, char **argv)
{

    sc_signal<bool> clk;
    sc_signal<bool> rst_n;
    sc_signal<bool> clear;
    sc_signal<bool> start;

    // components & communications
    source src("source");
    sink snk("sink");

    // TODO: replace with P2P
    sc_fifo<YUV_T> ififo;
    sc_fifo<YUV_T> ofifo;

    // bind
    src.clk(clk);
    src.rst_n(rst_n);
    src.clear(rst_n);
    src.yuvo(ififo);

    snk.clk(clk);
    snk.rst_n(rst_n);
    snk.clear(rst_n);
    snk.yuvi(ofifo);

#ifdef DUMP_SIM
    sc_trace_file *vcd_file;
    vcd_file = sc_create_vcd_trace_file("hscaler.vcd");
#endif

    // generate general purpose sigs
    {
        clk = false
        rst_n = false;
        clear = false;

        sc_initialize();

        // advance cycles
        for (int i =0; i<10; i++) {
            clk = false;
            sc_cycle(5);
            clk = true;
            sc_cycle(5);
        }

        rst_n.write(true);

        // run until stop triggered
        for(;;) {
            clk = false;
            sc_cycle(5);
            clk = true;
            sc_cycle(5);

            if (__STOP_SIM__) break;
        }
        

        sc_stop();
#ifdef DUMP_SIM
        sc_close_vcd_trace_file(vcd_file);
#endif

    }
    

    return 0;


}
