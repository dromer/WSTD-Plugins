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

#ifndef _HEAVY_LV2_ARP_DELAY_ENV_
#define _HEAVY_LV2_ARP_DELAY_ENV_

#include "DistrhoPlugin.hpp"
#include "Heavy_arp_delay_env.hpp"

START_NAMESPACE_DISTRHO

class HeavyDPF_arp_delay_env : public Plugin
{
public:
  enum Parameters
  {
      paramArp_Pitch,
      paramArp_Speed,
      paramDelay_Repeats,
      paramDelay_Time,
  };

  HeavyDPF_arp_delay_env();
  ~HeavyDPF_arp_delay_env() override;

protected:
  // -------------------------------------------------------------------
  // Information

  const char* getLabel() const noexcept override
  {
    return "arp_delay_env";
  }

  const char* getDescription() const override
  {
    return "";
  }

  const char* getMaker() const noexcept override
  {
    return "Wasted Audio";
}

  const char* getHomePage() const override
  {
    return "https://github.com/wasted.audio/arp_delay_env";
  }

  const char* getLicense() const noexcept override
  {
    return "GPL v3+";
  }

  uint32_t getVersion() const noexcept override
  {
    return d_version(0, 0, 1);
  }

  int64_t getUniqueId() const noexcept override
  {
    // return d_cconst('W', 'S', 't', 'd');
    return int64_t( 0x53FCAAC1 );
  }

  // -------------------------------------------------------------------
  // Init

  void initParameter(uint32_t index, Parameter& parameter) override;

  // -------------------------------------------------------------------
  // Internal data

  float getParameterValue(uint32_t index) const override;
  void  setParameterValue(uint32_t index, float value) override;

  // -------------------------------------------------------------------
  // Process

  // void activate() override;
  // void deactivate() override;
  void run(const float** inputs, float** outputs, uint32_t frames, const MidiEvent* midiEvents, uint32_t midiEventCount) override;

  // -------------------------------------------------------------------
  // Callbacks

  void sampleRateChanged(double newSampleRate) override;

  // -------------------------------------------------------------------

private:
  // parameters
  float _parameters[4]; // in range of [0,1]

  // heavy context
  HeavyContextInterface *_context;

  // HeavyDPF_arp_delay_env<float> farp_delay_env;

  DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeavyDPF_arp_delay_env)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // _HEAVY_LV2_ARP_DELAY_ENV_
