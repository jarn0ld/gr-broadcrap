/* -*- c++ -*- */
/*
 * Copyright 2015 <+YOU OR YOUR COMPANY+>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ofdm_sync_cc_impl.h"

namespace gr {
  namespace broadcrap {

    ofdm_sync_cc::sptr
    ofdm_sync_cc::make()
    {
      return gnuradio::get_initial_sptr
        (new ofdm_sync_cc_impl());
    }

    /*
     * The private constructor
     */
    ofdm_sync_cc_impl::ofdm_sync_cc_impl()
      : gr::sync_block("ofdm_sync_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))), _fill_buffer(true), _buffer_write_ptr(_buffer)
    {
        set_history(32);
    }

    /*
     * Our virtual destructor.
     */
    ofdm_sync_cc_impl::~ofdm_sync_cc_impl()
    {
    }

    int
    ofdm_sync_cc_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];

        for(int j = 0; j < noutput_items - 32; j++) {

            for(int i = j; i < (j + 16); i++) {
                gr_complex curr_corr(0,0);

                if(_fill_buffer) {
                    _buffer[_buffer_write_ptr] = std::conj(in[i])*in[i + 16];
                    if(_buffer_write_ptr == _buffer+14) {
                        fill_buffer = false;
                    }
                }

                gr_complex tmp;
                if((i - j) == 15)
                {
                    tmp = std::conj(in[i])*in[i + 16];
                    _buffer[_buffer_write_ptr] = tmp;
                }

                tmp = _buffer[_buffer_write_ptr];
                curr_corr += tmp;

                if(_buffer_write_ptr == _buffer+15)
                {
                    _buffer_write_ptr = _buffer;
                } else {
                    _buffer_write_ptr++;
                }
            }
            out[j] = curr_corr;
        }
        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace broadcrap */
} /* namespace gr */

