#include "kos.h";
#include <stdio.h>;
#include <oggvorbis/sndoggvorbis.h>;

//initialize the romdisk where we access to the frames and the music
extern uint8 romdisk_boot[];
KOS_INIT_ROMDISK(romdisk_boot);

int main()
{
	pvr_init_defaults();
	vid_set_mode(DM_640x480_VGA, PM_RGB565);
	
	//get the lcd of the first VMU
	maple_device* lcd;
	
	while (lcd == NULL)
	{
		lcd = maple_enum_type(0, MAPLE_FUNC_LCD);
	}

	//open file and put all of the contents to the buffer
	file_t pfile = fs_open("/rd/frames.bin", O_RDONLY);
	size_t fLength = fs_total(pfile);

	uint8 buffer[fLength];

	//return value was originally used for debug purposes
	ssize_t bytesCount = fs_read(pfile, buffer, fLength);

	uint8 currFrameBuffer[192];

	//initialize the sound system and play the ogg music
	snd_stream_init();

	sndoggvorbis_init();
	sndoggvorbis_start("/rd/music.ogg", 0);

	uint64 curTime;
	uint64 oldTime;
	for (size_t i = 0; i < fLength / 192; i++)
	{
		oldTime = timer_us_gettime64(); //internal KallistiOS µs timer
		for (size_t j = 0; j < 192; j++)
		{
			currFrameBuffer[j] = buffer[(i * 192) + j]; //there surely is a built in function for this but this works well enough anyway and should be fast enough
		}
		
		vmu_draw_lcd(lcd, currFrameBuffer);
		
		curTime = timer_us_gettime64();
		timer_spin_sleep(33 - ((curTime - oldTime) / 1000)); // get how long we gotta wait before processing the next frame (shoutouts to skewb for the maths here :p )
		//additional note: this might actually make the song end up after the frames are finished because we should normally pause for 33.33... frames but this only accepts an integer
	}

	//done with the stuff, cleanup and exit
	sndoggvorbis_stop();
	sndoggvorbis_shutdown();
	snd_stream_shutdown();

	return 0;
}