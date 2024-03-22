#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "src/raygui.h"
#include <math.h>

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
    static bool electricity = false, switched_on = false;
    static Texture2D lever_lever, lever_bottom, display_off, display_on;
    // Loading textures
    if(!textures_loaded){
        lever_lever = LoadTexture("assets/level_1/lever_lever.png");
        lever_bottom = LoadTexture("assets/level_1/lever_bottom.png");
        display_off = LoadTexture("assets/level_1/on_off_display_OFF.png");
        display_on = LoadTexture("assets/level_1/on_off_display_ON.png");

        textures_loaded = true;
    }
    // DEBUG
    if(IsKeyPressed(KEY_S) && !electricity) electricity = true;
    else if(IsKeyPressed(KEY_S) && electricity) electricity = false; 

    Vector2 lever_lever_size = (Vector2){lever_lever.width, lever_lever.height};
    Vector2 lever_bottom_size = (Vector2){lever_bottom.width, lever_bottom.height};
    // Destionation rectangle of the lever_Lever texture
    Rectangle level_level_rec = (Rectangle){
        .x = 100.0f + 260.0f,
        .y = GetScreenHeight() - lever_bottom_size.y + 331.0f*0.75,
        .width = lever_lever_size.x,
        .height = lever_lever_size.y
    };

    // Drawing the 7 segment display
    Rectangle display_src = (Rectangle){
        .x = 0.0f,
        .y = 0.0f,
        .width = display_on.width,
        .height = display_on.height
    };

    Rectangle display_rec = (Rectangle){
        .x = 260.0f,
        .y = 700.0f,
        .width = display_on.width * 0.8,
        .height = display_on.height * 0.8
    };

    if(electricity) DrawTexturePro(display_on, display_src, display_rec, (Vector2){.x=0, .y=0}, 0.0f, WHITE);
    else DrawTexturePro(display_off, display_src, display_rec, (Vector2){.x=0, .y=0}, 0.0f, WHITE);


    // I think changing the origin point shifts the entire rectangle away, so and unshifted version should be used for detecting clicks on the lever
    Rectangle unshifted_lever_rec = (Rectangle){
        .x = 100.0f,
        .y = GetScreenHeight() - lever_bottom_size.y,
        .width = lever_lever_size.x,
        .height = lever_lever_size.y
    };

    // ORIGINAL PLAN: There should be a circle at the end of the lever (where the knob is on the lever), so a click on it could be detected and 'realistic' feel of pulling the lever can be achieved
    // static Vector2 p = (Vector2){.x = 360, .y = 955};
    // static Vector2 l = (Vector2){.x = 570, .y = 750};
    // static Vector2 c = (Vector2){.x = 570, .y = 750};
    // float distance = sqrt(pow(l.x - p.x, 2) + pow(l.y - p.y, 2));
    static float rotation = 45.0f, d_rotation = 0.0f;
    float mouse_pos_x_pressed;
    // Check fif the left mouse button was pressed inside the rectangle of the lever
    if(electricity && (MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), unshifted_lever_rec)){
        mouse_pos_x_pressed = GetMousePosition().x;
    } else if(electricity && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), unshifted_lever_rec)){
        // (The x axis of the mouse position - x axis of the texture's origin point) - the x axis of the mouse position when the mouse left button was pressed down * scale (so "pulling" the lever is slower)
        d_rotation = ((GetMousePosition().x - (100.0f + 260.0f)) - mouse_pos_x_pressed) * 0.01;;
        if(-45.0f <= rotation && rotation <= 45.0f){
            rotation += d_rotation;
            // c.x = p.x + distance * cos(rotation * 0.1);
            // c.y = p.y + distance * sin(rotation * 0.1);
        } else if(rotation < -45.0f && 0 < d_rotation) rotation += d_rotation;
        else if(electricity && 45.0f < rotation && d_rotation < 0) rotation += d_rotation;
    }

    // Draw the lever parts
    DrawTexturePro(lever_lever,
                    (Rectangle){0.0f, 0.0f, lever_lever.width, lever_lever.height},
                    level_level_rec,
                    (Vector2){260.0f, 331.0f},
                    rotation,
                    WHITE);
    DrawTexturePro(lever_bottom,
                    (Rectangle){0.0f, 0.0f, lever_bottom.width, lever_bottom.height},
                    (Rectangle){100.0f + 260.0f, GetScreenHeight() - lever_bottom_size.y + 331.0f, lever_bottom_size.x, lever_bottom_size.y},
                    (Vector2){260.0f, 331.0f},
                    0.0f,
                    WHITE);
    // DrawCircle(c.x, c.y, 32.0f, BLACK);

    if(rotation <= -44.0f) switched_on = true;
    else switched_on = false;
    // DEBUG
    if(switched_on) DrawText("ON", 500, 500, 50, BLACK);
    else DrawText("OFF", 500, 500, 50, BLACK);

    typedef struct LogicGates {
        Rectangle rec;
        int input1;
        int input2;
        int output;
    } LogicGates;

    static LogicGates logic_gates[6];

    // Drawing the electricity source rectangle
    typedef struct E_Source{
        Rectangle rec;
        int output;
    } E_Source;

    // The main inputs of the circuit
    static E_Source e_sources[6];
    for(int i = 0; i < 6; i++){
        e_sources[i].rec = (Rectangle){
            .x = 800.0f + (i * 200),
            .y = 150.0f,
            .width = 100.0f,
            .height = 100.0f
        };
        e_sources[i].output = 0;
    }

    e_sources[0].output = 1;
    e_sources[2].output = 1;
    e_sources[3].output = 1;
    e_sources[5].output = 1;

    for(int i = 0; i < 6; i++){
        if(e_sources[i].output == 0)
            DrawRectanglePro(e_sources[i].rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, DARKGREEN);
        else if(e_sources[i].output == 1)
            DrawRectanglePro(e_sources[i].rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, GREEN);
        else
            DrawRectanglePro(e_sources[i].rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, RED);
    }

    // Initializing the logic gates placement rectangles
    for(int i = 0; i < 6; i++){
        logic_gates[i] = (LogicGates){
            .input1 = -1,
            .input2 = -1,
            .output = -1,
            .rec = (Rectangle){
                .x = 800.0f,
                .y = 350.0f,
                .width = 100.0f,
                .height = 100.0f
            }
        };
        logic_gates[i].output = -1;
    }
    logic_gates[0].rec.x = 900;
    logic_gates[1].rec.x = 1300;
    logic_gates[2].rec.x = 1700;
    logic_gates[3].rec.x = 1100;
    logic_gates[3].rec.y = 550;
    logic_gates[4].rec.x = 1500;
    logic_gates[4].rec.y = 550;
    logic_gates[5].rec.x = 1300;
    logic_gates[5].rec.y = 750;

    // Drawing the logic gates placement rectangles
    for(int i = 0; i < 6; i++){
        if(logic_gates[i].output == 0)
            DrawRectanglePro(logic_gates[i].rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, DARKGREEN);
        else if(logic_gates[i].output == 1)
            DrawRectanglePro(logic_gates[i].rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, GREEN);
        else 
            DrawRectanglePro(logic_gates[i].rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, RED);
    }

    // The main output of the circuit
    typedef struct E_Output {
        Rectangle rec;
        int input1;
        int input2;
        int output;
    } E_Output;

    E_Output e_output = {
        .rec = (Rectangle){
            .x = 1300.0f,
            .y = 920.0f,
            .width = 100.0f,
            .height = 100.0f
        },
        .input1 = -1,
        .input2 = -1,
        .output = -1
    };
    if(e_output.output == 0)
        DrawRectanglePro(e_output.rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, GRAY);
    else if(e_output.output == 1) 
        DrawRectanglePro(e_output.rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, GREEN);
    else 
        DrawRectanglePro(e_output.rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, RED);

    // If the user has clicked on the Menu button, unload the textures
    if(draw_exit_button(currentScreen)){
        UnloadTexture(lever_lever);
        UnloadTexture(lever_bottom);
        UnloadTexture(display_off);
        UnloadTexture(display_on);

        textures_loaded = false;
    }
}
