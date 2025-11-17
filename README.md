# 🎮 C++ Game Collection with raylib

A beginner-friendly game dev collection built in C++ using [raylib](https://www.raylib.com/). Includes:

- 🚗 GTA-style sandbox
- 🧠 Snake Ladder
- ❌⭕ Tic-Tac-Toe

Each game is standalone, easy to build, and perfect for learning game development fundamentals.

---

## 🛠️ Setup Guide (Windows)

### ✅ Prerequisites

| Tool        | Version | Notes                          |
|-------------|---------|--------------------------------|
| raylib      | ≥ 4.5   | [Download raylib](https://github.com/raysan5/raylib) |
| MinGW       | ≥ 8.1   | Use w64devkit or MSYS2         |
| VS Code     | Latest  | With C++ extension installed   |
| Git         | Latest  | For cloning the repo           |

---

### 📦 Installation Steps

1. **Clone the repo**
   ```bash
   git clone https://github.com/infinisri06-sri/CPP_Games
   cd CPP_Games
## 2. Install raylib

Follow the official Windows setup:  
https://github.com/raysan5/raylib/wiki/Install

Make sure:

- `raylib/src` is compiled  
- Libraries (`.a` or `.dll`) are accessible to MinGW  

---

## 3. Configure VS Code

Update your `tasks.json` to build a specific game:

```json
"args": [
    "RAYLIB_PATH=C:/raylib/raylib",
    "PROJECT_NAME=${fileBasenameNoExtension}",
    "OBJS=${fileBasenameNoExtension}.cpp",
    "BUILD_MODE=DEBUG"
],
```

## 4. Build a game
- Press **CTRL + SHIFT + B** in VS Code
- OR
```bash
mingw32-make <Game-Name>
```

## 5. Run the game

- Press **F5** in VS Code  
- Or run the generated `.exe`

---

# 🚗 GTA-Style Sandbox

## 🎮 Gameplay
- **WASD** → Move  
- **E** → Enter/exit car  
- Hit NPCs to splatter them  
- NPCs respawn infinitely  
- Kill counter updates live  

## 🛠️ Build
```bash
mingw32-make gta_proto
```
# 🧠 Snake Ladder

## 🎮 Gameplay
- Animated dice roll  
- Land on ladders → climb  
- Land on snakes → slide  
- Reach **tile 100** to win  
- Supports 2 players  

## 🛠️ Build
```bash
mingw32-make snake_ladder
```
# ❌⭕ Tic-Tac-Toe

## 🎮 Gameplay
- Click grid to place **X** or **O**  
- Win/draw detection  
- Reset button  
- Clean UI with turn indicator  

## 🛠️ Build
```bash
mingw32-make tic_tac_toe
```
## 📸 Screenshots

### 🚗 GTA-Style Sandbox
![Driving and NPC collision](assets/screenshots/gta_drive.png)

### 🧠 Snake Ladder
![Snake Ladder board](assets/screenshots/snake_ladder_board.png)

### ❌⭕ Tic-Tac-Toe
![Game screen](assets/screenshots/tic_tac_toe_start.png)


---

# 🧠 For Beginners

This repo is perfect for:

- Learning raylib fundamentals  
- Practicing game loops  
- Handling input, drawing, collisions  
- Creating UI and simple animations  

---

# 🤝 Contributing

Ideas to add:

- Sound effects  
- Smarter NPC AI  
- Local multiplayer  
- Save/load system  
- Particle effects  
- Menu UI  

Pull requests are welcome!

---

# 📄 License

MIT License — see `LICENSE` file for details.

---

# 🙌 Credits

Built with ❤️ using **raylib**  
Game logic & design by **@infinisri06-sri** and **@pvshyamlal**

