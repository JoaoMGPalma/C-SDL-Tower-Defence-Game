# C++-SDL-Tower-Defence-Game
A 2D action-defense game built in C++ and SDL2. Defend your castle from waves of enemies using precision archery mechanics and modular game systems.

Key Features
- Custom Graphics Engine: Powered by MiniGfx, a custom lightweight single-header wrapper for SDL2 that simplifies window management, event handling, and 2D primitive rendering.
- Procedural Backgrounds: A dynamic environment system that generates sky gradients, clouds, mountains, and terrain using math-based rendering rather than static images.
- Wave System: Increasingly difficult waves of enemies with randomized variants and stats managed by a central GameManager.
- Custom Bitmap Font: A handwritten 5x7 bitmap font system used to render all UI text and the "Game Over" screen without needing external .ttf files.
- Horde AI: Enemies feature automated movement, health bars, and collision-based damage logic against the player's castle.

Technical Architecture
The project follows a clean Object-Oriented Programming (OOP) structure:
- GameObject / Character: Base classes that handle positioning, health, and basic movement.
- GameManager: The "brain" of the game. It manages the life cycle of arrows and enemies, detects collisions, and tracks the game state (Waves, Game Over).
- Legolas & Enemy: Implementation of specific behaviors, including custom primitive-based rendering for characters.
- MiniGfx.h: An abstraction layer that hides SDL2 boilerplate, making the game code more readable and maintainable.

Installation & Building

C++17 Compiler (GCC/Clang/MSVC)
SDL2 Development Libraries - https://github.com/libsdl-org/SDL/releases
SDL2_image Development Libraries - https://github.com/libsdl-org/SDL_image/releases

<img width="800" height="602" alt="image" src="https://github.com/user-attachments/assets/c3997890-0d40-4442-a926-4ccbe5e6a753" />
