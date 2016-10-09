// Ruben Cuadra A01019102
// Data Structure
// ----------

#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "DoubleLinkedList.h"

static sf::Music *music;
void playSong(std::string song)
{
    music = new sf::Music;
    if (!music->openFromFile(song))
        throw 'e';
    //37 because songs are paths, songname starts at index 37
    std::cout << "Now Playing: " << song.substr(37)<< "\n";
    music->play();
}
void pauseSong(std::string song)
{
    if (music==nullptr)
        return;

    music->pause();
}
char userInterface()
{
    std::cout << "\nMenu options:" << std::endl;
    std::cout << "\ta. Play " << std::endl;
    std::cout << "\tb. Pause" << std::endl;
    std::cout << "\tc. Next" << std::endl;
    std::cout << "\td. Previous" << std::endl;
    std::cout << "\te. Print Playlist" << std::endl;
    std::cout << "\tf. Print Current" << std::endl;
    std::cout << "\tq. Exit" << std::endl;
    std::cout << "Your Choice: ";
    char choice;
    std::cin>>choice;
    return choice;
}

using namespace std;
void user_menu()
{
    DoubleLinkedList<string> playlist;
    short currentIndex = 0;
    string currentSong,temp;
    ifstream txtfile("/Users/Ruben/Documents/player/player/InATidalWaveOfMystery.txt");
    if (txtfile.is_open())
    {
        for (int i = 0; getline(txtfile, temp); ++i)
        {playlist.insertOrdered(temp);}
        txtfile.close();
    }else std::cout << "File could not be found" << std::endl;
    
    currentSong = playlist.getItemAt(currentIndex)->getData();
    bool exit = false;
    while (!exit)
    {
        switch (userInterface())
        {
            case 'a':
                playSong(currentSong);
                break;
            case 'b':
                pauseSong(currentSong);
                break;
            case 'c':
                currentIndex=currentIndex<playlist.getLength()?currentIndex+1:0;
                pauseSong(currentSong);
                currentSong = playlist.getItemAt(currentIndex)->getData();
                playSong(currentSong);
                break;
            case 'd':
                currentIndex=currentIndex>0?currentIndex-1:playlist.getLength()-1;
                pauseSong(currentSong);
                currentSong = playlist.getItemAt(currentIndex)->getData();
                playSong(currentSong);
                break;
            case 'e':
                std::cout << std::endl << "In A Tidal Wave Of Mystery:\n";
                playlist.printList();
                break;
            case 'f':
                std::cout <<"Now Playing: ";
                std::cout <<playlist.getItemAt(currentIndex)->getData().substr(40);
                std::cout<<" by Capital Cities\n";
                break;
            case 'q':
                std::cout << "Bye!" << std::endl;
                exit=true;
                break;
            default:
                std::cout << "Invalid option. Try again ..." << std::endl;
                break;
        }
    }
}

int main()
{
    std::cout << "Ruben Cuadra A01019102\n";
    user_menu();
    return 0;
}


