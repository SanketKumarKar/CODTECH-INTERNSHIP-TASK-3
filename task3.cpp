#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
using namespace sf;

// To compile this, you need SFML installed.
// On Debian/Ubuntu: sudo apt-get install libsfml-dev
// On Fedora/CentOS: sudo yum install SFML-devel
// On macOS (with Homebrew): brew install sfml
//
// Compile command: g++ task3.cpp -o snake_game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int TILE_SIZE = 20;

// Direction enum for snake movement
enum class Direction { UP, DOWN, LEFT, RIGHT };

int main() {
    srand(static_cast<unsigned>(time(0)));

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game");
    window.setFramerateLimit(10);

    // --- Game Elements ---
    // Snake
    list<Vector2i> snake;
    snake.push_back({WINDOW_WIDTH / (2 * TILE_SIZE), WINDOW_HEIGHT / (2 * TILE_SIZE)});
    Direction direction = Direction::RIGHT;

    // Food
    Vector2i food;
    auto spawn_food = [&]() {
        food.x = rand() % (WINDOW_WIDTH / TILE_SIZE);
        food.y = rand() % (WINDOW_HEIGHT / TILE_SIZE);
    };
    spawn_food();

    // Score
    int score = 0;
    Font font;
    
    // Cross-platform font loading
    bool fontLoaded = false;
    vector<string> fontPaths = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",  // Linux
        "C:/Windows/Fonts/arial.ttf",                       // Windows
        "/System/Library/Fonts/Supplemental/Arial.ttf"      // macOS
    };
    
    for (const string& fontPath : fontPaths) {
        if (font.loadFromFile(fontPath)) {
            fontLoaded = true;
            break;
        }
    }
    
    if (!fontLoaded) {
        cerr << "Warning: Could not load any font file. Text will not be displayed." << endl;
        // Continue without font rather than exiting
    }
    
    Text scoreText("Score: 0", font, 24);
    scoreText.setFillColor(Color::White);

    // Sound effects (optional, requires sound files)
    // SoundBuffer eatBuffer, gameOverBuffer;
    // if (!eatBuffer.loadFromFile("eat.wav")) return -1;
    // if (!gameOverBuffer.loadFromFile("gameover.wav")) return -1;
    // Sound eatSound(eatBuffer), gameOverSound(gameOverBuffer);

    bool gameOver = false;

    // --- Game Loop ---
    while (window.isOpen()) {
        // --- Event Handling ---
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (!gameOver) {
                    switch (event.key.code) {
                        case Keyboard::Up:    if (direction != Direction::DOWN) direction = Direction::UP; break;
                        case Keyboard::Down:  if (direction != Direction::UP) direction = Direction::DOWN; break;
                        case Keyboard::Left:  if (direction != Direction::RIGHT) direction = Direction::LEFT; break;
                        case Keyboard::Right: if (direction != Direction::LEFT) direction = Direction::RIGHT; break;
                        default: break;
                    }
                }
            }
        }

        if (!gameOver) {
            // --- Game Logic ---
            // Move snake
            Vector2i newHead = snake.front();
            switch (direction) {
                case Direction::UP:    newHead.y--; break;
                case Direction::DOWN:  newHead.y++; break;
                case Direction::LEFT:  newHead.x--; break;
                case Direction::RIGHT: newHead.x++; break;
            }
            snake.push_front(newHead);

            // Check for collision with food
            if (newHead == food) {
                score++;
                scoreText.setString("Score: " + to_string(score));
                spawn_food();
                // eatSound.play();
                // Increase speed
                window.setFramerateLimit(10 + score / 5);
            } else {
                snake.pop_back();
            }

            // Check for collision with self or walls
            if (newHead.x < 0 || newHead.x >= WINDOW_WIDTH / TILE_SIZE ||
                newHead.y < 0 || newHead.y >= WINDOW_HEIGHT / TILE_SIZE) {
                gameOver = true;
                // gameOverSound.play();
            }
            auto it = next(snake.begin());
            while (it != snake.end()) {
                if (*it == newHead) {
                    gameOver = true;
                    // gameOverSound.play();
                }
                it++;
            }
        }

        // --- Drawing ---
        window.clear(Color::Black);

        // Draw snake
        for (const auto& segment : snake) {
            RectangleShape shape(Vector2f(TILE_SIZE, TILE_SIZE));
            shape.setPosition(segment.x * TILE_SIZE, segment.y * TILE_SIZE);
            shape.setFillColor(Color::Green);
            window.draw(shape);
        }

        // Draw food
        RectangleShape foodShape(Vector2f(TILE_SIZE, TILE_SIZE));
        foodShape.setPosition(food.x * TILE_SIZE, food.y * TILE_SIZE);
        foodShape.setFillColor(Color::Red);
        window.draw(foodShape);

        // Draw score
        if (fontLoaded) {
            window.draw(scoreText);
        }

        if (gameOver) {
            if (fontLoaded) {
                Text gameOverText("Game Over", font, 50);
                gameOverText.setFillColor(Color::Red);
                gameOverText.setPosition(WINDOW_WIDTH / 2 - gameOverText.getGlobalBounds().width / 2,
                                         WINDOW_HEIGHT / 2 - gameOverText.getGlobalBounds().height / 2);
                window.draw(gameOverText);
            }
        }

        window.display();
    }

    return 0;
}
