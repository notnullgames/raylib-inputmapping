#include "raylib.h"

// these are the button-consts that your thing responds to
#define A 0
#define B 1
#define X 2
#define Y 3
#define L1 4
#define R1 5
#define START 6
#define SELECT 7
#define LEFT 8
#define RIGHT 9
#define UP 10
#define DOWN 11

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
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false
};


int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - gamepad mapped input");
    Texture2D texPs3Pad = LoadTexture(ASSETS_PATH"/ps3.png");

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
            DrawText(TextFormat("GP1: %s", GetGamepadName(0)), 10, 10, 10, BLACK);
        }
        DrawTexture(texPs3Pad, 0, 0, DARKGRAY);

        // Draw buttons: basic
        if (gamepad_state[SELECT]) DrawRectangle(328, 170, 32, 13, RED);
        if (gamepad_state[START]) DrawTriangle((Vector2){ 436, 168 }, (Vector2){ 436, 185 }, (Vector2){ 464, 177 }, RED);
        if (gamepad_state[X]) DrawCircle(557, 144, 13, LIME);
        if (gamepad_state[A]) DrawCircle(586, 173, 13, RED);
        if (gamepad_state[B]) DrawCircle(557, 203, 13, VIOLET);
        if (gamepad_state[Y]) DrawCircle(527, 173, 13, PINK);

        // Draw buttons: d-pad
        DrawRectangle(225, 132, 24, 84, BLACK);
        DrawRectangle(195, 161, 84, 25, BLACK);
        if (gamepad_state[UP]) DrawRectangle(225, 132, 24, 29, RED);
        if (gamepad_state[DOWN]) DrawRectangle(225, 132 + 54, 24, 30, RED);
        if (gamepad_state[LEFT]) DrawRectangle(195, 161, 30, 25, RED);
        if (gamepad_state[RIGHT]) DrawRectangle(195 + 54, 161, 30, 25, RED);

        // Draw buttons: left-right back buttons
        if (gamepad_state[L1]) DrawCircle(239, 82, 20, RED);
        if (gamepad_state[R1]) DrawCircle(557, 82, 20, RED);


        // Axis & center-button is not used, all input is setup like an SNES controller (D-pad + buttons)

        // // Draw buttons: ps
        // if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_MIDDLE)) DrawCircle(396, 222, 13, RED);

        // // Draw axis: left joystick
        // DrawCircle(319, 255, 35, BLACK);
        // DrawCircle(319, 255, 31, LIGHTGRAY);
        // DrawCircle(319 + (int)(GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) * 20),
        //            255 + (int)(GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) * 20), 25, BLACK);

        // // Draw axis: right joystick
        // DrawCircle(475, 255, 35, BLACK);
        // DrawCircle(475, 255, 31, LIGHTGRAY);
        // DrawCircle(475 + (int)(GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X) * 20),
        //            255 + (int)(GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y) * 20), 25, BLACK);

        // // Draw axis: left-right triggers
        // DrawRectangle(169, 48, 15, 70, GRAY);
        // DrawRectangle(611, 48, 15, 70, GRAY);
        // DrawRectangle(169, 48, 15, (int)(((1 - GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_TRIGGER)) / 2) * 70), RED);
        // DrawRectangle(611, 48, 15, (int)(((1 - GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_TRIGGER)) / 2) * 70), RED);
        
        EndDrawing();
    }

    UnloadTexture(texPs3Pad);
    CloseWindow();
    return 0;
}