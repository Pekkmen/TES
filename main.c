#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "src/raygui.h"
#include <math.h>

#define AND 0
#define OR 1
#define NAND 2
#define NOR 3
#define XOR 4
#define XNOR 5

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen {TITLE, LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_4, LEVEL_5, ENDING } GameScreen;
typedef struct LogicGates {
    Rectangle rec;
    int input1;
    Vector2 input1_pos;
    int input2;
    Vector2 input2_pos;
    int output;
    Vector2 output_pos;
} LogicGates;
typedef struct Wire {
    int status;
    Vector2 input_pos;
    Vector2 output_pos;
} Wire;

void draw_level_buttons(GameScreen*, int, bool *);
bool draw_exit_button(GameScreen *);
bool draw_level_1(GameScreen *);
void change_logic_values(LogicGates *, int, int, Wire *);
void reset_logic_value(LogicGates  *);

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
                    DrawText("1 PÁLYA", 1200, 10, 60, MAROON);
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
    typedef struct E_Source{
        Rectangle rec;
        int output;
        Vector2 output_pos;
    } E_Source;

    // The main output of the circuit
    typedef struct E_Output {
        Rectangle rec;
        int input;
        Vector2 input_pos;
        int output;
        Vector2 output_pos;
    } E_Output;

    static bool textures_loaded = false;
    static bool uninitialized = true;
    static bool electricity = false, switched_on = false;
    static Texture2D lever_lever, lever_bottom, display_off, display_on, lg[6];
    // The main inputs of the circuit
    static E_Source e_sources[6];
    static LogicGates logic_gates[6];
    static Wire wires[13];
    static Rectangle logic_gates_recs[6], logic_gates_recs_original[6];
    static Rectangle logic_gates_src = (Rectangle){
        .x = 0.0f,
        .y = 0.0f,
        .width = 855.0f,
        .height = 1295.0f
    };
    static E_Output e_output = {
        .rec = (Rectangle){
            .x = 500.0f,
            .y = 1040.0f,
            .width = 100.0f,
            .height = 100.0f
        },
        .input = -1,
        .output = -1,
        .input_pos.x = 550.0f,
        .input_pos.y = 1040.0f,
        .output_pos.x = 550.0f,
        .output_pos.y = 1090.0f
    };
    // DEBUG
    static int asd, wire_1, wire_2, wire_1_status, wire_2_status, lg_output;

    // Loading textures
    if(!textures_loaded){
        lever_lever = LoadTexture("assets/level_1/lever_lever.png");
        lever_bottom = LoadTexture("assets/level_1/lever_bottom.png");
        display_off = LoadTexture("assets/level_1/on_off_display_OFF.png");
        display_on = LoadTexture("assets/level_1/on_off_display_ON.png");
        for(int i = 0; i < 6; i++){
            lg[i] = LoadTexture(TextFormat("assets/level_1/lg_%d.png", i));
        }

        textures_loaded = true;
    }
    if(uninitialized){
        for(int i = 0; i < 6; i++){
            logic_gates_recs[i] = (Rectangle){
                .x = 150.0f * i + 50,
                .y = 10.0f,
                .width = 80.0f,
                .height = 100.0f
            };
            logic_gates_recs_original[i] = logic_gates_recs[i];
        }

        for(int i = 0; i < 6; i++){
            e_sources[i].rec = (Rectangle){
                .x = 800.0f + (i * 200),
                .y = 150.0f,
                .width = 100.0f,
                .height = 100.0f
            };
            e_sources[i].output = 0;
            e_sources[i].output_pos = (Vector2){
                .x = e_sources[i].rec.x + e_sources[i].rec.width/2,
                .y = e_sources[i].rec.y + e_sources[i].rec.height
            };
        }
        e_sources[0].output = 1;
        e_sources[2].output = 1;
        e_sources[3].output = 1;
        e_sources[5].output = 1;

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
                },
            };
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
        for(int i = 0; i < 6; i++){
            logic_gates[i].input1_pos.x = logic_gates[i].rec.x + logic_gates[i].rec.width/3;
            logic_gates[i].input1_pos.y = logic_gates[i].rec.y;
            logic_gates[i].input2_pos.x = logic_gates[i].rec.x + 2*logic_gates[i].rec.width/3;
            logic_gates[i].input2_pos.y = logic_gates[i].rec.y;
            logic_gates[i].output_pos.x = logic_gates[i].rec.x + logic_gates[i].rec.width/2;
            logic_gates[i].output_pos.y = logic_gates[i].rec.y + logic_gates[i].rec.height;
        }

        // Connecting and setting up the status of the wires connecting the first row of logic gates
        for(int i = 0; i < 13; i++){
            wires[i].status = -1;
        }
        for(int i = 0; i < 6; i += 2) {
            // Determine the index of the logic gate
            int gate_index = i/2; 

            // First wire of the pair
            wires[i].input_pos.x = e_sources[i].output_pos.x;
            wires[i].input_pos.y = e_sources[i].output_pos.y;
            wires[i].output_pos.x = logic_gates[gate_index].input1_pos.x;
            wires[i].output_pos.y = logic_gates[gate_index].input1_pos.y;
            wires[i].status = e_sources[i].output;

            // Second wire of the pair
            wires[i+1].input_pos.x = e_sources[i+1].output_pos.x;
            wires[i+1].input_pos.y = e_sources[i+1].output_pos.y;
            wires[i+1].output_pos.x = logic_gates[gate_index].input2_pos.x;
            wires[i+1].output_pos.y = logic_gates[gate_index].input2_pos.y;
            wires[i+1].status = e_sources[i+1].output;
        }
        // Ugly as hell boilerplate
        wires[6].input_pos.x = logic_gates[0].output_pos.x;
        wires[6].input_pos.y = logic_gates[0].output_pos.y;
        wires[6].output_pos.x = logic_gates[3].input1_pos.x;
        wires[6].output_pos.y = logic_gates[3].input1_pos.y;
        wires[7].input_pos.x = logic_gates[1].output_pos.x;
        wires[7].input_pos.y = logic_gates[1].output_pos.y;
        wires[7].output_pos.x = logic_gates[3].input2_pos.x;
        wires[7].output_pos.y = logic_gates[3].input2_pos.y;
        

        wires[8].input_pos.x = logic_gates[1].output_pos.x;
        wires[8].input_pos.y = logic_gates[1].output_pos.y;
        wires[8].output_pos.x = logic_gates[4].input1_pos.x;
        wires[8].output_pos.y = logic_gates[4].input1_pos.y;
        wires[9].input_pos.x = logic_gates[2].output_pos.x;
        wires[9].input_pos.y = logic_gates[2].output_pos.y;
        wires[9].output_pos.x = logic_gates[4].input2_pos.x;
        wires[9].output_pos.y = logic_gates[4].input2_pos.y;

        wires[10].input_pos.x = logic_gates[3].output_pos.x;
        wires[10].input_pos.y = logic_gates[3].output_pos.y;
        wires[10].output_pos.x = logic_gates[5].input1_pos.x;
        wires[10].output_pos.y = logic_gates[5].input1_pos.y;
        wires[11].input_pos.x = logic_gates[4].output_pos.x;
        wires[11].input_pos.y = logic_gates[4].output_pos.y;
        wires[11].output_pos.x = logic_gates[5].input2_pos.x;
        wires[11].output_pos.y = logic_gates[5].input2_pos.y;

        wires[12].input_pos.x = logic_gates[5].output_pos.x;
        wires[12].input_pos.y = logic_gates[5].output_pos.y;
        wires[12].output_pos.x = e_output.input_pos.x;
        wires[12].output_pos.y = e_output.input_pos.y;

        // DEBUG
        asd = -10, wire_1 = -10, wire_2 = -10, wire_1_status = -10, wire_2_status = -10, lg_output = -10;

        uninitialized = false;
    }
    wires[6].status = logic_gates[0].output;
    wires[7].status = logic_gates[1].output;
    wires[8].status = logic_gates[1].output;
    wires[9].status = logic_gates[2].output;
    wires[10].status = logic_gates[3].output;
    wires[11].status = logic_gates[4].output;
    wires[12].status = e_output.output;
    // DEBUG
    if(IsKeyPressed(KEY_S)) electricity = !electricity;

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

    if(rotation <= -44.0f) switched_on = true;
    else switched_on = false;
    // DEBUG
    if(switched_on) DrawText("ON", 500, 500, 50, BLACK);
    else DrawText("OFF", 500, 500, 50, BLACK);

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


    int moved_gate_index = -1;
    Vector2 pos = GetMousePosition();
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) DrawText(TextFormat("%.0f, %.0f", pos.x, pos.y), 600, 600, 60, BLACK);
    // Check for clicks on the logic gates
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        for(int i = 0; i < 6; i++){
            if(CheckCollisionPointRec(pos, logic_gates_recs[i])){
                logic_gates_recs[i].x = pos.x - 30;
                logic_gates_recs[i].y = pos.y - 30;
                break;
            }
        }
    } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
        for (int i = 0; i < 6; i++) {
            bool gate_moved = false;
            for (int j = 0; j < 6; j++) {
                moved_gate_index = j;
                // Check if any logic gate collides with any logic gate placeholder and check that the actual placeholder is free
                if(CheckCollisionRecs(logic_gates_recs[i], logic_gates[j].rec) && logic_gates[j].output == -1) {
                    logic_gates_recs[i] = logic_gates[j].rec;
                    gate_moved = true;
                    moved_gate_index = -1;
                    wire_1 = 2*j;
                    wire_2 = 2*j+1;
                    wire_1_status = wires[wire_1].status;
                    wire_2_status = wires[wire_2].status;
                    lg_output = logic_gates[j].output;
                    change_logic_values(&logic_gates[j], j, i, wires);
                    asd = logic_gates[j].output;
                    break;
                }
            }
            // If not, place it back to its original position
            if(!gate_moved && moved_gate_index != -1){
                reset_logic_value(&logic_gates[moved_gate_index]);
                logic_gates_recs[i] = logic_gates_recs_original[i];
            } 
        }
    }
    // DEBUG
    DrawText(TextFormat("%d, wire1: %d, wire2: %d\n\n\nwire1_status: %d, wire2_status: %d, lg_output: %d", asd, wire_1, wire_2, wire_1_status, wire_2_status, lg_output), 0, 0, 50, BLACK);

    // Draw the wires
    for(int i = 0; i < 13; i++){
        if(wires[i].status == -1){
            DrawLineBezier(wires[i].input_pos, wires[i].output_pos, 5, RED);
        } else if(wires[i].status == 0){
            DrawLineBezier(wires[i].input_pos, wires[i].output_pos, 5, DARKGREEN);
        } else if(wires[i].status == 1){
            DrawLineBezier(wires[i].input_pos, wires[i].output_pos, 5, GREEN);
        }
    }
    for(int i = 0; i < 6; i++){
        if(e_sources[i].output == 0)
            DrawRectanglePro(e_sources[i].rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, DARKGREEN);
        else if(e_sources[i].output == 1)
            DrawRectanglePro(e_sources[i].rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, GREEN);
        else
            DrawRectanglePro(e_sources[i].rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, RED);
    }
    // Drawing the logic gates placement rectangles
    for(int i = 0; i < 6; i++){
        if(logic_gates[i].output == 0)
            DrawRectanglePro(logic_gates[i].rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, DARKGREEN);
        else if(logic_gates[i].output == 1)
            DrawRectanglePro(logic_gates[i].rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, GREEN);
        else if(logic_gates[i].output == -1)
            DrawRectanglePro(logic_gates[i].rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, RED);
    }

    if(e_output.output == 0)
        DrawRectanglePro(e_output.rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, GRAY);
    else if(e_output.output == 1) 
        DrawRectanglePro(e_output.rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, GREEN);
    else if(e_output.output == -1)
        DrawRectanglePro(e_output.rec, (Vector2){.x=0.0f, .y=0.0f}, 0.0f, RED);

    // Draw the logic gates 
    for(int i = 0; i < 6; i++){
        DrawTexturePro(lg[i], logic_gates_src, logic_gates_recs[i], (Vector2){.x=0,.y=0}, 0, WHITE);
    }

    // If the user has clicked on the Menu button, unload the textures
    if(draw_exit_button(currentScreen)){
        UnloadTexture(lever_lever);
        UnloadTexture(lever_bottom);
        UnloadTexture(display_off);
        UnloadTexture(display_on);
        for(int i = 0; i < 6; i++){
            UnloadTexture(lg[i]);
        }

        textures_loaded = false;
    }
}

void change_logic_values(LogicGates *logic_gate, int index, int logic_value, Wire *wires){
    switch (logic_value)
    {
    case AND:
        if(wires[2*index].status == 1 && wires[2*index+1].status == 1) logic_gate->output = 1;
        else if(wires[2*index].status == -1 || wires[2*index+1].status == -1) logic_gate->output = -1;
        else if(wires[2*index].status == 0 || wires[2*index+1].status == 0)logic_gate->output = 0;
        break;

    case OR:
        if(wires[2*index].status == 1 || wires[2*index+1].status == 1) logic_gate->output = 1;
        else if(wires[2*index].status == -1 || wires[2*index+1].status == -1) logic_gate->output = -1;
        else if(wires[2*index].status == 0 && wires[2*index+1].status == 0)logic_gate->output = 0;
        break;

    case NAND:
        if(wires[2*index].status == 1 && wires[2*index+1].status == 1) logic_gate->output = 0;
        else if(wires[2*index].status == -1 || wires[2*index+1].status == -1) logic_gate->output = -1;
        else if(wires[2*index].status == 0 || wires[2*index+1].status == 0)logic_gate->output = 1;
        break;

    case NOR:
        if(wires[2*index].status == 1 || wires[2*index+1].status == 1) logic_gate->output = 0;
        else if(wires[2*index].status == -1 || wires[2*index+1].status == -1) logic_gate->output = -1;
        else if(wires[2*index].status == 0 && wires[2*index+1].status == 0)logic_gate->output = 1;
        break;

    case XOR:
        if(wires[2*index].status == -1 || wires[2*index+1].status == -1) logic_gate->output = -1;
        else if(wires[2*index].status == wires[2*index+1].status) logic_gate->output = 0;
        else logic_gate->output = 1;
        break;

    case XNOR:
        if(wires[2*index].status == -1 || wires[2*index+1].status == -1) logic_gate->output = -1;
        else if(wires[2*index].status == wires[2*index+1].status) logic_gate->output = 1;
        else logic_gate->output = 0;
        break;
    
    default:
        break;
    }
}

void reset_logic_value(LogicGates *logic_gate){
    logic_gate->output = -1;
}
