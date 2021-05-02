#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>
#include <vector>
#include <iostream>

namespace play{
class Audio
{
public:
	Audio(void);
	Audio(void (*endOfSamples)(int,int) );
	Audio( void (*my_callback)(void *userdata, Uint8 *stream, int len),void (*endOfSamples)(int,int));
	~Audio(void);
	int  loadWav( char* filename );					// returns handle
	int  loadWav( char* filename, float volume );	// returns handle
	int  loadWav( char* filename, float volume, bool reverseFlag );	// returns handle
	//
	bool	stop(int handle);
	bool	play(int handle);
	bool	play(int handle, int numberOfTimes);
	bool	play( int handle, int numberOfTimes, int channel );
//	void	resetPlayPosition( int handle, int channel );

private:
	void hardwarePlay(void);
	void hardwareStop(void);
	void*	getCurrentSampleBuffer(int handle, int channel);
	bool	AdvanceCurrentSampleBuffer(int handle, int channel);

	// structure
	typedef struct{
	int amountOfBlocks;				// blockBuffers.size() amount
	int currentPlayingBlock;		// range from 0 to blockBuffers.size()
	int	repeatNumberOfTimes;		// how many times the file will be played
	int	repeatNumberOfTimesCounter;	// how many times the file will be played, counter
	bool isPlaying;					// true or false
	}playStruct;					// not used yet

//	std::vector<playStruct*> plays;	// one such structure for each channel

	// structure - - - - - - - - - - - - - - - - - - - - 
	typedef struct wavData{
		wavData(){
			filename = NULL;
			buffer = NULL;
			length = 0;
			bitSize = 16;
			block = 0;
			rest = 0;
		}
	std::vector<Uint8*> blockBuffers;	// small memory blocks
	std::vector<playStruct*> plays;	// one such structure for each channel
	char			*filename;
	Uint8			*buffer;
	Uint32			length;		// in bytes
	int				bitSize;	// either 8 or 16.
	SDL_AudioSpec	spec;
	int block;			// block modulus size of buffer
	int rest;			// small rest, when size of buffer is uneven.
	} wavData;			// wad...one for each wave file loaded, use wavs[index] to reach
	// structure - - - - - - - - - - - - - - - - - - - - 


	//
	int channelHandle[6]; 
	//
	void (*jumpBack)(int handle,int channel);	// used for callback when sample ends.
	//code
	static void privateStaticAudioCallback(void *userdata, Uint8 *stream, int len);
	//
	void privateApplyVolumeOnBuffer( char *buffer, int length, float volume );
	void privateApplyLowpassFilterOnBuffer( char *buffer, int length ); // lowpass filter
	void privateApplyReverseOnBuffer( char *buffer, int length );
	//
	char *debugShowFormat( Uint16 format );
	void debugShowAudioSpec( SDL_AudioSpec *wspec, bool isWav );
	void debugShowAudioCVT(SDL_AudioCVT *cvt);
	//
	void privateInit( void (*my_callback)(void *userdata, Uint8 *stream, int len),void (*endOfSamples)(int,int));
	void privateTransformFromBufferIntoBuffers( int handle );
	bool privateTransformIntoHardwareFormat( int currentIndex ); // private
	void privateCalcBlockAndRest( int handle );
	// data
	bool initHardwareFlag;	// if hardware have been initted or not.
	bool debugFlag;			// good for developing.
	SDL_AudioSpec *hardwareFormat;	// the hardware format
	Uint8 *silencedBuffer; //
	
/*
typedef struct{
  int freq;			//Audio frequency in samples per second
  Uint16 format;	//Audio data format
  Uint8 channels;	//Number of channels: 1 mono, 2 stereo
  Uint8 silence;	//Audio buffer silence value (calculated)
  Uint16 samples;	//Audio buffer size in samples
  Uint32 size;		//Audio buffer size in bytes (calculated)
  void (*callback)(void *userdata, Uint8 *stream, int len);
  void *userdata;
} SDL_AudioSpec;
//
typedef struct{
  int needed;
  Uint16 src_format;
  Uint16 dest_format;
  double rate_incr;
  Uint8 *buf;
  int len;
  int len_cvt;
  int len_mult;
  double len_ratio;
  void (*filters[10])(struct SDL_AudioCVT *cvt, Uint16 format);
  int filter_index;
} SDL_AudioCVT;
*/
	std::vector<wavData*>wavs;		// each wav that is loaded.

};
} // namespace
#endif
