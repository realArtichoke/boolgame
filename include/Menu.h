#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;
Music music;
float musicVolume = 50;
int marginTop = 30;
void credits_menu(RenderWindow& win)
{
    Texture Menu;
    Menu.loadFromFile("source/help.jpg");
    Sprite menu(Menu);
    Vector2f coord = win.mapPixelToCoords({0, 0});

    menu.setPosition(coord);
    menu.setPosition(coord);
    if(win.hasFocus())
    while(win.isOpen())
    {
        Vector2f c = win.mapPixelToCoords(Mouse::getPosition(win));
        Event event;

        while(win.pollEvent(event))
        {
            if(event.type == Event::Closed) win.close();
            if(event.type == Event::KeyPressed) if(event.key.code == Keyboard::Escape){return;}
        }


        win.clear();
        win.draw(menu);
        win.display();
    }
}
void options_menu(RenderWindow& win)
{
    Text volum;
    Font font;
    font.loadFromFile("source/font.otf");
    volum.setFont(font);
    volum.setColor(Color(201, 46, 46));
    volum.setString("������ ");
    volum.setPosition(100, 200);


    Texture Menu, Vol;
    Menu.loadFromFile("source/menu.jpeg");
    Vol.loadFromFile("source/Vol.png");
    Sprite menu(Menu), volu(Vol);
    volu.setPosition(300, 200);
    volu.setTextureRect(IntRect(0, 0, music.getVolume()/100 * 250, 32));
    Vector2f coord = win.mapPixelToCoords({0, 0});

    menu.setPosition(coord);

    while(win.isOpen())
    {
        Vector2f c = win.mapPixelToCoords(Mouse::getPosition(win));
        Event event;
        bool setVolu;
        while(win.pollEvent(event))
        {
            if(event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left && volu.getGlobalBounds().contains(c.x, c.y)) setVolu = true;
            else if(event.type == Event::MouseButtonReleased) setVolu = false;
            if(Mouse::isButtonPressed(Mouse::Left) && setVolu)
            {
                if(c.x < volu.getGlobalBounds().left + 253 && c.x > volu.getGlobalBounds().left + 10) volu.setTextureRect(IntRect(0, 0, c.x-volu.getGlobalBounds().left, 32));
                musicVolume = volu.getTextureRect().width / 2.4f;
                music.setVolume(musicVolume);
            }
            if(event.type == Event::Closed) win.close();
            if(event.type == Event::KeyPressed) if(event.key.code == Keyboard::Escape){return;}
        }

        win.clear();
        win.draw(menu);
        win.draw(volu);
        win.draw(volum);
        win.display();
    }
}
void game_menu(RenderWindow &win, vector <Sprite> spriteVec, Level &_map)
{
    View view;
    view.setSize(win.getSize().x, win.getSize().y);
    Texture Menu, PlayMenu, OptionsMenu, CreditsMenu, EndMenu, Volume;
    Menu.loadFromFile("source/menu.jpeg");
    PlayMenu.loadFromFile("source/cont.png");
    OptionsMenu.loadFromFile("source/setting.png");
    CreditsMenu.loadFromFile("source/help.png");
    EndMenu.loadFromFile("source/end.png");
    Volume.loadFromFile("source/volume.png");
    Sprite menu(Menu), playMenu(PlayMenu), optionsMenu(OptionsMenu), creditsMenu(CreditsMenu), endMenu(EndMenu), volume(Volume);

    Vector2f coord = win.mapPixelToCoords({0, 0});
    view.setCenter(coord.x + win.getSize().x/2, coord.y + win.getSize().y/2);
    menu.setPosition(coord.x, coord.y);

    menu.setPosition(coord.x, coord.y);
    volume.setTextureRect(IntRect(0, 0, 32, 32));
    volume.setPosition(win.getSize().x - 42, win.getSize().y - 42);
    playMenu.setPosition(coord.x + 176, coord.y + 39);
    playMenu.setTextureRect(IntRect(0, 0, 288, 81));
    optionsMenu.setPosition(coord.x + 176, coord.y + marginTop+81+marginTop);
    optionsMenu.setTextureRect(IntRect(0, 0, 288, 81));
    creditsMenu.setPosition(coord.x + 176, coord.y + marginTop+81+marginTop+81+marginTop);
    creditsMenu.setTextureRect(IntRect(0, 0, 288, 81));
    endMenu.setPosition(coord.x + 176, coord.y + marginTop+81+marginTop+81+marginTop+81+marginTop);
    endMenu.setTextureRect(IntRect(0, 0, 288, 81));

    SoundBuffer h, c;
    h.loadFromFile("source/Mhover.wav");
    c.loadFromFile("source/Mclick.wav");
    Sound mhover(h);
    Sound mclick(c);

    bool goSound = false;
    bool music_is_play;
    if(music.getVolume() != 0) music_is_play = true;
    else music_is_play = false;
    static bool in_cont, in_opt, in_cred, in_end;
    float tempTime = 0;
    Clock clock;
    while(win.isOpen())
    {


        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        Vector2f c = win.mapPixelToCoords(Mouse::getPosition(win));
        Event event;
        system("cls");
        cout << c.x << ":"<<c.y << endl << coord.x << ":" << coord.y;

        while(win.pollEvent(event))
        {
            if(event.type == Event::MouseButtonReleased) if(volume.getGlobalBounds().contains(c.x, c.y)) music_is_play = !music_is_play;
            if(event.type == Event::Closed) win.close();
            if(event.type == Event::MouseButtonReleased && in_opt == true) { mclick.play(); options_menu(win); mclick.play();}
            if(event.type == Event::MouseButtonReleased && in_cred == true) { mclick.play(); credits_menu(win); mclick.play();}
            if(event.type == Event::KeyPressed) if(event.key.code == Keyboard::Escape){in_cont = false;return;}
            if(event.type == Event::MouseButtonPressed) if(playMenu.getGlobalBounds().contains(c.x, c.y)){ in_cont = true;}
            if(event.type == Event::MouseButtonPressed) if(optionsMenu.getGlobalBounds().contains(c.x, c.y)) { in_opt = true; }
            if(event.type == Event::MouseButtonPressed) if(creditsMenu.getGlobalBounds().contains(c.x, c.y)) { in_cred = true;}
            if(event.type == Event::MouseButtonPressed) if(endMenu.getGlobalBounds().contains(c.x, c.y)) { in_end = true;}
            if(event.type == Event::MouseButtonReleased && in_cont){ while(mclick.getPlayingOffset().asMicroseconds() > 0); in_cont = false;return; }
            if(event.type == Event::MouseButtonReleased){ in_cont = in_opt = in_cred = false; }
            if(event.type == Event::MouseButtonReleased && in_end) win.close();
        }

        if(music_is_play)
        {
            music.setVolume(musicVolume);
            volume.setTextureRect(IntRect(0, 0, 32, 32));
        }
        else
        {
            music.setVolume(0);
            volume.setTextureRect(IntRect(32, 0, 32, 32));
        }
        if(volume.getGlobalBounds().contains(c.x, c.y))
        {
            if(music_is_play) volume.setTextureRect(IntRect(64, 0, 32, 32));
            else volume.setTextureRect(IntRect(96, 0, 32, 32));
        }


        bool xplay, xopt, xcred, xend;
        if(playMenu.getGlobalBounds().contains(c.x, c.y))
        {
            playMenu.setTextureRect(IntRect(288, 0, 288, 81));
            if(!xplay) mhover.play();
            xplay = true;
        }
        else{ playMenu.setTextureRect(IntRect(0, 0, 288, 81)) ;xplay = false;}
        if(optionsMenu.getGlobalBounds().contains(c.x, c.y))
        {
            if(!xopt) mhover.play();
            xopt = true;
            optionsMenu.setTextureRect(IntRect(288, 0, 288, 81));
        }
        else {optionsMenu.setTextureRect(IntRect(0, 0, 288, 81));xopt = false;}
        if(creditsMenu.getGlobalBounds().contains(c.x, c.y))
        {
            if(!xcred) mhover.play();
            xcred = true;
            creditsMenu.setTextureRect(IntRect(288, 0, 288, 81));
        }
        else {creditsMenu.setTextureRect(IntRect(0, 0, 288, 81));xcred = false;}
        if(endMenu.getGlobalBounds().contains(c.x, c.y))
        {
            if(!xend) mhover.play();
            xend = true;
            endMenu.setTextureRect(IntRect(288, 0, 288, 81));
        }
        else {endMenu.setTextureRect(IntRect(0, 0, 288, 81));xend = false;}

        if(in_cont) playMenu.setTextureRect(IntRect(288*2, 0, 288, 81));
        if(in_opt) optionsMenu.setTextureRect(IntRect(288*2, 0, 288, 81));
        if(in_cred) creditsMenu.setTextureRect(IntRect(288*2, 0, 288, 81));
        if(in_end) endMenu.setTextureRect(IntRect(288*2, 0, 288, 81));

        win.clear();

        //win.draw(menu);
        _map.Draw(win);
        win.setView(view);
        for(int i = 0; i < spriteVec.size(); i++)
            win.draw(spriteVec[i]);
        win.draw(menu);
        win.draw(playMenu);
        win.draw(optionsMenu);
        win.draw(creditsMenu);
        win.draw(endMenu);
        win.draw(volume);
        win.display();
    }
}
void loading(RenderWindow &win, Sprite* spriteArr, int len, void play(RenderWindow& win))
{
    bool downLight = true, indicator = false;
    float tempTime = 0, indTime = 0;
    RectangleShape dark({1000, 1000});
    Texture Load;
    Load.loadFromFile("source/loading.png");
    Sprite load(Load);
    load.setPosition(win.getSize().x/2-load.getTextureRect().width/2 + 30, win.getSize().y/2-load.getTextureRect().height/2);
    dark.setFillColor(Color(0, 0, 0, 0));
    Clock clock;
    while(win.isOpen())
    {
        if(!downLight && !indicator){ play(win); }
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 100;
        Event event;
        while(win.pollEvent(event))
        {
            if(event.type == Event::Closed) win.close();
        }
        if(downLight)
        {
            tempTime+=time;
            float opacity = tempTime*170/10000;
            if(opacity > 255) opacity = 255;
            dark.setFillColor(Color(0, 0, 0, opacity));
            if(tempTime > 15000){ downLight = false; indicator = true;}
        }
        win.clear();
        if(downLight)
        {
            for(int i = 0; i < len; i++) win.draw(spriteArr[i]);
            win.draw(dark);
        }
        if(indicator)
        {
            indTime+=time;
            if(indTime > 11000){ indTime-=11000; indicator = false; }
            load.setTextureRect(IntRect(30, 0, 26*(int)(indTime/1000), 81));
            win.draw(load);
        }
        win.display();
    }
}
void main_menu(RenderWindow &win, void play(RenderWindow& win))
{
    Texture Menu, PlayMenu, OptionsMenu, CreditsMenu, EndMenu, Volume;
    Menu.loadFromFile("source/menu.jpeg");
    PlayMenu.loadFromFile("source/play.png");
    OptionsMenu.loadFromFile("source/setting.png");
    CreditsMenu.loadFromFile("source/help.png");
    EndMenu.loadFromFile("source/end.png");
    Volume.loadFromFile("source/volume.png");
    Sprite menu(Menu), playMenu(PlayMenu), optionsMenu(OptionsMenu), creditsMenu(CreditsMenu), endMenu(EndMenu), volume(Volume);
    volume.setPosition(640 - 42, 480 - 42);
    menu.setPosition(0, 0);
    volume.setTextureRect(IntRect(0, 0, 32, 32));
    playMenu.setPosition(176, 39);
    playMenu.setTextureRect(IntRect(0, 0, 288, 81));
    optionsMenu.setPosition(176, marginTop+81+marginTop);
    optionsMenu.setTextureRect(IntRect(0, 0, 288, 81));
    creditsMenu.setPosition(176, marginTop+81+marginTop+81+marginTop);
    creditsMenu.setTextureRect(IntRect(0, 0, 288, 81));
    endMenu.setPosition(176, marginTop+81+marginTop+81+marginTop+81+marginTop);
    endMenu.setTextureRect(IntRect(0, 0, 288, 81));
    static float time_to_load;
    static bool in_play, in_opt, in_cred, in_end;
    bool music_is_play = true;
    SoundBuffer h, c;
    h.loadFromFile("source/Mhover.wav");
    c.loadFromFile("source/Mclick.wav");
    Sound mhover(h);
    Sound mclick(c);

    while(win.isOpen())
    {
        Sprite spriteArr[] = {menu, playMenu, optionsMenu, creditsMenu, endMenu, volume};
        float time = Clock().getElapsedTime().asMicroseconds();
        Vector2f c = win.mapPixelToCoords(Mouse::getPosition(win));
        Event event;
        while(win.pollEvent(event))
        {
            if(event.type == Event::MouseButtonReleased) if(volume.getGlobalBounds().contains(c.x, c.y)) music_is_play = !music_is_play;
            if(event.type == Event::Closed) win.close();
            if(event.type == Event::MouseButtonReleased && in_opt == true) { mclick.play(); options_menu(win);}
            if(event.type == Event::MouseButtonReleased && in_cred == true) { mclick.play(); credits_menu(win);}
            if(event.type == Event::MouseButtonPressed) if(playMenu.getGlobalBounds().contains(c.x, c.y)) in_play = true;
            if(event.type == Event::MouseButtonPressed) if(optionsMenu.getGlobalBounds().contains(c.x, c.y)) in_opt = true;
            if(event.type == Event::MouseButtonPressed) if(creditsMenu.getGlobalBounds().contains(c.x, c.y)) in_cred = true;
            if(event.type == Event::MouseButtonPressed) if(endMenu.getGlobalBounds().contains(c.x, c.y)) in_end = true;
            if(event.type == Event::MouseButtonReleased && in_play){mclick.play();loading(win, spriteArr, 6, play);}
            if(event.type == Event::MouseButtonReleased){ in_play = in_opt = in_cred = false; }
            if(event.type == Event::MouseButtonReleased && in_end) win.close();

        }

        if(music_is_play)
        {
            music.setVolume(musicVolume);
            volume.setTextureRect(IntRect(0, 0, 32, 32));
        }
        else
        {
            music.setVolume(0);
            volume.setTextureRect(IntRect(32, 0, 32, 32));
        }
        if(volume.getGlobalBounds().contains(c.x, c.y))
        {
            if(music_is_play) volume.setTextureRect(IntRect(64, 0, 32, 32));
            else volume.setTextureRect(IntRect(96, 0, 32, 32));
        }

        bool xplay, xopt, xcred, xend;
        if(playMenu.getGlobalBounds().contains(c.x, c.y))
        {
            playMenu.setTextureRect(IntRect(288, 0, 288, 81));
            if(!xplay) mhover.play();
            xplay = true;
        }
        else{ playMenu.setTextureRect(IntRect(0, 0, 288, 81)); xplay = false;}
        if(optionsMenu.getGlobalBounds().contains(c.x, c.y))
        {
            optionsMenu.setTextureRect(IntRect(288, 0, 288, 81));
            if(!xopt) mhover.play();
            xopt = true;
        }
        else{ optionsMenu.setTextureRect(IntRect(0, 0, 288, 81)); xopt = false;}
        if(creditsMenu.getGlobalBounds().contains(c.x, c.y))
        {
            creditsMenu.setTextureRect(IntRect(288, 0, 288, 81));
            if(!xcred) mhover.play();
            xcred = true;
        }
        else{ creditsMenu.setTextureRect(IntRect(0, 0, 288, 81)); xcred = false;}
        if(endMenu.getGlobalBounds().contains(c.x, c.y))
        {
            endMenu.setTextureRect(IntRect(288, 0, 288, 81));
            if(!xend) mhover.play();
            xend = true;
        }
        else{ endMenu.setTextureRect(IntRect(0, 0, 288, 81)); xend = false;}

        if(in_play) playMenu.setTextureRect(IntRect(288*2, 0, 288, 81));
        if(in_opt) optionsMenu.setTextureRect(IntRect(288*2, 0, 288, 81));
        if(in_cred) creditsMenu.setTextureRect(IntRect(288*2, 0, 288, 81));
         if(in_end) endMenu.setTextureRect(IntRect(288*2, 0, 288, 81));

        win.clear();
        win.draw(menu);
        win.draw(playMenu);
        win.draw(optionsMenu);
        win.draw(creditsMenu);
        win.draw(endMenu);
        win.draw(volume);
        win.display();
    }
}
