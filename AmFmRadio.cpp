/*
*	FILE			: AmFmRadio.cpp
*	PROJECT			: AmFmRadio
*	NAME			: Chowon Jung
*	FIRST VERSION	: 2019-02-24
*	DESCRIPTION		: This file contains all the method bodies of the AmFmRadio class.
*					  The included methodes are :
*					  1. Libraries								: Line 18
*					  2. Pragma									: Line 27
*					  3. Constructors							: Line 31
*					  4. Destructor								: Line 77
*					  5. Accessors								: Line 84
*					  6. Mutators								: Line 136
*					  7. Methods								: Line 287
*/


/* Libraries */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#include "AmFmRadio.h"


/* Pragma */
#pragma warning(disable: 4996)


/* ***************************** Constructors ***************************** */
AmFmRadio::AmFmRadio(bool newOn = OFF)
{
	//Set all presets default as lowest frequencies
	for( int i = 0; i < MAX_PRESET; ++i )
	{
		presets[i].AMFreq = MIN_AM_FREQ;
	}
	for( int j = 0; j < MAX_PRESET; ++j )
	{
		presets[j].FMFreq = MIN_FM_FREQ;
	}
	//Set other default values
	prevFreq.AMFreq = MIN_AM_FREQ;
	prevFreq.FMFreq = MIN_FM_FREQ;
	currentFreq		= MIN_AM_FREQ;
	band			= AM;
	prevVolume		= MIN_VOL;
	currentVolume	= MIN_VOL;
	onOff			= newOn;
	displayOutput	= OFF;
}

AmFmRadio::AmFmRadio(bool newOn, Freqs newPresets[MAX_PRESET])
{
	//Set all default presets by given new presets
	for (int i = 0; i < MAX_PRESET; ++i)
	{
		presets[i].AMFreq = newPresets[i].AMFreq;
	}
	for (int j = 0; j < MAX_PRESET; ++j)
	{
		presets[j].FMFreq = newPresets[j].FMFreq;
	}
	//Set other default values
	prevFreq.AMFreq	= MIN_AM_FREQ;
	prevFreq.FMFreq = MIN_FM_FREQ;
	currentFreq		= MIN_AM_FREQ;
	band			= AM;
	prevVolume		= MIN_VOL;
	currentVolume	= MIN_VOL;
	onOff			= newOn;
	displayOutput	= OFF;
}


/* ***************************** Destructor ***************************** */
AmFmRadio::~AmFmRadio()
{
	cout << "Destroying AmFmRadio";
}


/* ***************************** Accessors ***************************** */
Freqs* AmFmRadio::GetPresets(int presetIndex)
{
	//Return by value to avoid passing pointer
	Freqs subPresets;
	subPresets.AMFreq = presets[presetIndex].AMFreq;
	subPresets.FMFreq = presets[presetIndex].FMFreq;

	return &subPresets;
}

Freqs* AmFmRadio::GetPrevFreq(void)
{
	//Return by value to avoid passing pointer
	Freqs subPrevFreq;
	subPrevFreq.AMFreq = prevFreq.AMFreq;
	subPrevFreq.FMFreq = prevFreq.FMFreq;

	return &subPrevFreq;
}

int AmFmRadio::GetCurrentFreq(void)
{
	return currentFreq;
}

int AmFmRadio::GetBand(void)
{
	return band;
}

int	AmFmRadio::GetVolume(void)
{
	return currentVolume;
}

int	AmFmRadio::GetPrevVolume(void)
{
	return prevVolume;
}

bool AmFmRadio::GetOnOff(void)
{
	return onOff;
}

bool AmFmRadio::GetDisplayOutput(void)
{
	return displayOutput;
}


/* ***************************** Mutators ***************************** */
int AmFmRadio::SetPreset(int preset_num, int band)
{
	//Check if valid preset
	if ((preset_num >= 0) && (preset_num < MAX_PRESET))
	{
		//Put in proper band preset
		if (band == AM)
		{
			presets[preset_num].AMFreq = GetCurrentFreq();
		}
		else
		{
			presets[preset_num].FMFreq = GetCurrentFreq();
		}
		return OK;
	}
	return ERROR;
}

int AmFmRadio::SetPrevFreq(int newPrevFreq)
{
	//Save current frequency of current band
	if (GetBand() == AM)
	{
		//Check if valid AM frequency
		if ((newPrevFreq >= MIN_AM_FREQ) &&
			(newPrevFreq <= MAX_AM_FREQ))
		{
			prevFreq.AMFreq = newPrevFreq;
		}
		return AM;
	}
	else
	{
		//Check if valid FM frequency
		if ((newPrevFreq >= MIN_FM_FREQ) &&
			(newPrevFreq <= MAX_FM_FREQ))
		{
			prevFreq.FMFreq = newPrevFreq;
		}
		return FM;
	}
	return ERROR;
}

int AmFmRadio::SetCurrentFreq(int newCurrentFreq)
{
	if (GetBand() == AM)
	{
		//Check if valid frequency for AM requested
		if ((newCurrentFreq >= MIN_AM_FREQ) &&
			(newCurrentFreq <= MAX_AM_FREQ))
		{
			currentFreq = newCurrentFreq;
			return AM;
		}
	}
	else
	{
		//Check if valid frequency for FM requested
		if ((newCurrentFreq >= MIN_FM_FREQ) &&
			(newCurrentFreq <= MAX_FM_FREQ))
		{
			currentFreq = newCurrentFreq;
			return FM;
		}
	}
	return ERROR;
}

int AmFmRadio::SetBand(int newBand)
{
	//Check if valid band requested
	if ((newBand == AM) ||
		(newBand == FM))
	{
		band = newBand;
		return OK;
	}
	return ERROR;
}

int AmFmRadio::SetVolume(int newVolume)
{
	//if user enters volume less than 0, volume = 0
	if (newVolume < MIN_VOL)
	{
		newVolume = MIN_VOL;
		return UNDER;
	}
	//if user enters volume greater than 100, volume = 100
	if (newVolume > MAX_VOL)
	{
		newVolume = MAX_VOL;
		return OVER;
	}

	currentVolume = newVolume;
	return OK;
}

int AmFmRadio::SetPrevVolume(int newPrevVolume)
{
	//Check if valid volume
	if (newPrevVolume < MIN_VOL)
	{
		prevVolume = MIN_VOL;
		return UNDER;
	}
	if (newPrevVolume > MAX_VOL) 
	{
		prevVolume = MAX_VOL;
		return OVER;
	}

	prevVolume = newPrevVolume;
	return OK;
}

bool AmFmRadio::SetOnOff(bool newOnOff)
{
	//Set power by passed value
	if (newOnOff == ON)
	{
		onOff = ON;
		return ON;
	}
	else
	{
		onOff = OFF;
		return OFF;
	}
}

bool AmFmRadio::SetDisplayOutput(bool newDisplay)
{
	//Set display option by passed value
	if (newDisplay == ON)
	{
		displayOutput = ON;
		return ON;
	}
	else
	{
		displayOutput = OFF;
		return OFF;
	}
}


/* ***************************** Methods ***************************** */
void AmFmRadio::PowerToggle(void)
{
	//Read current power status and set opposite
	if (GetOnOff() == OFF)
	{
		//Read previous volume and frequency when turn on
		SetVolume(GetPrevVolume());
		if (GetBand() == AM)
		{
			SetCurrentFreq(GetPrevFreq()->AMFreq);
		}
		else
		{
			SetCurrentFreq(GetPrevFreq()->FMFreq);
		}
		SetOnOff(ON);
	}
	else
	{
		//Save current volume and mute when turn off
		SetPrevVolume(GetVolume());
		SetVolume(MIN_VOL);
		SetOnOff(OFF);
	}
}

int AmFmRadio::SetVolumeByInput(void)
{
	char buf[MAX_INPUT] = "";
	int newVolume = 0;
	int result = ERROR;

	//Prompt user input
	printf("\nEnter the volume level (0 - 100). ");
	fgets(buf, sizeof buf, stdin);
	//Check if valid input
	if (sscanf(buf, "%d", &newVolume) == VALID_INT)
	{
		//Set volume
		switch (SetVolume(newVolume))
		{
		case OK:
			result = OK;
			break;
		case UNDER:
			SetVolume(MIN_VOL);
			result = UNDER;
			break;
		case OVER:
			SetVolume(MAX_VOL);
			result = OVER;
			break;
		}
	}
	else
	{
		printf("\nAre you sure you have entered a number? Please enter an integer between 0-100.\n");
		result = ERROR;
	}
	return result;
}

void AmFmRadio::ToggleBand(void)
{
	//Save previous frequency and toggle
	if(GetBand() == AM)
	{
		SetPrevFreq(GetCurrentFreq());
		SetBand(FM);
		SetCurrentFreq(GetPrevFreq()->FMFreq);
	}
	else
	{
		SetPrevFreq(GetCurrentFreq());
		SetBand(AM);
		SetCurrentFreq(GetPrevFreq()->AMFreq);
	}
}

int AmFmRadio::CurrentFreqToPreset(void)
{
	char buf[MAX_INPUT] = "";
	int preset_num = 0;

	//Prompt user input
	printf("\nEnter the number of the preset to set: ");
	fgets(buf, sizeof(buf), stdin);
	if ((sscanf(buf, "%d", &preset_num)) == VALID_INT)
	{
		//Set as corresponding index
		--preset_num;
		return SetPreset(preset_num, GetBand());
	}
	return ERROR;
}

int AmFmRadio::SelectExistingPreset()
{
	char buf[MAX_INPUT] = "";
	int preset_num = 0;

	//Prompt user input
	printf("\nEnter the number of the preset to load: ");
	fgets(buf, sizeof(buf), stdin);
	if ((sscanf(buf, "%d", &preset_num)) == VALID_INT)
	{
		//Set as corresponding index
		--preset_num;
		//Check if valid preset
		if ((preset_num > 0) &&
			(preset_num <= MAX_PRESET))
		{
			//Load requested preset matches current band
			if (GetBand() == AM)
			{
				SetCurrentFreq(GetPresets(preset_num)->AMFreq);
			}
			else
			{
				SetCurrentFreq(GetPresets(preset_num)->FMFreq);
			}
			return OK;
		}
	}
	return ERROR;
}

void AmFmRadio::ShowCurrentSettings(int whatToShow)
{
	int showHowMany = 0;

	//Check if to display all settings
	if (whatToShow == SHOW_ALL_SET)
	{
		//Set counter to print all settings
		showHowMany = NUMBER_OF_SETTINGS;
		whatToShow++;
	}

	//Repeat once if not requested to display all
	//Repeat until all settings displayed when requested to
	for (int i = 0; i <= showHowMany; i++)
	{
		switch (whatToShow)
		{
		case SHOW_ONOFF_SET:
			if (onOff == true)
			{
				printf("\n\nRadio is on. \n");
			}
			else
			{
				printf("\n\nRadio is off. \n");
			}
			break;
		case SHOW_BAND_SET:
			printf("\nFrequency: ");
			if (GetBand() == AM)
			{
				printf("%s\n", PRINT_AM);
			}
			else
			{
				printf("%s\n", PRINT_FM);
			}
			break;
		case SHOW_VOL_SET:
			printf("Volume: %d\n", GetVolume());
			break;
		case SHOW_CUR_FREQ_SET:
			printf("Current Station: %.1f", ((double)GetCurrentFreq())/BACK_TO_DOUBLE);
			if (GetBand() == AM)
			{
				printf(" %s\n", PRINT_AM);
			}
			else
			{
				printf(" %s\n", PRINT_FM);
			}
			break;
		case SHOW_PRESETS_SET:
			printf("AM Preset Settings: ");
			for (int i = 0; i < MAX_PRESET; ++i)
			{
				printf("%d) %6.1f ", i + 1, (GetPresets(i)->AMFreq) / BACK_TO_DOUBLE);
			}
			printf("\nFM Preset Settings: ");
			for (int j = 0; j < MAX_PRESET; ++j)
			{
				printf("%d) %6.1f ", j + 1, (GetPresets(j)->FMFreq) / BACK_TO_DOUBLE);
			}
			break;
		case SHOW_DISPLAY_SET:
			printf("\nDisplay Message Settings: ");
			if (GetDisplayOutput() == ON)
			{
				printf("%s\n", PRINT_ON);
			}
			else
			{
				printf("%s\n", PRINT_OFF);
			}
			break;
		}
		//Prepare displaying next setting
		whatToShow++;
	}
}

void AmFmRadio::ScanUp(void)
{
	if(GetBand() == AM)
	{
		//if current_station is 1700, the current_station becomes 530
		if( GetCurrentFreq() >= MAX_AM_FREQ )
		{
			SetCurrentFreq(MIN_AM_FREQ);
		}
		else
		{
			SetCurrentFreq(GetCurrentFreq() + TICK_AM);
		}
	}
	else
	{
		//if the current_station is 107.9, the current_station becomes 87.9
		if( GetCurrentFreq() >= MAX_FM_FREQ )
		{
			SetCurrentFreq(MIN_FM_FREQ);
		}
		else
		{
			SetCurrentFreq(GetCurrentFreq() + TICK_FM);
		}
	}
}

void AmFmRadio::ScanDown(void)
{
	if (GetBand() == AM)
	{
		//if current_station is 530, the current_station becomes 1700
		if (GetCurrentFreq() <= MIN_AM_FREQ)
		{
			SetCurrentFreq(MAX_AM_FREQ);
		}
		else
		{
			SetCurrentFreq(GetCurrentFreq() - TICK_AM);
		}
	}
	else
	{
		//if the current_station is 87.9, the current_station becomes 107.9
		if (GetCurrentFreq() <= MIN_FM_FREQ)
		{
			SetCurrentFreq(MAX_FM_FREQ);
		}
		else
		{
			SetCurrentFreq(GetCurrentFreq() - TICK_FM);
		}
	}
}