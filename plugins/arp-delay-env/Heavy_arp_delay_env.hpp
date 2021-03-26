/**
 * Copyright (c) 2021 Enzien Audio, Ltd.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions, and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the phrase "powered by heavy",
 *    the heavy logo, and a hyperlink to https://enzienaudio.com, all in a visible
 *    form.
 * 
 *   2.1 If the Application is distributed in a store system (for example,
 *       the Apple "App Store" or "Google Play"), the phrase "powered by heavy"
 *       shall be included in the app description or the copyright text as well as
 *       the in the app itself. The heavy logo will shall be visible in the app
 *       itself as well.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef _HEAVY_CONTEXT_ARP_DELAY_ENV_HPP_
#define _HEAVY_CONTEXT_ARP_DELAY_ENV_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalPhasor.h"
#include "HvSignalLine.h"
#include "HvControlDelay.h"
#include "HvTable.h"
#include "HvControlVar.h"
#include "HvControlSystem.h"
#include "HvMath.h"
#include "HvSignalTabwrite.h"
#include "HvSignalVar.h"
#include "HvControlBinop.h"
#include "HvControlSlice.h"
#include "HvSignalTabread.h"
#include "HvControlCast.h"

class Heavy_arp_delay_env : public HeavyContext {

 public:
  Heavy_arp_delay_env(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_arp_delay_env();

  const char *getName() override { return "arp_delay_env"; }
  int getNumInputChannels() override { return 0; }
  int getNumOutputChannels() override { return 2; }

  int process(float **inputBuffers, float **outputBuffer, int n) override;
  int processInline(float *inputBuffers, float *outputBuffer, int n) override;
  int processInlineInterleaved(float *inputBuffers, float *outputBuffer, int n) override;

  int getParameterInfo(int index, HvParameterInfo *info) override;
  struct Parameter {
    struct In {
      enum ParameterIn : hv_uint32_t {
        ARP_PITCH = 0x40ADE322, // Arp_Pitch
        ARP_SPEED = 0x234E72EF, // Arp_Speed
        DELAY_REPEATS = 0x53767352, // Delay_Repeats
        DELAY_TIME = 0xEE78D101, // Delay_Time
      };
    };
  };

 private:
  HvTable *getTableForHash(hv_uint32_t tableHash) override;
  void scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) override;

  // static sendMessage functions
  static void cVar_VDNZqovO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_JPaHZ9RM_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cCast_SZcq00qV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_xezCjcSZ_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_S45uNz9u_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_LTMsbU1K_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_gJ0SizUq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_l9azW0RB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_NO19wJP0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_XB2vJOHH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Mc4QLRlg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_5mo7bwWq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_SPJIwSMv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_868YltDP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_Q3vUHiRc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_6kd6utJC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_HwqkYOGI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wWYUUnSw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_BW8X5UdL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_czW9ZZCM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_93EyUsZe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_N1ylPTDI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_pNAh2Bt9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_4VOsakTK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_Q34wPe2B_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_NIcpxukU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_vrf1cVAq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_M9dvmJxK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_1qtebjam_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_67PoziTj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_0icxWHYj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_R4H5T71x_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wD2Mm4Cr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_wKcLvx5b_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_5lgy6asm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_ounosQSx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_3FLAQMET_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_GHlTgWwO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_QrkcKqOB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_4VG93WCb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_jtf1awR8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_IgtgMq2S_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_M5SeZSfF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_74GHqvdL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_GextMoqm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_mTQsYCrI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_8AfXfqXh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_xFPyYXqR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_kOGa5fB2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_qJn1Xnzn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_LLdrDTff_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_lCcskluN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_hTd0WbrT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_VebQNXZh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_rTLpCSEl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_1llHpySy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_VcWbFHxo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_LncwQjQD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_iAob3P2Z_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_BLpLRdA1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_QEY5zdlx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_uaSb9ygE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_kUskufA6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_dNUhrDDc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_fvcUpwZr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_oVY9fwjk_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalLine sLine_2eD61sRY;
  SignalTabhead sTabhead_H6U6VK6V;
  SignalTabread sTabread_NohsoJtX;
  SignalTabread sTabread_9Qx30wWo;
  SignalPhasor sPhasor_sm7g2hMo;
  SignalLine sLine_KGbNOmCD;
  SignalTabwrite sTabwrite_zTxws8nf;
  ControlVar cVar_VDNZqovO;
  ControlDelay cDelay_S45uNz9u;
  ControlVar cVar_NO19wJP0;
  ControlBinop cBinop_Mc4QLRlg;
  ControlBinop cBinop_5mo7bwWq;
  ControlBinop cBinop_SPJIwSMv;
  ControlDelay cDelay_6kd6utJC;
  ControlDelay cDelay_HwqkYOGI;
  ControlBinop cBinop_wWYUUnSw;
  HvTable hTable_BW8X5UdL;
  ControlBinop cBinop_93EyUsZe;
  ControlVar cVar_Q34wPe2B;
  ControlVar cVar_NIcpxukU;
  ControlVar cVar_vrf1cVAq;
  ControlVar cVar_M9dvmJxK;
  ControlVar cVar_0icxWHYj;
  ControlBinop cBinop_wD2Mm4Cr;
  ControlBinop cBinop_5lgy6asm;
  SignalVarf sVarf_Aq1HHgyT;
  SignalVarf sVarf_yOxiDGOd;
  SignalVarf sVarf_xmEmYqmK;
  ControlVar cVar_ounosQSx;
  ControlSlice cSlice_3FLAQMET;
  ControlSlice cSlice_GHlTgWwO;
  ControlSlice cSlice_QrkcKqOB;
  ControlBinop cBinop_4VG93WCb;
  ControlBinop cBinop_jtf1awR8;
  ControlBinop cBinop_IgtgMq2S;
  ControlBinop cBinop_M5SeZSfF;
  ControlBinop cBinop_GextMoqm;
  SignalVarf sVarf_ZIO0QCf4;
  ControlBinop cBinop_qJn1Xnzn;
  ControlBinop cBinop_hTd0WbrT;
  ControlBinop cBinop_VebQNXZh;
  ControlBinop cBinop_rTLpCSEl;
  ControlBinop cBinop_1llHpySy;
};

#endif // _HEAVY_CONTEXT_ARP_DELAY_ENV_HPP_
