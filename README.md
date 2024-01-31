# FSB5.Converter
C++ program that allow you to easily generate fsb5 audio using FMOD FSBank API

This program is based on [FSBank5.Net](https://github.com/CreatorsOfficial/FSBank5.Net)

```
Usage: FSB5.Converter.exe -a audio_path

Optional arguments:
   -f compression_format   Target format (default = Vorbis)
                           Available formats:
                           PCM, XMA, AT9, Vorbis, FADPCM, OPUS, MAX
   -n output_file_name     Custom filename
   -o output_folder_path   (default = current folder)
   -q quality              Value within 0-100 (default = 0, normal quality)
   -b thread_count         Set this to your number of CPU 'cores' for best performance (default = 4)
   -c cache_folder_path    (default = cache folder in the current directory)

   -e: close the program immediately after completion
   -d: print debug information
```
