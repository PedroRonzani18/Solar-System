#include "../Header/MusicManager.h"
#include <iostream>

// Função de setup das configurações de áudio
void MusicManager::configureMusic()
{
    // Cria um canal de música
    Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);

    // Adiciona umma música ao vector de Mix_Music*
    addMusic(Mix_LoadMUS("Assets/audio/background1.mp3"));

    // Inicia a reproducao da musica
    Mix_PlayMusic(getMusic(0),-1);

    // Define o volume inicial como 0
    Mix_VolumeMusic(0);
}

// Função que determina o volume da música baseando na proximidade da camera com Marte
// Quanto mais perto, maior o volume
void MusicManager::marsMusic(double distance)
{
    if(6 < distance)
        Mix_VolumeMusic(0);

    else if(2.5 <= distance && distance <= 6)
        Mix_VolumeMusic(-36.5 * distance + 219);
    
    else if(distance < 2.5)
        Mix_VolumeMusic(128);
}
