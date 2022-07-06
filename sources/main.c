#include "raylib.h"

// map raylib keys to buttons
int map_keys[] = {
  KEY_X,           // A
  KEY_Z,           // B
  KEY_S,           // X
  KEY_A,           // Y
  KEY_Q,           // L1
  KEY_W,           // R1
  KEY_ENTER,       // START
  KEY_LEFT_SHIFT,  // SELECT
  KEY_LEFT,        // LEFT
  KEY_RIGHT,       // RIGHT
  KEY_UP,          // UP
  KEY_DOWN         // DOWN
};

// map raylib buttons to buttons
int map_gamepad[] = {
  GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, // A
  GAMEPAD_BUTTON_RIGHT_FACE_DOWN,  // B
  GAMEPAD_BUTTON_RIGHT_FACE_UP,    // X
  GAMEPAD_BUTTON_RIGHT_FACE_LEFT,  // Y
  GAMEPAD_BUTTON_LEFT_TRIGGER_1,  // L1
  GAMEPAD_BUTTON_RIGHT_TRIGGER_1, // R1
  GAMEPAD_BUTTON_MIDDLE_RIGHT,    // START
  GAMEPAD_BUTTON_MIDDLE_LEFT,     // SELECT
  GAMEPAD_BUTTON_LEFT_FACE_LEFT,  // LEFT
  GAMEPAD_BUTTON_LEFT_FACE_RIGHT, // RIGHT
  GAMEPAD_BUTTON_LEFT_FACE_UP,    // UP
  GAMEPAD_BUTTON_LEFT_FACE_DOWN   // DOWN
};

// this is the current state of the virtual gamepad
bool gamepad_state[] = {
  false, // A
  false, // B
  false, // X
  false, // Y
  false, // L1
  false, // R1
  false, // START
  false, // SELECT
  false, // LEFT
  false, // RIGHT
  false, // UP
  false, // DOWN
};


int main(void) {
  const int screenWidth = 320;
  const int screenHeight = 240;

  SetConfigFlags(FLAG_MSAA_4X_HINT);

  InitWindow(screenWidth, screenHeight, "raylib [core] example - gamepad mapped input");
  Texture2D texPs3Pad = LoadTexture(ASSETS_PATH"/bg.png");

  Texture2D gamepad_images[] = {
    LoadTexture(ASSETS_PATH"/a.png"),
    LoadTexture(ASSETS_PATH"/b.png"),
    LoadTexture(ASSETS_PATH"/x.png"),
    LoadTexture(ASSETS_PATH"/y.png"),
    LoadTexture(ASSETS_PATH"/l1.png"),
    LoadTexture(ASSETS_PATH"/r1.png"),
    LoadTexture(ASSETS_PATH"/start.png"),
    LoadTexture(ASSETS_PATH"/select.png"),
    LoadTexture(ASSETS_PATH"/left.png"),
    LoadTexture(ASSETS_PATH"/right.png"),
    LoadTexture(ASSETS_PATH"/up.png"),
    LoadTexture(ASSETS_PATH"/down.png"),
  };

  SetTargetFPS(60);

  while (!WindowShouldClose()){
    // this is the actual mapping
    for (int i=0; i< sizeof(gamepad_state); i++) {
      if (IsKeyPressed(map_keys[i])) {
        gamepad_state[i] = true;
      }
      if (IsKeyReleased(map_keys[i])) {
        gamepad_state[i] = false;
      }
      if (IsGamepadAvailable(0)) {
        if (IsGamepadButtonPressed(0, map_gamepad[i])) {
          gamepad_state[i] = true;
        }
        if (IsGamepadButtonReleased(0, map_gamepad[i])) {
          gamepad_state[i] = false;
        }
      }
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (IsGamepadAvailable(0)) {
      DrawText(TextFormat("Virtual: %s", GetGamepadName(0)), 10, 10, 10, BLACK);
    } else {
      DrawText("Virtual Controller", 10, 10, 10, BLACK);
    }

    DrawTexture(texPs3Pad, 0, 50, WHITE);

    for (int i=0;i<sizeof(gamepad_state); i++) {
      if (gamepad_state[i]) {
        DrawTexture(gamepad_images[i], 0, 2, WHITE);
      }
    }
    
    EndDrawing();
  }

  UnloadTexture(texPs3Pad);
  CloseWindow();
  return 0;
}