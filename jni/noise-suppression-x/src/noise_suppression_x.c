/*
 *  Copyright (c) 2012 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "noise_suppression_x.h"

#include <stdlib.h>

#include "real_fft.h"
#include "nsx_core.h"
#include "nsx_defines.h"

NsxInst_t* WebRtcNsx_Create() {
  NsxInst_t* nsxInst = malloc(sizeof(NsxInst_t));

  WebRtcSpl_Init();
  nsxInst->real_fft = NULL;
  nsxInst->initFlag = 0;

  return nsxInst;
}

void WebRtcNsx_Free(NsxInst_t* nsxInst) {
  WebRtcSpl_FreeRealFFT(nsxInst->real_fft);
  free(nsxInst);
}

int WebRtcNsx_Init(NsxInst_t* nsxInst, uint32_t fs) {
  return WebRtcNsx_InitCore(nsxInst, fs);
}

int WebRtcNsx_set_policy(NsxInst_t* nsxInst, int mode) {
  return WebRtcNsx_set_policy_core(nsxInst, mode);
}

int WebRtcNsx_Process(NsxInst_t* nsxInst, short* speechFrame,
                      short* speechFrameHB, short* outFrame,
                      short* outFrameHB) {
  return WebRtcNsx_ProcessCore(nsxInst, speechFrame, speechFrameHB, outFrame, outFrameHB);
}

const uint32_t* WebRtcNsx_noise_estimate(const NsxInst_t* nsxInst) {
  return nsxInst->prevNoiseU32;
}

size_t WebRtcNsx_num_freq() {
  return HALF_ANAL_BLOCKL;
}
