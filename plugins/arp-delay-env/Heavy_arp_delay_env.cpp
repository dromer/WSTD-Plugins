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

#include "Heavy_arp_delay_env.hpp"

#define Context(_c) reinterpret_cast<Heavy_arp_delay_env *>(_c)



/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_arp_delay_env_new(double sampleRate) {
    return new Heavy_arp_delay_env(sampleRate);
  }

  HV_EXPORT HeavyContextInterface *hv_arp_delay_env_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    return new Heavy_arp_delay_env(sampleRate, poolKb, inQueueKb, outQueueKb);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_arp_delay_env::Heavy_arp_delay_env(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sLine_init(&sLine_2eD61sRY);
  numBytes += sTabhead_init(&sTabhead_H6U6VK6V, &hTable_BW8X5UdL);
  numBytes += sTabread_init(&sTabread_NohsoJtX, &hTable_BW8X5UdL, false);
  numBytes += sTabread_init(&sTabread_9Qx30wWo, &hTable_BW8X5UdL, false);
  numBytes += sPhasor_k_init(&sPhasor_sm7g2hMo, 220.0f, sampleRate);
  numBytes += sLine_init(&sLine_KGbNOmCD);
  numBytes += sTabwrite_init(&sTabwrite_zTxws8nf, &hTable_BW8X5UdL);
  numBytes += cVar_init_f(&cVar_VDNZqovO, 0.0f);
  numBytes += cDelay_init(this, &cDelay_S45uNz9u, 0.0f);
  numBytes += cVar_init_f(&cVar_NO19wJP0, 300.0f);
  numBytes += cBinop_init(&cBinop_SPJIwSMv, 0.0f); // __mul
  numBytes += cDelay_init(this, &cDelay_6kd6utJC, 0.0f);
  numBytes += cDelay_init(this, &cDelay_HwqkYOGI, 0.0f);
  numBytes += hTable_init(&hTable_BW8X5UdL, 256);
  numBytes += cVar_init_f(&cVar_Q34wPe2B, 0.0f);
  numBytes += cVar_init_f(&cVar_NIcpxukU, 0.0f);
  numBytes += cVar_init_f(&cVar_vrf1cVAq, 0.0f);
  numBytes += cVar_init_f(&cVar_M9dvmJxK, 0.0f);
  numBytes += cVar_init_s(&cVar_0icxWHYj, "del-del");
  numBytes += sVarf_init(&sVarf_Aq1HHgyT, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_yOxiDGOd, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_xmEmYqmK, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_ounosQSx, 1.0f);
  numBytes += cSlice_init(&cSlice_3FLAQMET, 2, 1);
  numBytes += cSlice_init(&cSlice_GHlTgWwO, 1, 1);
  numBytes += cSlice_init(&cSlice_QrkcKqOB, 0, 1);
  numBytes += cBinop_init(&cBinop_M5SeZSfF, 1.0f); // __pow
  numBytes += cBinop_init(&cBinop_GextMoqm, 0.0f); // __add
  numBytes += sVarf_init(&sVarf_ZIO0QCf4, 0.3f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_arp_delay_env::~Heavy_arp_delay_env() {
  hTable_free(&hTable_BW8X5UdL);
}

HvTable *Heavy_arp_delay_env::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x7BAC8768: return &hTable_BW8X5UdL; // del-del
    default: return nullptr;
  }
}

void Heavy_arp_delay_env::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0x40ADE322: { // Arp_Pitch
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_dNUhrDDc_sendMessage);
      break;
    }
    case 0x234E72EF: { // Arp_Speed
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_fvcUpwZr_sendMessage);
      break;
    }
    case 0x53767352: { // Delay_Repeats
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_kUskufA6_sendMessage);
      break;
    }
    case 0xEE78D101: { // Delay_Time
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_oVY9fwjk_sendMessage);
      break;
    }
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_QEY5zdlx_sendMessage);
      break;
    }
    case 0x67E37CA3: { // __hv_notein
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_uaSb9ygE_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_arp_delay_env::getParameterInfo(int index, HvParameterInfo *info) {
  if (info != nullptr) {
    switch (index) {
      case 0: {
        info->name = "Arp_Pitch";
        info->hash = 0x40ADE322;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 1.0f;
        info->defaultVal = 0.5f;
        break;
      }
      case 1: {
        info->name = "Arp_Speed";
        info->hash = 0x234E72EF;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 1.0f;
        info->defaultVal = 0.5f;
        break;
      }
      case 2: {
        info->name = "Delay_Repeats";
        info->hash = 0x53767352;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 1.0f;
        info->defaultVal = 0.5f;
        break;
      }
      case 3: {
        info->name = "Delay_Time";
        info->hash = 0xEE78D101;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 1.0f;
        info->defaultVal = 0.5f;
        break;
      }
      default: {
        info->name = "invalid parameter index";
        info->hash = 0;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 0.0f;
        info->defaultVal = 0.0f;
        break;
      }
    }
  }
  return 4;
}



/*
 * Send Function Implementations
 */


void Heavy_arp_delay_env::cVar_VDNZqovO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_GextMoqm, HV_BINOP_ADD, 1, m, &cBinop_GextMoqm_sendMessage);
}

void Heavy_arp_delay_env::cSwitchcase_JPaHZ9RM_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  switch (msg_getHash(m, 0)) {
    case 0x3F800000: { // "1.0"
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_SZcq00qV_sendMessage);
      break;
    }
    default: {
      break;
    }
  }
}

void Heavy_arp_delay_env::cCast_SZcq00qV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_8AfXfqXh_sendMessage(_c, 0, m);
}

void Heavy_arp_delay_env::cSwitchcase_xezCjcSZ_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  switch (msg_getHash(m, 0)) {
    case 0x0: { // "0.0"
      cMsg_XB2vJOHH_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_XB2vJOHH_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_LTMsbU1K_sendMessage);
      break;
    }
  }
}

void Heavy_arp_delay_env::cDelay_S45uNz9u_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_S45uNz9u, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_S45uNz9u, 0, m, &cDelay_S45uNz9u_sendMessage);
  cMsg_mTQsYCrI_sendMessage(_c, 0, m);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_iAob3P2Z_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_BLpLRdA1_sendMessage);
}

void Heavy_arp_delay_env::cCast_LTMsbU1K_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_XB2vJOHH_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_S45uNz9u, 0, m, &cDelay_S45uNz9u_sendMessage);
  cMsg_mTQsYCrI_sendMessage(_c, 0, m);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_iAob3P2Z_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_BLpLRdA1_sendMessage);
}

void Heavy_arp_delay_env::cMsg_gJ0SizUq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_l9azW0RB_sendMessage);
}

void Heavy_arp_delay_env::cSystem_l9azW0RB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_5mo7bwWq_sendMessage);
}

void Heavy_arp_delay_env::cVar_NO19wJP0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_SPJIwSMv, HV_BINOP_MULTIPLY, 0, m, &cBinop_SPJIwSMv_sendMessage);
}

void Heavy_arp_delay_env::cMsg_XB2vJOHH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_S45uNz9u, 0, m, &cDelay_S45uNz9u_sendMessage);
}

void Heavy_arp_delay_env::cBinop_Mc4QLRlg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_S45uNz9u, 2, m, &cDelay_S45uNz9u_sendMessage);
}

void Heavy_arp_delay_env::cBinop_5mo7bwWq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_SPJIwSMv, HV_BINOP_MULTIPLY, 1, m, &cBinop_SPJIwSMv_sendMessage);
}

void Heavy_arp_delay_env::cBinop_SPJIwSMv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_Mc4QLRlg_sendMessage);
}

void Heavy_arp_delay_env::cMsg_868YltDP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_Q3vUHiRc_sendMessage);
}

void Heavy_arp_delay_env::cSystem_Q3vUHiRc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_93EyUsZe_sendMessage);
}

void Heavy_arp_delay_env::cDelay_6kd6utJC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_6kd6utJC, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_HwqkYOGI, 0, m, &cDelay_HwqkYOGI_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_6kd6utJC, 0, m, &cDelay_6kd6utJC_sendMessage);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_zTxws8nf, 1, m, NULL);
}

void Heavy_arp_delay_env::cDelay_HwqkYOGI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_HwqkYOGI, m);
  cMsg_N1ylPTDI_sendMessage(_c, 0, m);
}

void Heavy_arp_delay_env::cBinop_wWYUUnSw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_czW9ZZCM_sendMessage(_c, 0, m);
}

void Heavy_arp_delay_env::hTable_BW8X5UdL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_4VOsakTK_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_6kd6utJC, 2, m, &cDelay_6kd6utJC_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_pNAh2Bt9_sendMessage);
}

void Heavy_arp_delay_env::cMsg_czW9ZZCM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "resize");
  msg_setElementToFrom(m, 1, n, 0);
  hTable_onMessage(_c, &Context(_c)->hTable_BW8X5UdL, 0, m, &hTable_BW8X5UdL_sendMessage);
}

void Heavy_arp_delay_env::cBinop_93EyUsZe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 1000.0f, 0, m, &cBinop_wWYUUnSw_sendMessage);
}

void Heavy_arp_delay_env::cMsg_N1ylPTDI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "mirror");
  hTable_onMessage(_c, &Context(_c)->hTable_BW8X5UdL, 0, m, &hTable_BW8X5UdL_sendMessage);
}

void Heavy_arp_delay_env::cCast_pNAh2Bt9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_6kd6utJC, 0, m, &cDelay_6kd6utJC_sendMessage);
}

void Heavy_arp_delay_env::cMsg_4VOsakTK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0,  static_cast<float>(HV_N_SIMD));
  cDelay_onMessage(_c, &Context(_c)->cDelay_HwqkYOGI, 2, m, &cDelay_HwqkYOGI_sendMessage);
}

void Heavy_arp_delay_env::cVar_Q34wPe2B_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 1000.0f, 0, m, &cBinop_1llHpySy_sendMessage);
}

void Heavy_arp_delay_env::cVar_NIcpxukU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 440.0f, 0, m, &cBinop_qJn1Xnzn_sendMessage);
}

void Heavy_arp_delay_env::cVar_vrf1cVAq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 600.0f, 0, m, &cBinop_hTd0WbrT_sendMessage);
}

void Heavy_arp_delay_env::cVar_M9dvmJxK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_ZIO0QCf4, m);
}

void Heavy_arp_delay_env::cMsg_1qtebjam_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_67PoziTj_sendMessage);
}

void Heavy_arp_delay_env::cSystem_67PoziTj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_wD2Mm4Cr_sendMessage);
}

void Heavy_arp_delay_env::cVar_0icxWHYj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_wKcLvx5b_sendMessage(_c, 0, m);
}

void Heavy_arp_delay_env::cSystem_R4H5T71x_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_5lgy6asm_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_Aq1HHgyT, m);
}

void Heavy_arp_delay_env::cBinop_wD2Mm4Cr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_yOxiDGOd, m);
}

void Heavy_arp_delay_env::cMsg_wKcLvx5b_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_R4H5T71x_sendMessage);
}

void Heavy_arp_delay_env::cBinop_5lgy6asm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_xmEmYqmK, m);
}

void Heavy_arp_delay_env::cVar_ounosQSx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sLine_onMessage(_c, &Context(_c)->sLine_KGbNOmCD, 0, m, NULL);
}

void Heavy_arp_delay_env::cSlice_3FLAQMET_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_arp_delay_env::cSlice_GHlTgWwO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_arp_delay_env::cSlice_QrkcKqOB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 69.0f, 0, m, &cBinop_jtf1awR8_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_arp_delay_env::cBinop_4VG93WCb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_sm7g2hMo, 0, m);
}

void Heavy_arp_delay_env::cBinop_jtf1awR8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 12.0f, 0, m, &cBinop_IgtgMq2S_sendMessage);
}

void Heavy_arp_delay_env::cBinop_IgtgMq2S_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_M5SeZSfF, HV_BINOP_POW, 1, m, &cBinop_M5SeZSfF_sendMessage);
  cMsg_74GHqvdL_sendMessage(_c, 0, m);
}

void Heavy_arp_delay_env::cBinop_M5SeZSfF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 440.0f, 0, m, &cBinop_4VG93WCb_sendMessage);
}

void Heavy_arp_delay_env::cMsg_74GHqvdL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 2.0f);
  cBinop_onMessage(_c, &Context(_c)->cBinop_M5SeZSfF, HV_BINOP_POW, 0, m, &cBinop_M5SeZSfF_sendMessage);
}

void Heavy_arp_delay_env::cBinop_GextMoqm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_VDNZqovO, 0, m, &cVar_VDNZqovO_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN, 4.0f, 0, m, &cBinop_rTLpCSEl_sendMessage);
}

void Heavy_arp_delay_env::cMsg_mTQsYCrI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  cBinop_onMessage(_c, &Context(_c)->cBinop_GextMoqm, HV_BINOP_ADD, 0, m, &cBinop_GextMoqm_sendMessage);
}

void Heavy_arp_delay_env::cMsg_8AfXfqXh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cVar_onMessage(_c, &Context(_c)->cVar_VDNZqovO, 0, m, &cVar_VDNZqovO_sendMessage);
}

void Heavy_arp_delay_env::cMsg_xFPyYXqR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  cSwitchcase_xezCjcSZ_onMessage(_c, NULL, 0, m, NULL);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 1000.0f, 0, m, &cBinop_1llHpySy_sendMessage);
}

void Heavy_arp_delay_env::cMsg_kOGa5fB2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.3f);
  sVarf_onMessage(_c, &Context(_c)->sVarf_ZIO0QCf4, m);
}

void Heavy_arp_delay_env::cBinop_qJn1Xnzn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_arp_delay_env::cMsg_LLdrDTff_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 440.0f);
}

void Heavy_arp_delay_env::cMsg_lCcskluN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 220.0f);
  cMsg_VcWbFHxo_sendMessage(_c, 0, m);
}

void Heavy_arp_delay_env::cBinop_hTd0WbrT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 20.0f, 0, m, &cBinop_VebQNXZh_sendMessage);
}

void Heavy_arp_delay_env::cBinop_VebQNXZh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_VcWbFHxo_sendMessage(_c, 0, m);
}

void Heavy_arp_delay_env::cBinop_rTLpCSEl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_JPaHZ9RM_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_arp_delay_env::cBinop_1llHpySy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_NO19wJP0, 0, m, &cVar_NO19wJP0_sendMessage);
}

void Heavy_arp_delay_env::cMsg_VcWbFHxo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setElementToFrom(m, 0, n, 0);
  msg_setFloat(m, 1, 20.0f);
  sLine_onMessage(_c, &Context(_c)->sLine_2eD61sRY, 0, m, NULL);
}

void Heavy_arp_delay_env::cMsg_LncwQjQD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  msg_setFloat(m, 1, 300.0f);
  sLine_onMessage(_c, &Context(_c)->sLine_KGbNOmCD, 0, m, NULL);
}

void Heavy_arp_delay_env::cCast_iAob3P2Z_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_ounosQSx, 0, m, &cVar_ounosQSx_sendMessage);
}

void Heavy_arp_delay_env::cCast_BLpLRdA1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_LncwQjQD_sendMessage(_c, 0, m);
}

void Heavy_arp_delay_env::cReceive_QEY5zdlx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_gJ0SizUq_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_NO19wJP0, 0, m, &cVar_NO19wJP0_sendMessage);
  cMsg_868YltDP_sendMessage(_c, 0, m);
  cMsg_xFPyYXqR_sendMessage(_c, 0, m);
  cMsg_kOGa5fB2_sendMessage(_c, 0, m);
  cMsg_LLdrDTff_sendMessage(_c, 0, m);
  cMsg_lCcskluN_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_0icxWHYj, 0, m, &cVar_0icxWHYj_sendMessage);
  cMsg_1qtebjam_sendMessage(_c, 0, m);
}

void Heavy_arp_delay_env::cReceive_uaSb9ygE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSlice_onMessage(_c, &Context(_c)->cSlice_3FLAQMET, 0, m, &cSlice_3FLAQMET_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_GHlTgWwO, 0, m, &cSlice_GHlTgWwO_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_QrkcKqOB, 0, m, &cSlice_QrkcKqOB_sendMessage);
}

void Heavy_arp_delay_env::cReceive_kUskufA6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_ZIO0QCf4, m);
}

void Heavy_arp_delay_env::cReceive_dNUhrDDc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 440.0f, 0, m, &cBinop_qJn1Xnzn_sendMessage);
}

void Heavy_arp_delay_env::cReceive_fvcUpwZr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 1000.0f, 0, m, &cBinop_1llHpySy_sendMessage);
}

void Heavy_arp_delay_env::cReceive_oVY9fwjk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 600.0f, 0, m, &cBinop_hTd0WbrT_sendMessage);
}




/*
 * Context Process Implementation
 */

int Heavy_arp_delay_env::process(float **inputBuffers, float **outputBuffers, int n) {
  while (hLp_hasData(&inQueue)) {
    hv_uint32_t numBytes = 0;
    ReceiverMessagePair *p = reinterpret_cast<ReceiverMessagePair *>(hLp_getReadBuffer(&inQueue, &numBytes));
    hv_assert(numBytes >= sizeof(ReceiverMessagePair));
    scheduleMessageForReceiver(p->receiverHash, &p->msg);
    hLp_consume(&inQueue);
  }
  const int n4 = n & ~HV_N_SIMD_MASK; // ensure that the block size is a multiple of HV_N_SIMD

  // temporary signal vars
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3, Bf4, Bf5, Bf6;
  hv_bufferi_t Bi0, Bi1;

  // input and output vars
  hv_bufferf_t O0, O1;

  // declare and init the zero buffer
  hv_bufferf_t ZERO; __hv_zero_f(VOf(ZERO));

  hv_uint32_t nextBlock = blockStartTimestamp;
  for (int n = 0; n < n4; n += HV_N_SIMD) {

    // process all of the messages for this block
    nextBlock += HV_N_SIMD;
    while (mq_hasMessageBefore(&mq, nextBlock)) {
      MessageNode *const node = mq_peek(&mq);
      node->sendMessage(this, node->let, node->m);
      mq_pop(&mq);
    }

    

    // zero output buffers
    __hv_zero_f(VOf(O0));
    __hv_zero_f(VOf(O1));

    // process all signal functions
    __hv_line_f(&sLine_2eD61sRY, VOf(Bf0));
    __hv_tabhead_f(&sTabhead_H6U6VK6V, VOf(Bf1));
    __hv_var_k_f_r(VOf(Bf2), -1.0f, -2.0f, -3.0f, -4.0f, -5.0f, -6.0f, -7.0f, -8.0f);
    __hv_add_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_varread_f(&sVarf_yOxiDGOd, VOf(Bf1));
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_xmEmYqmK, VOf(Bf0));
    __hv_min_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_zero_f(VOf(Bf1));
    __hv_max_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_sub_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_floor_f(VIf(Bf1), VOf(Bf2));
    __hv_varread_f(&sVarf_Aq1HHgyT, VOf(Bf0));
    __hv_zero_f(VOf(Bf3));
    __hv_lt_f(VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_and_f(VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_add_f(VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_cast_fi(VIf(Bf3), VOi(Bi0));
    __hv_var_k_i(VOi(Bi1), 1, 1, 1, 1, 1, 1, 1, 1);
    __hv_add_i(VIi(Bi0), VIi(Bi1), VOi(Bi1));
    __hv_tabread_if(&sTabread_NohsoJtX, VIi(Bi1), VOf(Bf3));
    __hv_tabread_if(&sTabread_9Qx30wWo, VIi(Bi0), VOf(Bf0));
    __hv_sub_f(VIf(Bf3), VIf(Bf0), VOf(Bf3));
    __hv_sub_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_fma_f(VIf(Bf3), VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_ZIO0QCf4, VOf(Bf2));
    __hv_phasor_k_f(&sPhasor_sm7g2hMo, VOf(Bf3));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_abs_f(VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf3), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf1), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf3));
    __hv_mul_f(VIf(Bf1), VIf(Bf3), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf5), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf6), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf4), VIf(Bf6), VIf(Bf1), VOf(Bf1));
    __hv_fma_f(VIf(Bf3), VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_line_f(&sLine_KGbNOmCD, VOf(Bf5));
    __hv_mul_f(VIf(Bf1), VIf(Bf5), VOf(Bf5));
    __hv_fma_f(VIf(Bf0), VIf(Bf2), VIf(Bf5), VOf(Bf2));
    __hv_tabwrite_f(&sTabwrite_zTxws8nf, VIf(Bf2));
    __hv_add_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf5), 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f);
    __hv_mul_f(VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_add_f(VIf(Bf5), VIf(O1), VOf(O1));
    __hv_add_f(VIf(Bf5), VIf(O0), VOf(O0));

    // save output vars to output buffer
    __hv_store_f(outputBuffers[0]+n, VIf(O0));
    __hv_store_f(outputBuffers[1]+n, VIf(O1));
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed
}

int Heavy_arp_delay_env::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 2 channel(s)
  float **const bOut = reinterpret_cast<float **>(hv_alloca(2*sizeof(float *)));
  bOut[0] = outputBuffers+(0*n4);
  bOut[1] = outputBuffers+(1*n4);

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_arp_delay_env::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 2 channel(s)
  float *const bOut = reinterpret_cast<float *>(hv_alloca(2*n4*sizeof(float)));

  int n = processInline(bIn, bOut, n4);

  // interleave the heavy output into the output buffer
  #if HV_SIMD_AVX
  for (int i = 0, j = 0; j < n4; j += 8, i += 16) {
    __m256 x = _mm256_load_ps(bOut+j);    // LLLLLLLL
    __m256 y = _mm256_load_ps(bOut+n4+j); // RRRRRRRR
    __m256 a = _mm256_unpacklo_ps(x, y);  // LRLRLRLR
    __m256 b = _mm256_unpackhi_ps(x, y);  // LRLRLRLR
    _mm256_store_ps(outputBuffers+i, a);
    _mm256_store_ps(outputBuffers+8+i, b);
  }
  #elif HV_SIMD_SSE
  for (int i = 0, j = 0; j < n4; j += 4, i += 8) {
    __m128 x = _mm_load_ps(bOut+j);    // LLLL
    __m128 y = _mm_load_ps(bOut+n4+j); // RRRR
    __m128 a = _mm_unpacklo_ps(x, y);  // LRLR
    __m128 b = _mm_unpackhi_ps(x, y);  // LRLR
    _mm_store_ps(outputBuffers+i, a);
    _mm_store_ps(outputBuffers+4+i, b);
  }
  #elif HV_SIMD_NEON
  // https://community.arm.com/groups/processors/blog/2012/03/13/coding-for-neon--part-5-rearranging-vectors
  for (int i = 0, j = 0; j < n4; j += 4, i += 8) {
    float32x4_t x = vld1q_f32(bOut+j);
    float32x4_t y = vld1q_f32(bOut+n4+j);
    float32x4x2_t z = {x, y};
    vst2q_f32(outputBuffers+i, z); // interleave and store
  }
  #else // HV_SIMD_NONE
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < n4; ++j) {
      outputBuffers[i+2*j] = bOut[i*n4+j];
    }
  }
  #endif

  return n;
}
