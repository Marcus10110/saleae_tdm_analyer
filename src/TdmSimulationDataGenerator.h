#ifndef TDM_SIMULATION_DATA_GENERATOR
#define TDM_SIMULATION_DATA_GENERATOR

#include "TdmAnalyzerSettings.h"
#include "AnalyzerHelpers.h"

enum RightLeftDirection
{
    Right,
    Left
};
enum BitGenerarionState
{
    Init,
    LeftPadding,
    Data,
    RightPadding
};

class TdmSimulationDataGenerator
{
  public:
    TdmSimulationDataGenerator();
    ~TdmSimulationDataGenerator();

    void Initialize( U32 simulation_sample_rate, TdmAnalyzerSettings* settings );
    U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );

  protected:
    TdmAnalyzerSettings* mSettings;
    U32 mSimulationSampleRateHz;

    SimulationChannelDescriptorGroup mSimulationChannels;
    SimulationChannelDescriptor* mClock;
    SimulationChannelDescriptor* mFrame;
    SimulationChannelDescriptor* mData;

  protected: // I2S specitic
    void InitSineWave();
    void WriteBit( BitState data, BitState frame );
    S64 GetNextAudioWord();
    BitState GetNextAudioBit();
    BitState GetNextFrameBit();

    std::vector<S64> mSineWaveSamplesRight;
    std::vector<S64> mSineWaveSamplesLeft;

    ClockGenerator mClockGenerator;

    std::vector<BitState> mFrameBits;
    U32 mCurrentFrameBitIndex;

    std::vector<U64> mBitMasks;
    U32 mCurrentAudioWordIndex;

    RightLeftDirection mCurrentAudioChannel;
    U32 mCurrentBitIndex;
    S64 mCurrentWord;
    U32 mPaddingCount;
    BitGenerarionState mBitGenerationState;

    // Fake data settings:
    double mAudioSampleRate;
    bool mUseShortFrames;
    U32 mNumPaddingBits;
};
#endif // TDM_SIMULATION_DATA_GENERATOR
