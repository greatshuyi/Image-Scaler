#include "hscaler.h"

void hscaler::bfifo() 
{

    {
        // reset
        yvalid = false;
        uvalid = false;
        vvalid = false;
        
        // TODO: need to reset P2P here instead
        wait();
    }

    // TODO: how to write sync reset


    // locals storage
    
    bool yfull = false;
    bool ufull = false;
    bool vfull = false;

    sc_uint<Y_FIFO_WIDTH> yregs[Y_FIFO_DEPTH];
    for(int i=0; i<Y_FIFO_DEPTH; i++) {
        yregs = 0;
    }

    sc_uint<U_FIFO_WIDTH> uregs[V_FIFO_DEPTH];
    for(int i=0; i<U_FIFO_DEPTH; i++) {
        uregs = 0;
    }

    sc_uint<V_FIFO_WIDTH> vregs[V_FIFO_DEPTH];
    for(int i=0; i<V_FIFO_DEPTH; i++) {
        vregs = 0;
    }

    sc_uint<Y_FIFO_PTR_WIDTH> ywptr = 0;
    sc_uint<Y_FIFO_PTR_WIDTH+1> yrptr = 0;

    sc_uint<U_FIFO_PTR_WIDTH> uwptr = 0;
    sc_uint<U_FIFO_PTR_WIDTH> urptr = 0;

    sc_uint<V_FIFO_PTR_WIDTH> vwptr = 0;
    sc_uint<V_FIFO_PTR_WIDTH> vrptr = 0;
    
    // infinite loop
    while(1) {

        // Y fifo, not empty means valid
        yfull = (ywptr(Y_FIFO_PTR_WIDTH-1) != yrptr(Y_FIFO_PTR_WIDTH-1) && 
                 ywptr.range(Y_FIFO_PTR_WIDTH-2:0) == yrptr.range(Y_FIFO_PTR_WIDTH-2, 1)) ? true : false;

        yvalid = (ywptr == yrptr.range(Y_FIFO_PTR_WIDTH-1:1) && yrptr(0) == 0) ? false : true;
        
        if (yrden && yvalid) {

            sc_uint<Y_FIFO_PTR_WIDTH-2> yaddr = yrptr.range(Y_FIFO_PTR_WIDTH-2:1);
            if (yrptr(0) == 0)
                yo.write(yregs[yaddr].range(Y_WIDTH*2-1, Y_WIDTH));
            else
                yo.write(yregs[yaddr].range(Y_WIDTH-1:0));
        }

        // U fifo, not empty means valid
        ufull = (uwptr(U_FIFO_PTR_WIDTH-1) != urptr(U_FIFO_PTR_WIDTH-1) && 
                 uwptr.range(U_FIFO_PTR_WIDTH-2:0) == urptr.range(U_FIFO_PTR_WIDTH-2, 1)) ? true : false;

        uvalid = (uwptr == urptr.range(U_FIFO_PTR_WIDTH-1:1) && urptr(0) == 0) ? false : true;
        
        if (urden && uvalid) {

            sc_uint<U_FIFO_PTR_WIDTH-2> uaddr = urptr.range(U_FIFO_PTR_WIDTH-2:1);
            uo.write(uregs[uaddr];
        }

        // V fifo, not empty means valid
        vfull = (vwptr(V_FIFO_PTR_WIDTH-1) != vrptr(V_FIFO_PTR_WIDTH-1) && 
                 vwptr.range(V_FIFO_PTR_WIDTH-2:0) == vrptr.range(V_FIFO_PTR_WIDTH-2, 1)) ? true : false;

        vvalid = (vwptr == vrptr.range(V_FIFO_PTR_WIDTH-1:1) && vrptr(0) == 0) ? false : true;
        
        if (vrden && vvalid) {

            sc_uint<V_FIFO_PTR_WIDTH-2> vaddr = vrptr.range(V_FIFO_PTR_WIDTH-2:1);
            vo.write(vregs[vaddr];
        }

        // write control
        sc_signal<bool> full = yfull & ufull & vfull;

        /***********change below code to actual*************yy**/
        // TODO: change below code
        if (!full && yuvi.num_available() > 0) {

            YUV_T yuvi_tmp;
            while (yuvi.nb_read(yuvi_tmp) {
                yregs[ywptr++] = (yuvi_tmp.yh, yuvi_tmp.yl);
                uregs[uwptr++] = yuvi_tmp.u;
                vregs[vwptr++] = yuvi_tmp.v;
                wait();
            }   
        }
        /***********change below code to actual*************yy**/

        wait();
    } // end of infinite loop

}


void hscaler::shift_hywin(uint t)
{

    uint t_tmp = 0;
    yrden = true;
    while (t_tmp < t) {
        if (yvalid) {
            for(int i=0; i<NHYTAPS-1; i++)
                hywin[NHYTAPS-1-i] = hywin[NHYTAPS-2-i];
            // eol
            if (
            hywin[0]=yo;
            t_tmp++;
        }
        // TODO: ask fanxu is wait is needed?
        //wait();
    }
    yrden = false;
}

void hscaler::shift_huwin(uint t)
{

    uint t_tmp = 0;
    urden = true;
    while (t_tmp < t) {
        if (uvalid) {
            for(int i=0; i<NHYTAPS-1; i++)
                huwin[NHYTAPS-1-i] = huwin[NHYTAPS-2-i];
            huwin[0]=uo;
            t_tmp++;
        }
        // TODO: ask fanxu is wait is needed?
        //wait();
    }
    urden = false;
}

void hscaler::shift_hvwin(uint t)
{

    uint t_tmp = 0;
    urden = true;
    while (t_tmp < t) {
        if (vvalid) {
            for(int i=0; i<NHYTAPS-1; i++)
                hvwin[NHYTAPS-1-i] = hvwin[NHYTAPS-2-i];
            hvwin[0]=vo;
            t_tmp++;
        }
        // TODO: ask fanxu is wait is needed?
        //wait();
    }
    urden = false;
}


// TODO: implement interpolations
sc_uint<Y_WIDTH>& hscaler::hyinterp() {
    sc_uint<Y_WIDTH> tmp = 0;
    for (int i=0; i<NHYTAPS; i++) {
        tmp += hywin[i]*i;
    }
    return tmp;
}

sc_uint<U_WIDTH>& hscaler::huinterp() {
    sc_uint<U_WIDTH> tmp = 0;
    for (int i=0; i<NHUTAPS; i++) {
        tmp += huwin[i]*i;
    }
    return tmp;
}

sc_uint<V_WIDTH>& hscaler::hvinterp() {
    sc_uint<V_WIDTH> tmp = 0;
    for (int i=0; i<NHVTAPS; i++) {
        tmp += hvwin[i]*i;
    }
    return tmp;
}

void hscaler::hscale()
{
    {
        // reset
        yldone.write(false);
        yhdone.write(false);
        udone.write(false);
        vdone.write(false);
        wait();
    }

    // wait to start
    while(!start.read()) {
        wait();
    }

    unsigned int hywin[NHYTAPS];
    for (int i = 0; i<NHYTAPS; i++)
        hywin = 0;

    unsigned int hyaccu = 0;

    while(1) {
        
        // Y component
        // row
        do {

            hyaccu = IHLEFT;
            unsigned int ypos;
            unsigned int yphase;
            unsigned int hywin_max;
            unsigned int hystep = 0;

            //populate window
            shift_hywin(6);
            hywin_max = 3;

            // ouput col
            do {
                
                if (sended) { 
                    // TODO: ask fanxu if flag clearance can be put here or add waits below?
                    // clear flag
                    yldone.write(false);
                    yhdone.write(false);

                    ypos = hyaccu >> 16;
                    yphase = hyaccu >> 13 & 0x7;
                    ypos_max = (ypos + NHYTAPS/2);

                    // compute interpolation
                    shift_hywin(ypoas_max);
                    sc_uint<Y_WIDTH> ytmp =  hyinterp();

                    if (ocol & 0x1 == 0) {
                        ylpo.write(ytmp);
                        yldone.write(true);
                        hyaccu += HINC;
                        ocol++;
                    } else {
                        yhpo.write(ytmp);
                        yhdone.write(true);
                        hyaccu += HINC;
                        ocol++
                    }
                }

                wait();

            } while (ocol < owidth) // end of col

        // TODO: change condition
        } while (icol < 16) // end of row
#ifdef SIM
        cout << sc_time_stamp() << ": ";
        cout << __FILE__ << ", ";
        cout << __LINE__ << ", ";
        cout << "end of H-Y interpolation, before wait();" << endl
#endif

        // do we need this?
        wait();
#ifdef SIM
        cout << sc_time_stamp() << ": ";
        cout << __FILE__ << ", ";
        cout << __LINE__ << ", ";
        cout << "end of H-Y interpolation, after wait();" << endl
#endif
    }

}


void hscaler::gather()
{
    {
        // reset
        sended.write(true);
        // TODO:need to reset P2P here instead
        wait();

    }

    // infinite loop
    while(1) {

        if (yldone && yhdone && udone && vdone) {
            // TODO: ask fanxu flag clearance can be put here or add wait()?
            // clear flag
            sended.write(false);
            
            // TODO: replace with P2P interface
            YUV_T tmp;
            tmp.yl = ylpo;
            tmp.yh = yhpo;
            tmp.u = upo;
            tmp.v = vpo;
            ofifo.write(tmp);
            
        } else {
            sended.write(true);
            wait();
        }
        // TODO: ask fanxu if we need below wait();
        // wait();
    } // end of infinite loop

}
