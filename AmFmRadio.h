/*
*	FILE			: AmFmRadio.h
*	PROJECT			: AmFmRadio
*	NAME			: Chowon Jung
*	FIRST VERSION	: 2019-02-24
*	DESCRIPTION		: This file is the header file for the project AmFmRadio.
*					  This file contains :
*					  1. Load Once								: Line 15
*					  2. Constants								: Line 20
*					  3. Struct									: Line 56
*					  4. AmFmRaio Class Definition				: Line 64
*/


/* Load Once */
#ifndef _AMFMRADIO_H
#define _AMFMRADIO_H


/* Constants */
#define MAX_PRESET 5
#define AMFM 3
#define AM 0
#define FM 1
#define PRINT_AM "AM"
#define PRINT_FM "FM"
#define MAX_INPUT 20
#define MIN_VOL 0
#define MAX_VOL 100
#define MAX_AM_FREQ 17000
#define MIN_AM_FREQ 5300
#define TICK_AM 100
#define TICK_FM 2
#define MAX_FM_FREQ 1079
#define MIN_FM_FREQ 879
#define OK 0
#define ERROR -1
#define UNDER 1
#define OVER 2
#define BACK_TO_DOUBLE 10.0
#define ON true
#define OFF false
#define PRINT_ON "ON"
#define PRINT_OFF "OFF"
#define VALID_INT 1
#define SHOW_ALL_SET 0
#define SHOW_ONOFF_SET 1
#define SHOW_BAND_SET 2
#define SHOW_VOL_SET 3
#define SHOW_CUR_FREQ_SET 4
#define SHOW_PRESETS_SET 5
#define SHOW_DISPLAY_SET 6
#define NUMBER_OF_SETTINGS 6


/* Struct */
struct Freqs
{
	int AMFreq;											// AM frequency
	int FMFreq;											// FM frequency
};


/* Class */	
class AmFmRadio
{
private:
	/* Data members */
	Freqs	presets[MAX_PRESET];						// List of radio presets 5 each for AM and FM
	Freqs	prevFreq;									// Two last frequencies for AM and FM
	int		currentFreq;								// Current frequency of the radio
	int		band;										// Current band of the radio
	int		prevVolume;									// Previous volume before turned off
	int		currentVolume;								// Current volume of the radio
	bool	onOff;										// Current on/off status of the radio
	bool	displayOutput;								// Current setting about displaying setting-respond messages

public:
	/* Constructors */
	AmFmRadio(bool newOn);
	AmFmRadio(bool newOn, Freqs newPresets[MAX_PRESET]);

	/* Destructor */
	~AmFmRadio();

	/* Accessors */
	Freqs*	GetPresets(int presetIndex);				// Preset getter given by the index of preset
	Freqs*	GetPrevFreq(void);							// Previous frequency getter
	int		GetCurrentFreq(void);						// Current frequency getter
	int		GetBand(void);								// Current band getter
	int		GetVolume(void);							// Current volume getter
	int		GetPrevVolume(void);						// Previous volume getter
	bool	GetOnOff(void);								// Radio power status getter
	bool	GetDisplayOutput(void);						// Responding message setting status getter

	/* Mutators */
	int SetPreset(int preset_num, int band);			// Setter sets passed frequency as the requested preset
	int SetPrevFreq(int newPrevFreq);					// Setter saves given frequency for later use
	int SetCurrentFreq(int newCurrentFreq);				// Setter sets current frequency as newly given frequency
	int SetBand(int newBand);							// Setter sets current band as newly given band
	int SetVolume(int newVolume);						// Setter sets current volume as newly given volume
	int SetPrevVolume(int newPrevVolume);				// Setter saves given volume for later use
	bool SetOnOff(bool newOnOff);						// Setter sets current radio power as newly given status
	bool SetDisplayOutput(bool newDisplay);				// Setter sets message display setting as newly given status

	/* Methods */
	/*
	*	Method		: PowerToggle()
	*	Purpose		: This method toggles current radio power to the opposite status.
	*	Parameters	: void
	*	Return		: void
	*	Body		: AmFmRadio.cpp (Line: 288)
	*/
	void PowerToggle(void);

	/*
	*	Method		: SetVolumeByInput()
	*	Purpose		: This method sets current volume from user input prompted.
	*	Parameters	: void
	*	Return		: int OK	: when volume is set without exception
	*				: int UNDER	: when volume is set as minimum volume truncated from invalid input lower than minimum
	*				: int OVER	: when volume is set as maximum volume truncated from invalid input higher than maximum
	*	Body		: AmFmRadio.cpp (Line: 314)
	*/
	int SetVolumeByInput(void);

	/*
	*	Method		: ToggleBand()
	*	Purpose		: This method toggles current band to the opposite status.
	*	Parameters	: void
	*	Return		: void
	*	Body		: AmFmRadio.cpp (Line: 350)
	*/
	void ToggleBand(void);

	/*
	*	Method		: CurrentFreqToPreset()
	*	Purpose		: This method saves the current frequency as the preset requested.
	*	Parameters	: void
	*	Return		: int OK	: when current frequency is successfully saved as the requested preset
	*				: int ERROR : when failed
	*	Body		: AmFmRadio.cpp (Line: 367)
	*/
	int CurrentFreqToPreset(void);

	/*
	*	Method		: SelectExistingPreset()
	*	Purpose		: This method sets current frequency as the existing preset requested.
	*	Parameters	: void
	*	Return		: int OK	: when valid preset is successfully set as current frequency
	*				: int ERROR : when invalid preset is requested
	*	Body		: AmFmRadio.cpp (Line: 384)
	*/
	int SelectExistingPreset(void);

	/*
	*	Method		: ShowCurrentSettings()
	*	Purpose		: This method displays requested current settings. 
	*	Parameters	: int whatToShow :	SHOW_ALL_SET			: To show every current setting exists
	*								 :	SHOW_ONOFF_SET			: To show only current on/off status
	*								 :	SHOW_BAND_SET			: To show only current band
	*								 :	SHOW_VOL_SET			: To show only current volume 
	*								 :	SHOW_CUR_FREQ_SET		: To show only current frequency
	*								 :	SHOW_PRESETS_SET		: To show only current presets
	*								 :	SHOW_DISPLAY_SET		: To show only current display setting status
	*	Return		: void
	*	Body		: AmFmRadio.cpp (Line: 415)
	*/
	void ShowCurrentSettings(int whatToShow);

	/*
	*	Method		: ScanUp()
	*	Purpose		: This method scans the current frequency upward.
	*	Parameters	: void
	*	Return		: void
	*	Body		: AmFmRadio.cpp (Line: 497)
	*/
	void ScanUp(void);

	/*
	*	Method		: ScanDown()
	*	Purpose		: This method scans the current frequency downward.
	*	Parameters	: void
	*	Return		: void
	*	Body		: AmFmRadio.cpp (Line: 525)
	*/
	void ScanDown(void);
};
#endif