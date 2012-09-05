/**
 * @file mmreg.h
 * @copy 2012 MinGW.org project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifndef _MMREG_H
#define _MMREG_H
#pragma GCC system_header

#ifndef _MMSYSTEM_H
#include <mmsystem.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- DirectShow Reference - DirectShow Structures */
typedef struct mpeg1waveformat_tag {
	WAVEFORMATEX wfx;
	WORD fwHeadLayer;
	DWORD dwHeadBitrate;
	WORD fwHeadMode;
	WORD fwHeadModeExt;
	WORD wHeadEmphasis;
	WORD fwHeadFlags;
	DWORD dwPTSLow;
	DWORD dwPTSHigh;
} MPEG1WAVEFORMAT;
#define ACM_MPEG_LAYER1 0x0001
#define ACM_MPEG_LAYER2 0x0002
#define ACM_MPEG_LAYER3 0x0004
#define ACM_MPEG_STEREO 0x0001
#define ACM_MPEG_JOINTSTEREO 0x0002
#define ACM_MPEG_DUALCHANNEL 0x0004
#define ACM_MPEG_SINGLECHANNEL 0x0008
#define ACM_MPEG_PRIVATEBIT 0x0001
#define ACM_MPEG_COPYRIGHT 0x0002
#define ACM_MPEG_ORIGINALHOME 0x0004
#define ACM_MPEG_PROTECTIONBIT 0x0008
#define ACM_MPEG_ID_MPEG1 0x0010
typedef struct {
	WAVEFORMATEX Format;
	union {
		WORD wValidBitsPerSample;
		WORD wSamplesPerBlock;
		WORD wReserved;
	} Samples;
	DWORD dwChannelMask; 
	GUID SubFormat;
} WAVEFORMATEXTENSIBLE,*PWAVEFORMATEXTENSIBLE;
#define SPEAKER_FRONT_LEFT 0x1
#define SPEAKER_FRONT_RIGHT 0x2
#define SPEAKER_FRONT_CENTER 0x4
#define SPEAKER_LOW_FREQUENCY 0x8
#define SPEAKER_BACK_LEFT 0x10
#define SPEAKER_BACK_RIGHT 0x20
#define SPEAKER_FRONT_LEFT_OF_CENTER 0x40
#define SPEAKER_FRONT_RIGHT_OF_CENTER 0x80
#define SPEAKER_BACK_CENTER 0x100
#define SPEAKER_SIDE_LEFT 0x200
#define SPEAKER_SIDE_RIGHT 0x400
#define SPEAKER_TOP_CENTER 0x800
#define SPEAKER_TOP_FRONT_LEFT 	0x1000
#define SPEAKER_TOP_FRONT_CENTER 0x2000
#define SPEAKER_TOP_FRONT_RIGHT 0x4000
#define SPEAKER_TOP_BACK_LEFT 0x8000
#define SPEAKER_TOP_BACK_CENTER 0x10000
#define SPEAKER_TOP_BACK_RIGHT 0x20000

/*msdn.microsoft.com/en-us/library/dd390710%28VS.85%29.aspx*/
typedef struct mpeglayer3waveformat_tag {
  WAVEFORMATEX wfx;
  WORD         wID;
  DWORD        fdwFlags;
  WORD         nBlockSize;
  WORD         nFramesPerBlock;
  WORD         nCodecDelay;
} MPEGLAYER3WAVEFORMAT, *LPMPEGLAYER3WAVEFORMAT;

/* http://www.ietf.org/rfc/rfc2361.txt */
#define WAVE_FORMAT_UNKNOWN                 0x0000
#define WAVE_FORMAT_PCM                     0x0001
#define WAVE_FORMAT_ADPCM                   0x0002
#define WAVE_FORMAT_IEEE_FLOAT              0x0003
#define WAVE_FORMAT_VSELP                   0x0004
#define WAVE_FORMAT_IBM_CVSD                0x0005
#define WAVE_FORMAT_ALAW                    0x0006
#define WAVE_FORMAT_MULAW                   0x0007

#define WAVE_FORMAT_OKI_ADPCM               0x0010
#define WAVE_FORMAT_DVI_ADPCM               0x0011
#define WAVE_FORMAT_MEDIASPACE_ADPCM        0x0012
#define WAVE_FORMAT_SIERRA_ADPCM            0x0013
#define WAVE_FORMAT_G723_ADPCM              0x0014
#define WAVE_FORMAT_DIGIFIX                 0x0016
#define WAVE_FORMAT_DIALOGIC_OKI_ADPCM      0x0017
#define WAVE_FORMAT_MEDIAVISION_ADPCM       0x0018
#define WAVE_FORMAT_CU_CODEC                0x0019
#define WAVE_FORMAT_YAMAHA_ADPCM            0x0020
#define WAVE_FORMAT_SONARC                  0x0021
#define WAVE_FORMAT_DSPGROUP_TRUESPEECH     0x0022
#define WAVE_FORMAT_ECHOSC1                 0x0023
#define WAVE_FORMAT_AUDIOFILE_AF36          0x0024
#define WAVE_FORMAT_APTX                    0x0025
#define WAVE_FORMAT_AUDIOFILE_AF10          0x0026
#define WAVE_FORMAT_PROSODY_1612            0x0027
#define WAVE_FORMAT_LRC                     0x0028

#define WAVE_FORMAT_DOLBY_AC2               0x0030
#define WAVE_FORMAT_GSM610                  0x0031
#define WAVE_FORMAT_MSNAUDIO                0x0032
#define WAVE_FORMAT_ANTEX_ADPCME            0x0033
#define WAVE_FORMAT_CONTROL_RES_VQLPC       0x0034
#define WAVE_FORMAT_DIGIREAL                0x0035
#define WAVE_FORMAT_DIGIADPCM               0x0036
#define WAVE_FORMAT_CONTROL_RES_CR10        0x0037
#define WAVE_FORMAT_NMS_VBXADPCM            0x0038
#define WAVE_FORMAT_ROLAND_RDAC             0x0039
#define WAVE_FORMAT_ECHOSC3                 0x003A
#define WAVE_FORMAT_ROCKWELL_ADPCM          0x003B
#define WAVE_FORMAT_ROCKWELL_DIGITALK       0x003C
#define WAVE_FORMAT_XEBEC                   0x003D

#define WAVE_FORMAT_G721_ADPCM              0x0040
#define WAVE_FORMAT_G728_CELP               0x0041
#define WAVE_FORMAT_MSG723                  0x0042

#define WAVE_FORMAT_MPEG                    0x0050

#define WAVE_FORMAT_RT24                    0x0052
#define WAVE_FORMAT_PAC                     0x0053

#define WAVE_FORMAT_MPEGLAYER3              0x0055

#define WAVE_FORMAT_LUCENT_G723             0x0059
#define WAVE_FORMAT_CIRRUS                  0x0060
#define WAVE_FORMAT_ESPCM                   0x0061
#define WAVE_FORMAT_VOXWARE                 0x0062
#define WAVE_FORMAT_CANOPUS_ATRAC           0x0063
#define WAVE_FORMAT_G726_ADPCM              0x0064
#define WAVE_FORMAT_G722_ADPCM              0x0065
#define WAVE_FORMAT_DSAT                    0x0066
#define WAVE_FORMAT_DSAT_DISPLAY            0x0067

#define WAVE_FORMAT_VOXWARE_BYTE_ALIGNED    0x0069
#define WAVE_FORMAT_VOXWARE_AC8             0x0070
#define WAVE_FORMAT_VOXWARE_AC10            0x0071
#define WAVE_FORMAT_VOXWARE_AC16            0x0072
#define WAVE_FORMAT_VOXWARE_AC20            0x0073
#define WAVE_FORMAT_VOXWARE_RT24            0x0074
#define WAVE_FORMAT_VOXWARE_RT29            0x0075
#define WAVE_FORMAT_VOXWARE_RT29HW          0x0076
#define WAVE_FORMAT_VOXWARE_VR12            0x0077
#define WAVE_FORMAT_VOXWARE_VR18            0x0078
#define WAVE_FORMAT_VOXWARE_TQ40            0x0079
#define WAVE_FORMAT_SOFTSOUND               0x0080
#define WAVE_FORMAT_VOXWARE_TQ60            0x0081
#define WAVE_FORMAT_MSRT24                  0x0082
#define WAVE_FORMAT_G729A                   0x0083
#define WAVE_FORMAT_MVI_MV12                0x0084
#define WAVE_FORMAT_DF_G726                 0x0085
#define WAVE_FORMAT_DF_GSM610               0x0086

#define WAVE_FORMAT_ISIAUDIO                0x0088
#define WAVE_FORMAT_ONLIVE                  0x0089

#define WAVE_FORMAT_SBC24                   0x0091
#define WAVE_FORMAT_DOLBY_AC3_SPDIF         0x0092

#define WAVE_FORMAT_ZYXEL_ADPCM             0x0097
#define WAVE_FORMAT_PHILIPS_LPCBB           0x0098
#define WAVE_FORMAT_PACKED                  0x0099
#define WAVE_FORMAT_RHETOREX_ADPCM          0x0100
#define WAVE_FORMAT_IRAT                    0x0101
#define WAVE_FORMAT_VIVO_G723               0x0111
#define WAVE_FORMAT_VIVO_SIREN              0x0112
#define WAVE_FORMAT_DIGITAL_G723            0x0113

#define WAVE_FORMAT_CREATIVE_ADPCM          0x0200

#define WAVE_FORMAT_CREATIVE_FASTSPEECH8    0x0202
#define WAVE_FORMAT_CREATIVE_FASTSPEECH10   0x0203

#define WAVE_FORMAT_QUARTERDECK             0x0220

#define WAVE_FORMAT_FM_TOWNS_SND            0x0300

#define WAVE_FORMAT_BTV_DIGITAL             0x0400

#define WAVE_FORMAT_VME_VMPCM               0x0680

#define WAVE_FORMAT_OLIGSM                  0x1000
#define WAVE_FORMAT_OLIADPCM                0x1001
#define WAVE_FORMAT_OLICELP                 0x1002
#define WAVE_FORMAT_OLISBC                  0x1003
#define WAVE_FORMAT_OLIOPR                  0x1004

#define WAVE_FORMAT_LH_CODEC                0x1100

#define WAVE_FORMAT_NORRIS                  0x1400
#define WAVE_FORMAT_ISIAUDIO                0x1401

#define WAVE_FORMAT_SOUNDSPACE_MUSICOMPRESS 0x1500

#define WAVE_FORMAT_DVM                     0x2000

/* http://msdn.microsoft.com/en-us/library/aa372553%28VS.85%29.aspx */
#define WAVE_FORMAT_RAW_AAC1                0x00FF
#define WAVE_FORMAT_MPEG_HEAAC              0x1610
#define WAVE_FORMAT_MPEG_ADTS_AAC           0x1600
#define WAVE_FORMAT_DRM                     0x0009
#define WAVE_FORMAT_DTS                     0x0008
#define WAVE_FORMAT_WMAVOICE9               0x000A
#define WAVE_FORMAT_WMASPDIF                0x0164
#define WAVE_FORMAT_WMAUDIO_LOSSLESS        0x0163
#define WAVE_FORMAT_WMAUDIO2                0x0161
#define WAVE_FORMAT_WMAUDIO3                0x0162

/* http://msdn.microsoft.com/en-us/library/dd317599%28VS.85%29.aspx */
#define WAVE_FORMAT_MPEG_LOAS               0x1602
#define WAVE_FORMAT_RAW_SPORT               0x0240
#define WAVE_FORMAT_ESST_AC3                0x0241
#define WAVE_FORMAT_DTS2                    0x2001

#ifdef __cplusplus
}
#endif
#endif