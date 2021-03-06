# DOOM-NUKEM CORONA EDITION
Codam Coding College final project


![Demo of doom-nukem-corona-edition](https://github.com/jdsmith022/doom_corona_edition/blob/master/git_assets/start-doom.gif)

## Description

Doom-Nukem is the final graphics branch product of the first part of the curriculum at Codam Coding College. My four teammates and myself wrote our project entirely from scratch and in C. As we started this project at the beginning of the COVID-19 pandemic, we made a creative decision to theme our game around COVID-19. 

We used SDL2, SDL2_mixer and SDL2_tff libraries to support our game, perfering to use SDL over miniLibX. As with previous projects from Codam, the goals of this project included: rigor, C, commonly used algorithms, information search, literature analysis, etc. However, as a graphic programming project, Doom-Nukem focus was to strengthen my teams knowledge in these particular field: windows, images, events, filling in forms, etc.

For full pdf of project requirements click [here](https://github.com/jdsmith022/doom_corona_edition/blob/master/git_assets/doom-nukem.en.pdf).

### Installation
From terminal, the program can be install with git clone with the project repository, followed by the name of the directory you wish to download the repository to.

Example
```
$ git clone git@github.com:jdsmith022/doom-nukem.git [directory-name]
```

### Dependencies
This program was written on LinuxOS and complies with a Makefile.

To install dependencies go to repo directory, run: 
```
bash install.bash
```
To uninstall dependencies go to repo directory, run:
```
bash uninstall.bash
```


### Usage
In terminal, go into the project directory. First install dependencies if you have not already. Run:
```
bash install.bash
```
This program uses a makefile to compile. To compile, run:
```
$ make
```

The executable made is doom-nukem. To being playing, run executable in terminal: 
```
$ ./doom-nukem
```
To delete all object files from directory, run:
```
$ make clean
```
To delete executable and all object files from directory, run:
```
$ make fclean
```


### Gameplay

![Demo of doom-nukem-corona-edition](https://github.com/jdsmith022/doom_corona_edition/blob/master/git_assets/scissor-lift-doom.gif)

The objective of the game is to get all the items on your grocery list and checkout before your time runs out and without catching the Corona virus. To combat the virus, you will have sanitizing spray that you can fill up as well as healthpacks and facemaks to collect through the grocery store to increase your health level. But make sure you keep your 1.5 meter distance from shoppers!

### Settings
Settings and instructions can be found and some changed in the Settings menu on the home screen.

![Demo of doom-nukem-corona-edition](https://github.com/jdsmith022/doom_corona_edition/blob/master/git_assets/settings-doom.gif)

### Game Editor
In the game editor, a player may select the textures to go on the pre-made layout of the grocery store. The player may also add shoppers, viruses, and healthpacks to the game to increase difficulty.


![Demo of doom-nukem-corona-edition](https://github.com/jdsmith022/doom_corona_edition/blob/master/git_assets/game-editor.gif)

### Collaborator
This project was a group effort with:
[Malou](https://github.com/mminkjan)
[Roos](https://github.com/RoosCocolien)
[Elkan](https://github.com/elkanfrank)
[Marin]
