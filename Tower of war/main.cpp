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
    mainView.setSize(1400.f, 800.f);

    Clock clock;
    Time gameTimeTotal;
    Time dashTime;

    // 2 type of MousePosition
    Vector2f mouseWorld_Position;
    Vector2i mouseScreen_Position;

    Player player;
    Time LastDash;
    int DashRate = 1; // Dash/Sec.

    IntRect arena;

    VertexArray backGround;
    Texture textureBackGround;
    textureBackGround.loadFromFile("graphics/Arena.png");

    int numMonsters;
    int numMonstersAlive;
    Monsters* monsters = nullptr;

    // Megic 
    Megic fireball[100];
    int currentFireball = 0;
    int Mana = 10;
    int maxMana = 10;
    int castRate = 10; // ball/Sec.
    Time LastPressed;

    // Pickup
    pickUp HealthPickUp(1);
    pickUp ManaPickUp(2);

    int score = 0;
    int highScore = 0;

    // HUD and Text ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // Home / Game Over screen
    Sprite spriteGameOver;
    Texture texTureGameOver = TextureHolder::GetTexture("graphics/wallpaper.png");
    spriteGameOver.setTexture(texTureGameOver);
    spriteGameOver.setPosition(0, 0);

    // view for HUD
    View hudView(FloatRect(0, 0, resolution.x, resolution.y));

    // Mana icon
    Sprite spriteManaIcon;
    Texture texTureManaIcon = TextureHolder::GetTexture("graphics/mana_icon.png");
    spriteManaIcon.setTexture(texTureManaIcon);
    spriteManaIcon.setPosition(20, 100);

    // Load the font
    Font font;
    font.loadFromFile("font/IMMORTAL.ttf");

    // Pause the game Text
    Text pauseText;
    pauseText.setFont(font);
    pauseText.setCharacterSize(72);
    pauseText.setFillColor(Color::White);
    pauseText.setPosition(350, 200);
    pauseText.setString("Press Enter \nto continue");

    // Game Over Text
    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(72);
    gameOverText.setFillColor(Color::White);
    gameOverText.setPosition(280, 540);
    gameOverText.setString("Click here to Challenge");

    // Leveling up
    Text levelUpText;
    levelUpText.setFont(font);
    levelUpText.setCharacterSize(84);
    levelUpText.setFillColor(Color::White);
    levelUpText.setPosition(80, 150);
    stringstream levelUpStream;
    levelUpStream <<
        "Increased cast speed" <<
        "\nIncreased max mana" <<
        "\nIncreased max health" <<
        "\nIncreased running speed" <<
        "\nMore and better health potion" <<
        "\nMore and better mana potion";
    levelUpText.setString(levelUpStream.str());

    // Mana
    Text manaText;
    manaText.setFont(font);
    manaText.setCharacterSize(50);
    manaText.setFillColor(Color::White);
    manaText.setPosition(70, 95);

    // Score
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(1500, 0);

    // Monster remaining
    Text textMonsterRemaining;
    textMonsterRemaining.setFont(font);
    textMonsterRemaining.setCharacterSize(50);
    textMonsterRemaining.setFillColor(Color::White);
    textMonsterRemaining.setPosition(1500, 900);
    textMonsterRemaining.setString("Monster : 100");

    // Wave number
    int wave = 0;
    Text waveNumberText;
    waveNumberText.setFont(font);
    waveNumberText.setCharacterSize(50);
    waveNumberText.setFillColor(Color::White);
    waveNumberText.setPosition(1500, 60);
    waveNumberText.setString("Wave : 0");

    // Health bar
    RectangleShape healthBar;
    healthBar.setFillColor(Color::Red);
    healthBar.setPosition(20, 0); 

    // When did we last update the HUD
    int framesSinceLastHUD_Update = 0;

    // How often (in frame) should we update the HUD
    int fpsMeasurementFrameInterval = 1;

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
            if (Keyboard::isKeyPressed(Keyboard::LShift))
            {
                if (gameTimeTotal.asMilliseconds() - LastDash.asMilliseconds() > 1000 / DashRate)
                {
                    player.moveDash();
                    LastDash = gameTimeTotal;
                }
            }

            // Cast fireball
            if (Mouse::isButtonPressed(Mouse::Right))
            {
                if (gameTimeTotal.asMilliseconds() - LastPressed.asMilliseconds() > 1000 / castRate && Mana > 0)
                {
                    fireball[currentFireball].Cast(player.getPlayerCenter().x, player.getPlayerCenter().y, mouseWorld_Position.x, mouseWorld_Position.y);

                    currentFireball++;
                    if (currentFireball > 99)
                    {
                        currentFireball = 0;
                    }

                    LastPressed = gameTimeTotal;
                    Mana--; 
                }
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

                HealthPickUp.setArena(arena);
                ManaPickUp.setArena(arena);

                numMonsters = 2;

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

            // Update fireball in flight
            for (int i = 0; i < 100; i++) 
            {
                if (fireball[i].isInFlight())
                {
                    fireball[i].update(dtAsSecond);
                }
            }

            // Update pickups
            HealthPickUp.update(dtAsSecond);
            ManaPickUp.update(dtAsSecond);

            // collision detection
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < numMonsters; j++)
                {
                    if (fireball[i].isInFlight() && monsters[j].Alive())
                    {
                        if (fireball[i].getPosition().intersects(monsters[j].getPosition()))
                        {
                            fireball[i].stop();

                            if (monsters[j].hit())
                            {
                                score += 10;
                                if (score > highScore)
                                {
                                    highScore = score;
                                }

                                numMonstersAlive--;

                                if (numMonstersAlive == 0)
                                {
                                    state = State::LEVELING_UP;
                                }
                            }
                        }
                    }
                }
            }

            // attack the player
            for (int i = 0; i < numMonsters; i++)
            {
                if (player.getPosition().intersects(monsters[i].getPosition()) && monsters[i].Alive())
                {
                    if (player.hit(gameTimeTotal))
                    {
                        //
                    }

                    if (player.getHealth() <= 0)
                    {
                        state = State::GAME_OVER;
                    }
                }
            }

            // get the potion
            if (player.getPosition().intersects(HealthPickUp.getPosition()) && HealthPickUp.isSpawned())
            {
                player.increaseHealthLevel(HealthPickUp.gotIt());
            }
            if (player.getPosition().intersects(ManaPickUp.getPosition()) && ManaPickUp.isSpawned())
            {
                Mana += ManaPickUp.gotIt();
            }

            if (Mana > maxMana)
            {
                Mana = maxMana;
            }

            // size up the health bar
            healthBar.setSize(Vector2f(player.getHealth() * 3, 70));

            framesSinceLastHUD_Update++;

            if (framesSinceLastHUD_Update > fpsMeasurementFrameInterval)
            {
                //Update game HUD text
                stringstream ssMana;
                stringstream ssScore;
                stringstream ssWave;
                stringstream ssMonsterAlive;

                // Update Mana Text
                ssMana << Mana << "/" << maxMana;
                manaText.setString(ssMana.str());

                // Update Score Text
                ssScore << "Score : " << score;
                scoreText.setString(ssScore.str());

                // Update the Wave
                ssWave << "Wave : " << wave;
                waveNumberText.setString(ssWave.str());

                // Update Monster Alive
                ssMonsterAlive << "Monster : " << numMonstersAlive;
                textMonsterRemaining.setString(ssMonsterAlive.str());
                framesSinceLastHUD_Update = 0;
            }
        }

        // Draw the scene ///////////////////////////////////////////////////////////////////////////////////////
        if (state == State::PLAYING)
        {
            window.clear();
            window.setView(mainView);
            window.draw(backGround, &textureBackGround);

            if (ManaPickUp.isSpawned())
            {
                window.draw(ManaPickUp.getSprite());
            }
            if (HealthPickUp.isSpawned())
            {
                window.draw(HealthPickUp.getSprite());
            }

            for (int i = 0; i < numMonsters; i++)
            {
                window.draw(monsters[i].getSprite());
            }

            window.draw(player.getSprite());

            for (int i = 0; i < 100; i++)
            {
                if (fireball[i].isInFlight())
                {
                    window.draw(fireball[i].getShape());
                }
            }

            window.setView(hudView);

            // Draw HUD element
            window.draw(spriteManaIcon);
            window.draw(manaText);
            window.draw(scoreText);
            window.draw(healthBar);
            window.draw(waveNumberText);
            window.draw(textMonsterRemaining);
            
        }
        if (state == State::LEVELING_UP)
        {
            window.draw(spriteGameOver);
            window.draw(levelUpText);
        }
        if (state == State::PAUSED)
        {
            window.draw(pauseText);
        }
        if (state == State::GAME_OVER)
        {
            window.draw(spriteGameOver);
            window.draw(gameOverText);
            window.draw(scoreText);
        }

        window.display();
    }
    delete[] monsters;
    return 0;
}