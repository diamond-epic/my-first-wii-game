[Click here to skip straight to Building](https://github.com/diamond-epic/my-first-wii-game/tree/main?tab=readme-ov-file#building)

# My First Wii Game!!!
Recently, I've been into modding my video game consoles. First I modded my **3DS**, then my **DSi**, and then my **Wii!** Of course, I had fun playing the cool homebrew games, but I also wanted to make some of my own!

It has been quite a struggle... I found initial success in using a library called **WiiLÖVE** because it used Lua which is a programming language I'm already familiar with as I have been a **Roblox** developer for 9 years. Unfortunately, I couldn't quite get Wiimote inputs to work properly.

So... I had to switch to a different library called **GRRLIB**. Something I should mention is that I'm a **Mac** user. However, GRRLIB was for **Windows** (and **Linux**, I guess). So for a while, I had to use my **Macbook** which had **UTM** (a **virtual machine** that can emulate Windows) on it. I couldn't get UTM on my iMac because it's, like, _really old_. UTM was for **ARM** CPUs and my Mid-2010 iMac had an **Intel** CPU.

Another problem was that GRRLIB used **C**, which is a programming language that I've NEVER used before. I have made games in **Unity** which uses **C#**, so I thought that they would be similar enough. And to an extent, I was right! I found that I was able to implement a lot of my knowledge from C# into C. I'm really grateful for the example builds that are provided with the GRRLIB download because I was able to learn how to do things like **rendering shapes** and **Wiimote inputs** from them! There was also some documentation that came with the download, which was also pretty helpful. I couldn't manage to render **.ttf** files for some reason, but that could be because I had to modify the **make** file, which is something I had to do quite a bit later on.

Another struggle point for me was **implementing audio**. There were some examples that came with the installation of **devkitPro**. I could build the **.mp3** one, but when I tried to implement it in my project, it didn't work for some reason, even when I edited the make file. I couldn't build the **.ogg** example because I had to install some libraries that didn't come with devkitPro (**ppc-libogg** & **ppc-libvorbisidec**) which I couldn't figure out how to do on Windows. The only audio example that I was able to implement into my project was the **.mod** example. What's .mod, you might be asking? Oh yeah, it's just a ***VERY INCOMPATIBLE MIDI AUDIO FORMAT FROM 1987.*** There are virtually *ZERO* ways to convert most widely known audio formats to .mod. The only program I found that was able to export .mod files was **OpenMPT**. So... I wasn't very excited to face the harsh reality that I would have to make EVERY sound in an incompatible MIDI format using a program that I had NO IDEA how to use. Luckily, I didn't have to face that reality for long...

Today (July 26th, 2024), I decided to figure out how to get **GRRLIB** installed on **my iMac**. Yes, I know I said that it was for **Windows** (and **Linux**) only. HOWEVER... I figured something out. When I ran the "make clean all install" command in the GRRLIB folder, it did manage to make all the files, but it couldn't put them in the correct directories. So, I did it myself. I compared my Windows directories to my Mac directories to see where I had to put the GRRLIB and pngu files (In case you were wondering, grrlib.h and the grrlib folder go in opt/devkitPro/portlibs/wii/include, libgrrlib.a goes in opt/devkitPro/portlibs/wii/lib, pngu.h goes in opt/devkitPro/portlibs/ppc/include, and libpngu.a goes in opt/devkitPro/portlibs/ppc/lib). I know this seems very simple, but you have to understand that there were *ZERO* tutorials about this. I had to figure it all out on my own, and considering how I don't usually succeed at these types of things, I was very proud of myself! A nice cherry on top was that I was finally able to install the libraries needed to build that .ogg example project. And after modifying the make file, I managed to implement the .ogg libraries into my own project. A caveat of switching to Mac was that when I tested the .dol files using **Dolphin**, the sound didn't work, but when I tested it on my actual Wii, the sound did work. But that didn't really matter because testing it on my Wii was easier now. When I was using the laptop, I had to transfer the files from there to my computer using a USB stick, and then I used my computer to put the files from my USB stick onto my SD card. Now that the files are already on my computer, I can just put the files directly onto my SD card!

I know that was a lot to read, but I've just been really excited about all of this! As someone who doesn't usually go too far with these types of things, I've surprised myself quite a bit! Once again, there were very few tutorials on how to do **ANY** of this. So other than [this fella](https://www.youtube.com/@BackSoon...) who made [a couple videos](https://www.youtube.com/watch?v=noxGGdxHbDY&list=PL_CdIPK7HDFVtPA4cjuTMBzyi33rOrqPP) about making Wii homebrew, I was on my own. I have even more respect for the homebrew developers out there than I did before I embarked on this journey. That's not to say my journey isn't over yet, but it has been quite a wild ride! If reading this has inspired you to start developing your own homebrew for the Wii, then that's great! I'll probably put out a tutorial on how I did all of this stuff in the future.

7/27/24 (July 27th, 2024) - I struggled on rendering images that didn't have 640x480 dimensions. After around an hour of trial and error, I found that any images with dimensions that are divisible by 4 would render.

## i wanna play
If you have a modded Wii, all you need to do is download "maze game.zip", extract it, and put the "maze game" folder into your apps folder. I've tested this game on Dolphin, but I am not sure if the audio works with it.

## Building
I'm assuming you already have devkitPro installed on your computer. If you don't, then you won't be able to build the game. To build this game from source, you'll need to install ppc-libogg and ppc-libvorbisidec. For Mac (and Linux I think?) just enter "sudo dkp-pacman -S ppc-libvorbisidec" in Terminal and go through the installation process. Then enter "cd ../maze_game_FINAL" (the .. is just a placeholder for wherever the file is stored in) and then "make". It should spit out a build folder, a .elf file, and a .dol file. I'm not sure how to install the ogg libraries on Windows, but try "pacman -S ppc-libvorbisidec" or "pacman --sync --needed --noconfirm ppc-libvorbisidec" or smth idk. Maybe I'll include a .zip file that already has the game built at some point in development, but it'll certainly be there when the game's done.
