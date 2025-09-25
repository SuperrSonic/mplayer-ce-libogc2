for %%A IN (*.mp4) do (
"ffmpeg.exe"  -i "%%~A" -vf crop=1440:ih:240:0,scale='512:480:flags=lanczos',setdar='4/3' -vcodec libx264 -profile:v baseline -level:v 3.0 -vb 2000k -refs 1 -me_method umh -subq 6 -me_range 16 -g 60 -keyint_min 31 -sc_threshold 0 -mixed-refs 1 -rc-lookahead 60 -qcomp 0.50 -qmin 8 -qmax 51 -pix_fmt yuv420p -x264opts "fast-pskip=0:trellis=0:8x8dct=0:no-deblock:stitchable:vbv-maxrate=3000:vbv-bufsize=4000:interlaced=0" -acodec libvorbis -ab 64k -ac 2 "GCN_OUTPUT/%%~A_gcn.mkv"
echo  Converting video for GameCube...
)
PAUSE

:: This is the script I used to turn quality YT videos into GameCube compatible files.
:: It will read all .mp4 files on the current dir, change it to meet your needs.

:: It's NOT an ideal recipe (it's overkill for anime) but it will play fine on the GC.

:: The x264 settings are based on 2012 Elephants Dream encodes that may or may not have been used by the Wii's Netflix app back then.
:: In other words, the bitrate is so constrained that it's very fast.
:: The biggest difference is that there is no deblocking from the start, bitrate is greater, and the resolution is lower.

:: This recipe follows this pattern:
:: -g 60 (fps*2) (This is keyint)
:: -keyint_min 31 ((fps*2)+1)
:: -rc-lookahead 60 (fps*2)
:: -vb 2000k (This is bitrate)
:: vbv-maxrate=((bitrate*2)*0.75)
:: vbv-bufsize=(bitrate*2)

:: You don't have to follow this pattern to get good encodes, though.
:: And I've had success with increasing the bitrate up to 2500k.


:: CROPPING

:: By cropping 16:9 to 4:3 you get to use more bitrate on a cleaner image, and tends to look way better, always crop if you can.

:: crop=1440:ih:240:0 = crop center 1920x1080 16/9 = 1440x1080 4/3
:: crop=2880:ih:480:0 = same but with 4K
:: crop=960:ih:322:0 = same but with 1280x720


:: AUDIO

:: If your video comes from YT, it most likely has AAC audio, if it does, you can go ahead and adjust to use "-acodec copy" instead of libvorbis, to keep the original audio.

:: It's frustrating when some videos have a high dynamic range, or the volume is too low, you can add "-af dynaudnorm=f=150:b=1" to level out the sound to an extent.


:: 60 FPS

:: As you can tell by using 512x480, decoding x264 can be slow, so to play 60 fps videos without sacrificing the fluidity
:: you can use the interlace filter "-vf tinterlace=4" as well as enabling interlaced encoding by adding "interlaced=1" to -x264opts
:: All that matters is that the original video is 60 fps and that height is 480.


:: WHAT THE...?? WHY NOT USE A FASTER CODEC, LIKE XVID???
:: I'm used to using ffmpeg, and x264 can encode much faster and tends to be easier to work with overall.

:: WHAT ABOUT CRF?
:: CRF with such a constrained bitrate would be worse than 2-pass, I think.
:: If you break the limit, it would just be too slow.
