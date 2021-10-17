#include "Player.h"
using namespace sf;

int main()
{
    TextureHolder holder;

    enum class State // All State of the game
    {
        PAUSED, LEVELING_UP, GAME_OVER, PLAYING
    };
    
    State state = State::GAME_OVER; // Start of the State

    // Get Screen resolution and create window
    Vector2f resolution;                              
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Tower of war", Style::Fullscreen);

    // create an sfml view for the main action
    View mainView(FloatRect(0, 0, resolution.x, resolution.y));

    Clock clock;
    Time gameTimeTotal;
    Time dashTime;

    // 2 type of MousePosition
    Vector2f mouseWorld_Position;
    Vector2i mouseScreen_Position;

    Player player;

    IntRect arena;

    VertexArray backGround;
    Texture textureBackGround;
    textureBackGround.loadFromFile("graphics/background.png");

    int numMonsters;
    int numMonstersAlive;
    Monsters* monsters = nullptr;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Return && state == State::PLAYING)
                {
                    state = State::PAUSED;
                }
                else if (event.key.code == Keyboard::Return && state == State::PAUSED)
                {
                    state = State::PLAYING;
                    clock.restart();
                }
                else if (event.key.code == Keyboard::Return && state == State::GAME_OVER)
                {
                    state = State::LEVELING_UP;
                }

                if (state == State::PLAYING)
                {

                }
            }
        } // End event Polling

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (state == State::PLAYING) // Player Control ///////////////////////////////////////////////////////////////////
        {
            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                player.moveUp();
            }
            else
            {
                player.stopUp();
            }
            if (Keyboard::isKeyPressed(Keyboard::S))
            {
                player.moveDown();
            }
            else
            {
                player.stopDown();
            }
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                player.moveLeft();
            }
            else
            {
                player.stopLeft();
            }
            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                player.moveRight();
            }
            else
            {
                player.stopRight();
            }            
        }

        // Player Leveling Up ///////////////////////////////////////////////////////////////////////////////////////
        if (state == State::LEVELING_UP)
        {
            if (event.key.code == Keyboard::Num1)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num2)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num3)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num4)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num5)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num6)
            {
                state = State::PLAYING;
            }

            // Preparing the Arena ////////////////////////////////////////////////////////////////////////////////////
            if (state == State::PLAYING)
            {
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top = 0;

                int tileSize = createBackGround(backGround, arena);

                player.Spawn(arena, resolution, tileSize);

                numMonsters = 0;

                delete[] monsters;
                monsters = createHorde(numMonsters, arena);
                numMonstersAlive = numMonsters;

                clock.restart();
            }
        }

        // Update frame /////////////////////////////////////////////////////////////////////////////////////////
        if (state == State::PLAYING)
        {
            Time dt = clock.restart();

            gameTimeTotal += dt;

            float dtAsSecond = dt.asSeconds();

            // Where is the mouse pointer
            mouseScreen_Position = Mouse::getPosition();

            mouseWorld_Position = window.mapPixelToCoords(Mouse::getPosition(), mainView);

            player.update(dtAsSecond, Mouse::getPosition());

            // Note the player position
            Vector2f playerPosition(player.getPlayerCenter());

            mainView.setCenter(player.getPlayerCenter());

            // Loop for update Monster
            for (int i = 0; i < numMonsters; i++)
            {
                if (monsters[i].Alive())
                {
                    monsters[i].update(dt.asSeconds(), playerPosition);
                }
            }
        }

        // Draw the scene ///////////////////////////////////////////////////////////////////////////////////////
        if (state == State::PLAYING)
        {
            window.clear();
            window.setView(mainView);
            window.draw(backGround, &textureBackGround);
            window.draw(player.getSprite());

            for (int i = 0; i < numMonsters; i++)
            {
                window.draw(monsters[i].getSprite());
            }
        }
        if (state == State::LEVELING_UP)
        {

        }
        if (state == State::PAUSED)
        {

        }
        if (state == State::GAME_OVER)
        {

        }

        window.display();
    }
    delete[] monsters;
    return 0;
}