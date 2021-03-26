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

#include "HeavyDPF_arp_delay_env.hpp"


#define HV_LV2_NUM_PARAMETERS 4

START_NAMESPACE_DISTRHO

static float scaleParameterForIndex(uint32_t index, float value)
{
  switch (index) {
    case 0: return (1.0f*value) + 0.0f; // Arp_Pitch
    case 1: return (1.0f*value) + 0.0f; // Arp_Speed
    case 2: return (1.0f*value) + 0.0f; // Delay_Repeats
    case 3: return (1.0f*value) + 0.0f; // Delay_Time
    default: return 0.0f;
  }
}

HeavyDPF_arp_delay_env::HeavyDPF_arp_delay_env()
 : Plugin(HV_LV2_NUM_PARAMETERS, 0, 0)
{

}

HeavyDPF_arp_delay_env::~HeavyDPF_arp_delay_env() {
  delete _context;
}

void HeavyDPF_arp_delay_env::initParameter(uint32_t index, Parameter& parameter)
{
  // initialise parameters with defaults
  switch (index)
  {
      case paramArp_Pitch:
        parameter.name = "Arp Pitch";
        parameter.symbol = "arp_pitch";
        _parameters[0] = 0.5f; // Arp_Pitch
        break;
      case paramArp_Speed:
        parameter.name = "Arp Speed";
        parameter.symbol = "arp_speed";
        _parameters[1] = 0.5f; // Arp_Speed
        break;
      case paramDelay_Repeats:
        parameter.name = "Delay Repeats";
        parameter.symbol = "delay_repeats";
        _parameters[2] = 0.5f; // Delay_Repeats
        break;
      case paramDelay_Time:
        parameter.name = "Delay Time";
        parameter.symbol = "delay_time";
        _parameters[3] = 0.5f; // Delay_Time
        break;
  }
  _context = nullptr;
  // // sampleRateChanged(0.0f); // initialise sample rate
  sampleRateChanged(44100.0f); // set sample rate to some default
}

// -------------------------------------------------------------------
// Internal data

float HeavyDPF_arp_delay_env::getParameterValue(uint32_t index) const
{
  return _parameters[index];
}

void HeavyDPF_arp_delay_env::setParameterValue(uint32_t index, float value)
{
  switch (index) {
    case 0: {
      _context->sendFloatToReceiver(
          Heavy_arp_delay_env::Parameter::In::ARP_PITCH,
          scaleParameterForIndex(index, value));
          // value);
      break;
    }
    case 1: {
      _context->sendFloatToReceiver(
          Heavy_arp_delay_env::Parameter::In::ARP_SPEED,
          scaleParameterForIndex(index, value));
          // value);
      break;
    }
    case 2: {
      _context->sendFloatToReceiver(
          Heavy_arp_delay_env::Parameter::In::DELAY_REPEATS,
          scaleParameterForIndex(index, value));
          // value);
      break;
    }
    case 3: {
      _context->sendFloatToReceiver(
          Heavy_arp_delay_env::Parameter::In::DELAY_TIME,
          scaleParameterForIndex(index, value));
          // value);
      break;
    }
    default: return;
  }
  _parameters[index] = value;
}


// -------------------------------------------------------------------
// Process

// void HeavyDPF_arp_delay_env::activate()
// {

// }

// void HeavyDPF_arp_delay_env::deactivate()
// {

// }

void HeavyDPF_arp_delay_env::run(const float** inputs, float** outputs, uint32_t frames, const MidiEvent* midiEvents, uint32_t midiEventCount)
{
  uint32_t framesDone = 0;
  uint32_t curEventIndex = 0;

  _context->process((float**)inputs, outputs, frames);

  while (framesDone < frames)
  {
    while (curEventIndex < midiEventCount && framesDone == midiEvents[curEventIndex].frame)
    {
      if (midiEvents[curEventIndex].size > MidiEvent::kDataSize)
          continue;

      int status = midiEvents[curEventIndex].data[0];
      int command = status & 0xF0;
      int channel = status & 0x0F;
      int data1   = midiEvents[curEventIndex].data[1];
      int data2   = midiEvents[curEventIndex].data[2];

      switch (command) {
        case 0x80:   // note off
        case 0x90: { // note on
          _context->sendMessageToReceiverV(0x67E37CA3, // __hv_notein
              1000.0/getSampleRate(), "fff",
              (float) data1, // pitch
              (float) data2, // velocity
              (float) channel);
          break;
        }
        case 0xB0: { // control change
          _context->sendMessageToReceiverV(0x41BE0F9C, // __hv_ctlin
              1000.0/getSampleRate(), "fff",
              (float) data2, // value
              (float) data1, // controller number
              (float) channel);
          break;
        }
        case 0xC0: { // program change
          _context->sendMessageToReceiverV(0x2E1EA03D, // __hv_pgmin,
              1000.0/getSampleRate(), "ff",
              (float) data1,
              (float) channel);
          break;
        }
        case 0xD0: { // aftertouch
          _context->sendMessageToReceiverV(0x553925BD, // __hv_touchin
              1000.0/getSampleRate(), "ff",
              (float) data1,
              (float) channel);
          break;
        }
        case 0xE0: { // pitch bend
          hv_uint32_t value = (((hv_uint32_t) data2) << 7) | ((hv_uint32_t) data1);
          _context->sendMessageToReceiverV(0x3083F0F7, // __hv_bendin
              1000.0/getSampleRate(), "ff",
              (float) value,
              (float) channel);
          break;
        }
        default: break;
      }
      curEventIndex++;
    }
    framesDone++;
  }
}

// -------------------------------------------------------------------
// Callbacks

void HeavyDPF_arp_delay_env::sampleRateChanged(double newSampleRate)
{
  if (getSampleRate() != newSampleRate) {
    delete _context;

    _context = new Heavy_arp_delay_env(newSampleRate, 10, 4, 2);
    // ensure that the new context has the current parameters
    for (int i = 0; i < HV_LV2_NUM_PARAMETERS; ++i) {
      setParameterValue(i, _parameters[i]);
    }
  }
}

// -----------------------------------------------------------------------
/* Plugin entry point, called by DPF to create a new plugin instance. */

Plugin* createPlugin()
{
    return new HeavyDPF_arp_delay_env();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO