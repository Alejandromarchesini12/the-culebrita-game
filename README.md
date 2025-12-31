# The Culebrita (Snake) Game 

## Overview
Culebrita is a classic snake game built in C# during my freshman year at Biola University. Guide the snake through a maze, eat food to grow, and avoid hazards like cacti and your own tail.

## How to Play
- **Objective:** Eat the light red food squares to score points and grow.
- **Controls:** W up, A left, S down, D right, Q quit.
- **Scoring:** Each food eaten = 50 points.
- **Obstacles:** Hitting a cactus or your own body ends the game.

## Game Flow
- Start on the welcome screen, enter the maze, and collect food.
- Game over occurs if you collide with yourself, a cactus, or press Q to exit.

## How to Run (concise)
1) Clone: `git clone https://github.com/Alejandromarchesini12/the-culebrita-game.git`
2) Open `My-Game.sln` in Visual Studio and build (Debug/Release).
3) Run the built EXE and play.

### Run from VS Code (no Visual Studio UI)
- Install **Visual Studio Build Tools** (Desktop C++ workload) so `cl`/`msbuild` are available.
- Install VS Code + the **C/C++ extension (ms-vscode.cpptools)**.
- Open a **Developer PowerShell for VS** in the repo folder.
- Build: `msbuild My-Game.sln /p:Configuration=Debug`
- Run: `Debug\My-Game.exe` (or `Release\My-Game.exe`).

Notes: This is a C++/Windows project that links `graphics.lib`; there are no `pip install` steps.

## Files of interest
- My-Game.cpp, graphics.h, resource.h: core game and resources.
- My-Game.sln, My-Game.vcxproj, My-Game.vcxproj.filters: Visual Studio solution and project files.
- graphics.lib, icon1.ico: supporting assets.
- Main Maze Game.txt: maze content.
- IMPROVEMENTS.md: ideas for future work.

## Future Ideas
- Rotate among multiple maze layouts each run.
- Increase snake speed as you score more points.
- Add sound effects and UI polish.

## Reflection
Building this as a freshman project taught me how much organization matters. Commenting and separating concerns kept the longer codebase manageable. The hardest part was getting the snake movement and growth right, but iterating on past code and asking for help made it possible. If I revisit this, I’d randomize mazes and scale difficulty by speed so each run feels fresh.
