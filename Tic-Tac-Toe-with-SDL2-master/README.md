# Tic-Tac-Toe-with-SDL2 in C++
![Screenshot2](assets/Screenshot2.png?raw=true)

## Requirements
- Microsoft Visual Studio
- SDL2 (already included in Dependencies folder)

## How to build and run
- Open Microsoft Visual Studio
- Click "Clone a repository"
- Copy and paste respository link
- Open the solution file
- Compile and run in x86 mode in either Debug or Release
- If you want to run from the generated executable, copy the dll files and assets folder in the same directory as the executable.

## Framework diagram
Key: 
  - Arrow = inheritance
  - Line = composition
  
![Framework](assets/Framework.png?raw=true)

- All cells act as buttons since they must be clicked by the mouse
- Grid colour changes depending whos turn it is (blue = cross, red = circle)
- Winning row, col, or diagonal of 3 will be highlighted in that players corresponding colour

![Screenshot1](assets/Screenshot1.png?raw=true)
