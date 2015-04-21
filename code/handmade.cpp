/*
* @Author: dingxijin
* @Date:   2015-04-21 08:09:18
* @Last Modified by:   dingxijin
* @Last Modified time: 2015-04-21 15:36:54
*/

#include "handmade.h"

internal void
UpdateSound(game_sound_buffer *SoundBuffer)
{
  local_persist float tSine;
  int ToneVolume = 5000;
  int16_t *SampleOut = SoundBuffer->Samples;
  for(int SampleIndex = 0 ;SampleIndex < SoundBuffer->SampleCount ;
    SampleIndex++)
  {
    float SineValue = sinf(tSine);
    int16_t SampleValue = (int16_t)(SineValue * ToneVolume);
    *SampleOut++ = SampleValue;
    *SampleOut++ = SampleValue;
    tSine += 2.0f * Pi32 / (float)(SoundBuffer->WavePeriod);
  }
}

internal void
RenderWeirdGradient(game_offscreen_buffer *Buffer, int BlueOffset, int GreenOffset)
{
  uint8_t *Row = (uint8_t *)Buffer->Memory;

  for(int Y = 0;Y < Buffer->Height; Y++)
  {
    uint32_t *Pixel = (uint32_t *)Row;
    for(int X = 0; X < Buffer->Width; X++)
    {
      // Memory Order: BB GG RR XX
      // 0xXXRRGGBB
      uint8_t Blue = X + BlueOffset;
      uint8_t Green = Y + GreenOffset;

      *Pixel++ = ((Green << 8) | Blue );

    }
    Row += Buffer->Pitch;
  }
}

internal void
GameUpdateAndRender(game_offscreen_buffer *Buffer, int BlueOffset, int GreenOffset, game_sound_buffer *SoundBuffer)
{
  UpdateSound(SoundBuffer);
  RenderWeirdGradient(Buffer, BlueOffset, GreenOffset);
}