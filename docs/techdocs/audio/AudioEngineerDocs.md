# Audio Engineering for Citrus 64

## Performance is Critical

Sound in modern games tends to be a very low footprint thing. Back in the era of the N64 however sound was an expected expensive luxury performance wise. As an audio engineer for the system it is your responsibility to optimize your music and sound effects to take up the least amount of space possible at what you deem an aceptable quality.

## Sound Effects

### Process
1. Get a sound effect from a library or record one yourself
2. Edit it in your audio workstation of choice
3. Export it in your target Hz (see below) to the asset folder
4. Listen to the exported clip in a media player
5. Tweak the sound effect and export settings until the sound effect sounds acceptable (by retro game standards) and is under budget.
6. Playtest and listen to it in-game using the [asset tester]()

### Optimization
Sound effects are comprised of waveforms (graphs) that are made up of many many points of data called samples (points on a graph, not to be confused with sound-clips or instruments). The more points there are on a graph the bigger the memory size. Without care and consideration a random sound effect can easily take up extreme amounts of cartridge space. 

#### Tips
* Sound effects should be under 2 seconds bursts
* Trim empty space from beginning to end
* Keep your file size under 32kb
* 8000Hz or lower is an ideal range (go above only if the file is short enough or quality is unnacceptable and alternative low-frequency friendly sounds are not ideal)
* Use [scripts](#sound-scripting) rather than long sound files

## Music

High quality modern music filescan take up a lot of space and processing power compared to what the N64 can handle. A modern song file can take over 5 megabytes... an entry level cartridge can hold 4 megabytes. Playing a modern format can take almost half of of the console's resources with optimization... So unless your game is only music a smarter approach should be taken.

Sequenced music is a much more retro-friendly approach to music. Only small bits of waveform data are saved for each instrument and the file contains instructions on how to play it back. The SDK provides support for playing back Fast Tracker 2's XM format.

### OpenMPT

Modern DAWs are not optimal for old-school sequenced music since 99% of their features cant be used. Software called **trackers** are designed to make sequenced music. Trackers are easy to get into compared to DAWs since they are basically just note spread-sheets with a sample editor. An excellent free beginner friendly sequenced music editor is **OpenMPT** which you can download [here](https://openmpt.org/).

Remember to create your music in the XM format and follow the optimization guide.

#### Resources
* [OpenMPT Documentation](https://wiki.openmpt.org/Main_Page)
* [Quick Start Tutorial](https://www.youtube.com/watch?v=6IxSL1zrLDo)

### Optimization
* Plugins are not supported in the engine (for obvious reasons) if you need special effects bake them into the sample using external software.
* A maximum of 12 channels are allowed in the engine
* Use the least amount of channels you can. 4 and under is ideal, 8 and under if you are going really hard. (treat each channels like a musician who can change instruments)
* Wherever possible try small looping hand drawn samples for simple notes or techno instruments
* For optimizing samples follow the [sound effect optimization guide](#sound-effects) (scripting unsupported)
* Samples will be embedded in the XM file and wav files don't need to be added to the asset folder

## Sound Scripting

Citrus 64 lets audio designers create JSON files which describe audio events or ambient soundscapes and generate the code to play it behind the scenes independent from programmer intervention.

### Events
(todo)

### Ambient
(todo)

## Mixing

## Asset Settings
(todo)