/*
*	FILE			: driver.cpp
*	PROJECT			: AmFmRadio
*	NAME			: Chowon Jung
*	FIRST VERSION	: 2019-02-24
*	DESCRIPTION		: This file is used to run the main function of the AmFmRadio project.
*					  The AmFmRadio project is used to set up a radio that :
*					  - displays menu and get user input
*					  - has ability to toggle power
*					  - has ability to customize volume
*					  - has ability to toggle band
*					  - has ability to set/load 5 presets for each band
*					  - has ability to display settings
*					  - has ability to scan up/down
*					  This file contains :
*					  1. Libraries								: Line 23
*					  2. Pragma									: Line 31
*					  3. Enum									: Line 35
*					  4. Main function							: Line 44
*/


/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include "AmFmRadio.h"
#include <iostream>
using namespace std;


/* Pragma */
#pragma warning(disable: 4996)


/* Enum */
enum menuItems
{
	kMenuNothing = 0,	// special constant for initialization only
	kMenuTogglePower = 1, kMenuSetVolume, kMenuToggleAMFM, kMenuSetButton, kMenuSelectButton,
	kMenuShowCurrentSettings, kMenuScanUp, kMenuScanDown, kMenuQuit
};


/* Main */
int main(void)
{
	menuItems	choice = kMenuNothing;
	char		buf[MAX_INPUT] = {0};
	AmFmRadio	jazzy(ON);
	bool		isRadioOn = false;
	
	//Repeat until requested to quit
	do
	{
		//Display menu
		printf("\n\nMAIN MENU\n");
		printf("=========\n\n");
		printf("1.  Toggle Power\n");
		printf("2.  Set Volume\n");
		printf("3.  Toggle AM / FM\n");
		printf("4.  Set a Preset \n"); 
		printf("5.  Select a Preset \n"); 
		printf("6.  Show Current Settings\n"); 
		printf("7.  Scan Up \n"); 
		printf("8.  Scan Down \n");
		printf("9.  Quit the Program\n");
		printf("\nMake a selection from the menu\n");

		//Get user input
		fgets(buf, sizeof(buf), stdin);
		choice = (menuItems)atoi(buf);

		switch( choice )
		{
		//If to toggle power
		case kMenuTogglePower:
			jazzy.PowerToggle();
			//Display result if the setting is on
			if (jazzy.GetDisplayOutput() == ON)								
			{
				jazzy.ShowCurrentSettings(SHOW_ONOFF_SET);
			}
			break;
		//If to set volume
		case kMenuSetVolume:
			isRadioOn = jazzy.GetOnOff();
			if (isRadioOn = ON)
			{
				switch (jazzy.SetVolumeByInput())
				{
				case ERROR :
					printf("\nYou entered a non-numeric value!\n");
					break;
				case UNDER :
					//Display result if the setting is on
					if (jazzy.GetDisplayOutput() == ON)
					{
						printf("\nThe minimum value for volume is %d. ", MIN_VOL);
					}
				case OVER :
					if (jazzy.GetDisplayOutput() == ON)
					{
						printf("\nThe maximum value for volume is %d. ", MAX_VOL);
					}
				default :
					if (jazzy.GetDisplayOutput() == ON)
					{
						jazzy.ShowCurrentSettings(SHOW_VOL_SET);
					}
				}
			}
			//If power is off
			else
			{
				printf("\nThe radio must be turned on before the "
					"volume can be set!");
			}
			break;
		//If to toggle band
		case kMenuToggleAMFM:
			isRadioOn = jazzy.GetOnOff();
			if (isRadioOn == ON)
			{
				jazzy.ToggleBand();
				//Display result if the setting is on
				if (jazzy.GetDisplayOutput() == ON)
				{
					jazzy.ShowCurrentSettings(SHOW_BAND_SET);
				}
			}
			//If power is off
			else
			{
				printf("\nThe radio must be turned on before the "
					"band can be toggled!");
			}
			break;
		//If to set current frequency as a preset button
		case kMenuSetButton:
			isRadioOn = jazzy.GetOnOff();
			if (isRadioOn == ON)
			{
				if ((jazzy.CurrentFreqToPreset()) != ERROR)
				{
					if ((jazzy.GetDisplayOutput() == ON))
					{
						printf("\nYour current frequency is now a preset.\n");
					}
				}
				//If non-numeric
				else
				{
					printf("\nYou entered a non-numeric value!\n");
				}
			}
			//If power is off
			else
			{
				printf("\nYou must turn the radio on before you set the buttons!\n");
			}
			break;
		//If to load a preset
		case kMenuSelectButton:
			isRadioOn = jazzy.GetOnOff();
			if (isRadioOn == ON)
			{
				//Check if invalid preset
				if ((jazzy.SelectExistingPreset()) == ERROR)
				{
					printf("\nYou entered an invalid preset!\n");
				}
				//Display result if the setting is on
				else
				{
					if (jazzy.GetDisplayOutput() == ON)
					{
						jazzy.ShowCurrentSettings(SHOW_CUR_FREQ_SET);
					}
				}
			}
			//If power is off
			else
			{
				printf("\nYou must turn the radio on before you select the buttons!\n");
			}
			break;
		//If to display all settings
		case kMenuShowCurrentSettings:
			jazzy.ShowCurrentSettings(SHOW_ALL_SET);
			break;
		//If to scan up current frequency
		case kMenuScanUp:
			isRadioOn = jazzy.GetOnOff();
			if (isRadioOn == ON)
			{
				jazzy.ScanUp();
				//Display result if the setting is on
				if (jazzy.GetDisplayOutput() == ON)
				{
					jazzy.ShowCurrentSettings(SHOW_CUR_FREQ_SET);
				}
			}
			//If power is off
			else
			{
				printf("\nYou must turn the radio on before you can scan up!\n");
			}
			break;
		//If to scan down current frequency
		case kMenuScanDown:
			isRadioOn = jazzy.GetOnOff();
			if (isRadioOn == ON)
			{
				jazzy.ScanDown();
				//Display result if the setting is on
				if (jazzy.GetDisplayOutput() == ON)
				{
					jazzy.ShowCurrentSettings(SHOW_CUR_FREQ_SET);
				}
			}
			//If power is off
			else
			{
				printf("\nYou must turn the radio on before you can scan down!\n");
			}
			break;
		//If to quit
		case kMenuQuit:
		    break;
		//If invalid menu
		default:
			printf("You have entered an invalid selection. Please make \n"
				   "another selection.\n");
			break;
		}
	}while( choice != kMenuQuit );

	printf("\nGoodbye!\n");
	return OK;
}