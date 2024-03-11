#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "src/raygui.h"

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen {TITLE, LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_4, LEVEL_5, ENDING } GameScreen;

void draw_level_buttons(GameScreen*, int);
bool draw_exit_button(GameScreen *);

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

    GameScreen currentScreen = TITLE;

    // Count how many levels have been completed
    int level_completed = 0;

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

            } break;
            case LEVEL_2:
            {

            } break;
            case LEVEL_3:
            {

            } break;
            case LEVEL_4:
            {

            } break;
            case LEVEL_5:
            {

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
                    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                    draw_level_buttons(&currentScreen, level_completed);

                } break;
                case LEVEL_1:
                {
                    // TODO: Draw GAMEPLAY screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    DrawText("LEVEL_1", 130, 220, 20, MAROON);
                    draw_exit_button(&currentScreen);

                } break;
                case LEVEL_2:
                {
                    // TODO: Draw GAMEPLAY screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    DrawText("LEVEL_2", 130, 220, 20, MAROON);
                    draw_exit_button(&currentScreen);

                } break;
                case LEVEL_3:
                {
                    // TODO: Draw GAMEPLAY screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    DrawText("LEVEL_3", 130, 220, 20, MAROON);
                    draw_exit_button(&currentScreen);

                } break;
                case LEVEL_4:
                {
                    // TODO: Draw GAMEPLAY screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    DrawText("LEVEL_4", 130, 220, 20, MAROON);
                    draw_exit_button(&currentScreen);

                } break;
                case LEVEL_5:
                {
                    // TODO: Draw GAMEPLAY screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    DrawText("LEVEL_5", 130, 220, 20, MAROON);
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

void draw_level_buttons(GameScreen *current_screen, int level_completed){
    Rectangle level_buttons[5];
    float level_buttons_width = 250.0f, level_buttons_height = 140.0f;
    // Padding under and top of the button
    float padding = 50.0f;

    Font font = GuiGetFont();
    font.baseSize = 2.0f;
    GuiSetFont(font);

    int choosen_level = 0;

    int frames_counter = 120;

    for(int i = 0 ; i < 5; i++){
        level_buttons[i] = (Rectangle){
            .x = GetScreenWidth()/2 - level_buttons_width/2,
            .y = 100.0f + i*(level_buttons_height + padding),
            .width = level_buttons_width,
            .height = level_buttons_height
        };
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
            TODO: FIX THIS
            frames_counter = 0;
        }
        break; 
    
    default:
        break;
    }
    while(frames_counter < 120){
        DrawText("Teljesítened kell az első négy pályát mielőtt elkezdhetnéd az utolsót!", 0, 0, 30.0f, BLACK);
        frames_counter++;
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
    }
    
    // Load back the original font
    GuiSetFont(real_font);
}
