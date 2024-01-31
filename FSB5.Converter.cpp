#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <windows.h>
#include <fsbank.h>
#include <fsbank_errors.h>
#include <filesystem>

using namespace std;

string FSBankResultToString(FSBANK_RESULT result)
{
    switch (result)
    {
    case FSBANK_OK:
        return "FSBANK_OK";
    case FSBANK_ERR_CACHE_CHUNKNOTFOUND:
        return "FSBANK_ERR_CACHE_CHUNKNOTFOUND";
    case FSBANK_ERR_CANCELLED:
        return "FSBANK_ERR_CANCELLED";
    case FSBANK_ERR_CANNOT_CONTINUE:
        return "FSBANK_ERR_CANNOT_CONTINUE";
    case FSBANK_ERR_ENCODER:
        return "FSBANK_ERR_ENCODER";
    case FSBANK_ERR_ENCODER_INIT:
        return "FSBANK_ERR_ENCODER_INIT";
    case FSBANK_ERR_ENCODER_NOTSUPPORTED:
        return "FSBANK_ERR_ENCODER_NOTSUPPORTED";
    case FSBANK_ERR_FILE_OS:
        return "FSBANK_ERR_FILE_OS";
    case FSBANK_ERR_FILE_NOTFOUND:
        return "FSBANK_ERR_FILE_NOTFOUND";
    case FSBANK_ERR_FMOD:
        return "FSBANK_ERR_FMOD";
    case FSBANK_ERR_INITIALIZED:
        return "FSBANK_ERR_INITIALIZED";
    case FSBANK_ERR_INVALID_FORMAT:
        return "FSBANK_ERR_INVALID_FORMAT";
    case FSBANK_ERR_INVALID_PARAM:
        return "FSBANK_ERR_INVALID_PARAM";
    case FSBANK_ERR_MEMORY:
        return "FSBANK_ERR_MEMORY";
    case FSBANK_ERR_UNINITIALIZED:
        return "FSBANK_ERR_UNINITIALIZED";
    case FSBANK_ERR_WRITER_FORMAT:
        return "FSBANK_ERR_WRITER_FORMAT";
    case FSBANK_WARN_CANNOTLOOP:
        return "FSBANK_WARN_CANNOTLOOP";
    case FSBANK_WARN_IGNORED_FILTERHIGHFREQ:
        return "FSBANK_WARN_IGNORED_FILTERHIGHFREQ";
    case FSBANK_WARN_IGNORED_DISABLESEEKING:
        return "FSBANK_WARN_IGNORED_DISABLESEEKING";
    case FSBANK_WARN_FORCED_DONTWRITENAMES:
        return "FSBANK_WARN_FORCED_DONTWRITENAMES";
    case FSBANK_ERR_ENCODER_FILE_NOTFOUND:
        return "FSBANK_ERR_ENCODER_FILE_NOTFOUND";
    case FSBANK_ERR_ENCODER_FILE_BAD:
        return "FSBANK_ERR_ENCODER_FILE_BAD";
    default:
        return "Unknown Result";
    }
}

FSBANK_FORMAT GetFormatEnum(string format)
{
    if (format == "PCM")
    {
        return FSBANK_FORMAT_PCM;
    }
    else if (format == "XMA")
    {
        return FSBANK_FORMAT_XMA;
    }
    else if (format == "AT9")
    {
        return FSBANK_FORMAT_AT9;
    }
    else if (format == "Vorbis")
    {
        return FSBANK_FORMAT_VORBIS;
    }
    else if (format == "FADPCM")
    {
        return FSBANK_FORMAT_FADPCM;
    }
    else if (format == "OPUS")
    {
        return FSBANK_FORMAT_OPUS;
    }
    else if (format == "MAX")
    {
        return FSBANK_FORMAT_MAX;
    }
    else
    {
        cerr << "Incorrect compression format." << endl;
        cin.get();
        exit(1);
    }
}

string GetFileNameWithoutExtension(const string& filePath)
{
    filesystem::path path(filePath);
    return path.stem().string();
}

void PrintHelp()
{
    cout << "FSB5 converter by JunkBeat" << endl;
    cout << "" << endl;
    cout << "Usage: FSB5.Converter.exe -a audio_path" << endl;
    cout << "" << endl;
    cout << "Optional arguments:" << endl;
    cout << "   -f compression_format   Target format (default = Vorbis)" << endl;
    cout << "                           Available formats:" << endl;
    cout << "                           PCM, XMA, AT9, Vorbis, FADPCM, OPUS, MAX" << endl;
    cout << "   -n output_file_name     Custom filename" << endl;
    cout << "   -o output_folder_path   (default = current folder)" << endl;
    cout << "   -q quality              Value within 0-100 (default = 0, normal quality)" << endl;
    cout << "   -b thread_count         Set this to your number of CPU 'cores' for best performance (default = 4)" << endl;
    cout << "   -c cache_folder_path    (default = cache folder in the current directory)" << endl;
    cout << "" << endl;
    cout << "   -e: close the program immediately after completion" << endl;
    cout << "   -d: print debug information" << endl;
    cout << "" << endl;
    cout << "Press Enter to continue..." << endl;
}

int main(int argc, char* argv[])
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    string cachePath = "cache";
    string outputPath = "";
    string audioPath;
    string audioName;
    string format = "Vorbis";
    int quality = 0;
    int threadCount = 4;
    bool exitImmediately = false;
    bool debug = false;

    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            switch (argv[i][1])
            {
            case 'c':
                if (i + 1 < argc)
                {
                    cachePath = argv[i + 1];
                    ++i;  // Move to the next argument
                }
                break;
            case 'a':
                if (i + 1 < argc)
                {
                    audioPath = argv[i + 1];
                    ++i;  // Move to the next argument
                }
                break;
            case 'q':
                if (i + 1 < argc)
                {
                    quality = atoi(argv[i + 1]);
                    ++i;  // Move to the next argument
                }
                break;
            case 'b':
                if (i + 1 < argc)
                {
                    threadCount = atoi(argv[i + 1]);
                    ++i;  // Move to the next argument
                }
                break;
            case 'f':
                if (i + 1 < argc)
                {
                    format = argv[i + 1];
                    ++i;  // Move to the next argument
                }
                break;
            case 'n':
                if (i + 1 < argc)
                {
                    audioName = argv[i + 1];
                    ++i;  // Move to the next argument
                }
                break;
            case 'o':
                if (i + 1 < argc)
                {
                    outputPath = argv[i + 1];
                    ++i;  // Move to the next argument
                }
                break;
            case 'e':
                exitImmediately = true;
                break;
            case 'd':
                debug = true;
                break;
            default:
                PrintHelp();
                cin.get();
                return 1;
            }
        }
    }

    if (audioPath.empty())
    {
        PrintHelp();
        cin.get();
        return 1;
    }

    const char* cachePathC = cachePath.c_str();
    const char* const audioPathC = audioPath.c_str();
    FSBANK_FORMAT formatEnum = GetFormatEnum(format);
    if (audioName.empty())
    {
        audioName = GetFileNameWithoutExtension(audioPath);
    }

    FSBANK_RESULT result = FSBank_Init(FSBANK_FSBVERSION_FSB5, FSBANK_INIT_NORMAL, threadCount, cachePathC);
    cout << "FSBank Init:-  ";
    cout << FSBankResultToString(result) << endl;

    FSBANK_SUBSOUND subsound = { NULL };
    subsound.fileNames = &audioPathC;
    subsound.overrideFlags = FSBANK_BUILD_DISABLESYNCPOINTS;
    subsound.overrideQuality = quality;
    subsound.desiredSampleRate = 0;
    subsound.numFiles = 1;
    const FSBANK_SUBSOUND* newSubsound = &subsound;
    cout << "Subsound assigned  " << endl;

    string completePath = (filesystem::path(outputPath) / (audioName + ".fsb")).string();
    result = FSBank_Build(newSubsound, 1, formatEnum, FSBANK_BUILD_DEFAULT | FSBANK_BUILD_DONTLOOP, quality, NULL, completePath.c_str());
    cout << "FSBank Build:-     ";
    cout << FSBankResultToString(result) << endl;

    if (debug)
    {
        cout << "" << endl;
        cout << "Debug information:" << endl;
        cout << "- Cache path: " << cachePath << endl;
        cout << "- Input audio path: " << audioPath << endl;
        cout << "- Output audio name: " << audioName << endl;
        cout << "- Quality: " << quality << endl;
        cout << "- Compression format: " << format << endl;
        cout << "- Compression format enum: " << formatEnum << endl;
        cout << "- Output path: " << outputPath << endl;
        cout << "- Complete output path: " << completePath << endl;
        cout << "" << endl;
    }


    if (!exitImmediately)
    {
        cout << "Press Enter to continue...";
        cin.get();
    }
    return 0;
}