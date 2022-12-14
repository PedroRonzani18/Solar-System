#ifndef _MUSICMANAGER_H
#define _MUSICMANAGER_H

// STL
#include <vector>

// SDL
#include <SDL2/SDL_mixer.h>

class MusicManager
{
    private:
        std::vector<Mix_Music*> musics;

    public:
        MusicManager(){musics.resize(0);}
        void addMusic(Mix_Music* music){musics.push_back(music);}
        std::vector<Mix_Music*> getMusics(){return this->musics;}
        Mix_Music* getMusic(int i){return this->musics[i];}

        void configureMusic();
        void marsMusic(double distance);
};

#endif