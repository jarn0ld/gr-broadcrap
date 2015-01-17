/* -*- c++ -*- */

#define BROADCRAP_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "broadcrap_swig_doc.i"

%{
#include "broadcrap/ofdm_sync_cc.h"
%}


%include "broadcrap/ofdm_sync_cc.h"
GR_SWIG_BLOCK_MAGIC2(broadcrap, ofdm_sync_cc);
