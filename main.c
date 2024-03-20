#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "src/raygui.h"

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen {TITLE, LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_4, LEVEL_5, ENDING } GameScreen;

void draw_level_buttons(GameScreen*, int, bool *);
bool draw_exit_button(GameScreen *);
bool draw_level_1(GameScreen *);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "TES");
    //ToggleFullscreen();

    GameScreen currentScreen = TITLE;

    // Count how many levels have been completed
    int level_completed = 0;
    bool game_completed = false, levels[5] = {false};

    // TODO: Initialize all required variables and load all required data here!

    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        switch(currentScreen)
        {
            case TITLE:
            {

            } break;
            case LEVEL_1:
            {
                if(IsKeyPressed(KEY_K)){ 
                    levels[0] = true;
                    level_completed++;
                }
            } break;
            case LEVEL_2:
            {
                if(IsKeyPressed(KEY_K)){
                    levels[1] = true;
                    level_completed++;
                }
            } break;
            case LEVEL_3:
            {
                if(IsKeyPressed(KEY_K)){
                    levels[2] = true;
                    level_completed++;
                }
            } break;
            case LEVEL_4:
            {
                if(IsKeyPressed(KEY_K)){
                    levels[3] = true;
                    level_completed++;
                }
            } break;
            case LEVEL_5:
            {
                if(IsKeyPressed(KEY_K)){
                    levels[4] = true;
                    level_completed++;
                }
            } break;
            case ENDING:
            {

            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch(currentScreen)
            {
                case TITLE:
                {
                    // TODO: Draw TITLE screen here!
                    draw_level_buttons(&currentScreen, level_completed, levels);

                } break;
                case LEVEL_1:
                {
                    // TODO: Draw GAMEPLAY screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    DrawText("LEVEL 1", screenWidth/2, screenHeight/2, 60, MAROON);
                    draw_level_1(&currentScreen);

                } break;
                case LEVEL_2:
                {
                    // TODO: Draw GAMEPLAY screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    DrawText("LEVEL 2", screenWidth/2, screenHeight/2, 60, MAROON);
                    draw_exit_button(&currentScreen);

                } break;
                case LEVEL_3:
                {
                    // TODO: Draw GAMEPLAY screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    DrawText("LEVEL 3", screenWidth/2, screenHeight/2, 60, MAROON);
                    draw_exit_button(&currentScreen);

                } break;
                case LEVEL_4:
                {
                    // TODO: Draw GAMEPLAY screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    DrawText("LEVEL 4", screenWidth/2, screenHeight/2, 60, MAROON);
                    draw_exit_button(&currentScreen);

                } break;
                case LEVEL_5:
                {
                    // TODO: Draw GAMEPLAY screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    DrawText("LEVEL 5", screenWidth/2, screenHeight/2, 60, MAROON);
                    draw_exit_button(&currentScreen);

                } break;
                case ENDING:
                {
                    // TODO: Draw ENDING screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                    DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
                    draw_exit_button(&currentScreen);

                } break;
                default: break;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void draw_level_buttons(GameScreen *current_screen, int level_completed, bool *levels){
    Rectangle level_buttons[5];
    float level_buttons_width = 250.0f, level_buttons_height = 140.0f;
    // Padding under and top of the button
    float padding = 50.0f;

    Font font = GuiGetFont();
    font.baseSize = 2.0f;
    GuiSetFont(font);

    int choosen_level = 0;

    static int display_text_timer = 0;


    for(int i = 0 ; i < 5; i++){
        level_buttons[i] = (Rectangle){
            .x = GetScreenWidth()/2 - level_buttons_width/2,
            .y = 100.0f + i*(level_buttons_height + padding),
            .width = level_buttons_width,
            .height = level_buttons_height
        };
        
        // Display if a level was completed or not by drawing a rectangle behind the given button
        Rectangle button_underlay = (Rectangle){
            .x = (GetScreenWidth()/2 - level_buttons_width/2) - 15.0f,
            .y = (100.0f + i*(level_buttons_height + padding)) - 15.0f,
            .width = level_buttons_width + 30.0f,
            .height = level_buttons_height + 30.0f
        };
        if(levels[i]) DrawRectangleRec(button_underlay, GREEN);
        else DrawRectangleRec(button_underlay, RED);
        
        if(GuiButton(level_buttons[i], TextFormat("%d. pálya", i+1))){
            // Save the index of the level button the user clicked on
            choosen_level = i+1;
            break;
        }
    }
    // Switch to the level corresponding to the button clicked by the user
    switch (choosen_level)
    {
    case 1:
        *current_screen = LEVEL_1;
        break;

    case 2:
        *current_screen = LEVEL_2;
        break;

    case 3:
        *current_screen = LEVEL_3;
        break;

    case 4:
        *current_screen = LEVEL_4;
        break;

    case 5:
        if(4 <= level_completed){
            *current_screen = LEVEL_5;
        } else {
            // This will activate the timer
            display_text_timer = 120; 
        }
        break; 
    
    default:
        break;
    }

    if(display_text_timer > 0){ 
        DrawText("Még nem teljesítetted a többi pályát!", GetScreenWidth()/4 - 100.0f, 10.0f, 60.0f, RED);
        display_text_timer--;
    }

    if(levels[4]){
        DrawText("Gratulálunk! Sikeresen teljesítetted a játékot!", GetScreenWidth()/4 - 220.0f, 10.0f, 60.0f, GREEN);
    }
}


bool draw_exit_button(GameScreen *current_screen){
    // I have no idea how to set the font size for only one instance, so I save the relevant font then reload it after I draw parts with the temporary font size
    Font real_font = GuiGetFont();
    Font temp_font = real_font;
    temp_font.baseSize = 3.0f;
    GuiSetFont(temp_font);

    float exit_button_width = 100.0f, exit_button_height = 100.0f;

    Rectangle exit_button = (Rectangle){
        .x = GetScreenWidth() - exit_button_width,
        .y = 0.0f,
        .width = exit_button_width,
        .height = exit_button_height
    };
    if(GuiButton(exit_button, "Menü")){
        *current_screen = TITLE;
        // Load back the original font
        GuiSetFont(real_font);

        return true;
    }
    
    // Load back the original font
    GuiSetFont(real_font);

    return false;
}

bool draw_level_1(GameScreen *currentScreen) {
    static bool textures_loaded = false;
    static Texture2D lever_lever, lever_bottom;
    // Loading textures
    if(!textures_loaded){
        lever_lever = LoadTexture("assets/level_1/lever_lever.png");
        lever_bottom = LoadTexture("assets/level_1/lever_bottom.png");

        textures_loaded = true;
    }

    static float rotation = 0.0f;
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) rotation++;
    else if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) rotation--;

    // Draw the lever parts
    float lever_scale = 0.4f;
    Vector2 lever_lever_size = (Vector2){lever_lever.width * lever_scale, lever_lever.height * lever_scale};
    Vector2 lever_bottom_size = (Vector2){lever_bottom.width * lever_scale, lever_bottom.height * lever_scale};
    DrawTexturePro(lever_lever,
                    (Rectangle){0.0f, 0.0f, lever_lever.width, lever_lever.height},
                    (Rectangle){345.0f, 1457.0f - lever_lever_size.y, lever_lever_size.x, lever_lever_size.y},
                    (Vector2){583.0f*lever_scale, 969.0f*lever_scale},
                    rotation,
                    WHITE);
    DrawTexturePro(lever_bottom,
                    (Rectangle){0.0f, 0.0f, lever_bottom.width, lever_bottom.height},
                    (Rectangle){100.0f, GetScreenHeight() - lever_bottom_size.y, lever_bottom_size.x, lever_bottom_size.y},
                    (Vector2){0.0f, 0.0f},
                    0.0f,
                    WHITE);

    // If the user has clicked on the Menu button, unload the textures
    if(draw_exit_button(currentScreen)){
        UnloadTexture(lever_lever);
        UnloadTexture(lever_bottom);

        textures_loaded = false;
    }
}
