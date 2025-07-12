# Task 3: Snake Game with Graphics

This is a classic Snake game implemented in C++ with the SFML (Simple and Fast Multimedia Library) for graphics and windowing.

## Code Description

The program `task3.cpp` contains the complete source code for the game. It is a single, self-contained file that relies on the SFML library.

- **Game Logic**: The game state, including the snake's position, the food's location, the score, and the current direction of movement, is managed within the `main` function.
- **Rendering**: SFML's `RenderWindow` is used to create the game window. The snake, food, and score are drawn as `sf::RectangleShape` and `sf::Text` objects.
- **Controls**: The snake is controlled using the arrow keys (Up, Down, Left, Right).
- **Difficulty**: The game's speed increases as the player's score goes up, making it progressively more challenging.

## Dependencies

This program requires the **SFML** development library.

### Linux:
-   **On Debian/Ubuntu:**
    ```bash
    sudo apt-get install libsfml-dev
    ```
-   **On Fedora/CentOS:**
    ```bash
    sudo yum install SFML-devel
    ```

### macOS:
-   **With Homebrew:**
    ```bash
    brew install sfml
    ```

### Windows:
-   **Option 1: Using vcpkg (Recommended)**
    ```cmd
    git clone https://github.com/Microsoft/vcpkg.git
    cd vcpkg
    .\bootstrap-vcpkg.bat
    .\vcpkg install sfml
    ```
-   **Option 2: Manual Installation**
    1. Download SFML from https://www.sfml-dev.org/download.php
    2. Extract to a folder (e.g., `C:\SFML`)
    3. Add the bin directory to your PATH environment variable

The game also requires a font file to display the score. The code currently points to different font paths based on the operating system:
- **Linux**: `/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf`
- **Windows**: `C:/Windows/Fonts/arial.ttf`
- **macOS**: `/System/Library/Fonts/Supplemental/Arial.ttf`

If these paths don't work on your system, you may need to change the font path in the source code.

## How to Compile and Run

### Linux/macOS:
1.  **Compile the code:**
    Open a terminal and use g++ to compile the game. You must link the necessary SFML modules.

    ```bash
    g++ task3.cpp -o snake_game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
    ```

2.  **Run the game:**
    Execute the compiled program.

    ```bash
    ./snake_game
    ```

### Windows:
1.  **Compile the code:**
    
    **If using vcpkg:**
    ```cmd
    g++ task3.cpp -o snake_game.exe -I[vcpkg-root]\installed\x64-windows\include -L[vcpkg-root]\installed\x64-windows\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
    ```
    
    **If using manual installation:**
    ```cmd
    g++ task3.cpp -o snake_game.exe -IC:\SFML\include -LC:\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
    ```
    
    **Note:** Replace `[vcpkg-root]` with your actual vcpkg installation path, or `C:\SFML` with your actual SFML installation path.

2.  **Run the game:**
    Execute the compiled program.

    ```cmd
    snake_game.exe
    ```

    A window will open, and you can start playing immediately. Use the arrow keys to control the snake.
