# MPlayer with libogc2 support

This updates MPlayer CE so that it can compile with the latest devkit and libogc2, enabling the gc-loader, cubeode, or sd2sp2 to work as a valid storage device.

I added some new options that can be activated by editing mplayer.conf on the /apps/mplayer-ce/ path.


# Shuffle
* Make sure dir_play=1 is on the conf.
* Write dir_shuffle=1 to use the shuffle mode.
* Optionally, also use dir_loop=1 to loop thru files endlessly.


# 240p
* Use video_mode=5 to force 240p output.
* Region should be detected automatically, but only NTSC has been tested.

# FFmpeg updates
* A couple of upstream fixes have been copied over here.
* This improves ADX and BRSTM support.

Video framerate is also detected. If it's close to 29.97 or 30 fps, it will use Extrems' PsF register poke that makes the console output 29.97, this allows video to play smoothly, in a consistent way.

The original paired-singles code is present with the exception of some h264 functions that result in occasional odd-colored artifacts.



# Known Issues

It's best to use the overscan=0 setting paired with panscan=1 for interlaced, 720x480 DVD-type of videos. Removing overscan may make some text difficult to read, but you can use the control stick to move the interface around, and Z to reset.

While VP8 and H264 encodes will almost certainly need lavdopts=fast=1:skiploopfilter=all to improve speed.
