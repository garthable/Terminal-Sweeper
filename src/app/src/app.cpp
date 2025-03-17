#include "mine_sweeper.hpp"
#include "mine_sweeper_constants.hpp"
#include "util.hpp"
#include "log.hpp"

#include "app.hpp"

#include <iostream>
#define CLAY_IMPLEMENTATION
#include "clay.h"
#include "clay_renderer_raylib.c"

namespace app
{

const Clay_Color COLOR_LIGHT = (Clay_Color) {224, 215, 210, 255};
const Clay_Color COLOR_RED = (Clay_Color) {168, 66, 28, 255};
const Clay_Color COLOR_ORANGE = (Clay_Color) {225, 138, 50, 255};

void HandleClayErrors(Clay_ErrorData errorData) {
    // See the Clay_ErrorData struct for more information
    printf("%s", errorData.errorText.chars);
    switch(errorData.errorType) {
        // etc
    }
}

// Example measure text function
static inline Clay_Dimensions MeasureText(Clay_StringSlice text, Clay_TextElementConfig *config, uintptr_t userData) {
    // Clay_TextElementConfig contains members such as fontId, fontSize, letterSpacing etc
    // Note: Clay_String->chars is not guaranteed to be null terminated
    return (Clay_Dimensions) {
            .width = text.length * config->fontSize, // <- this will only work for monospace fonts, see the renderers/ directory for more advanced text measurement
            .height = config->fontSize
    };
}

// Layout config is just a struct that can be declared statically, or inline
Clay_ElementDeclaration sidebarItemConfig = (Clay_ElementDeclaration) {
    .layout = {
        .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(50) }
    },
    .backgroundColor = COLOR_ORANGE
};

// Re-useable components are just normal functions
void SidebarItemComponent() {
    CLAY(sidebarItemConfig) {
        // children go here...
    }
}

// GUI
void runInGUI()
{
    // Note: malloc is only used here as an example, any allocator that provides
    // a pointer to addressable memory of at least totalMemorySize will work
    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));

    auto screenWidth = GetScreenWidth();
    auto screenHeight = GetScreenHeight();

    // Note: screenWidth and screenHeight will need to come from your environment, Clay doesn't handle window related tasks
    Clay_Initialize(arena, (Clay_Dimensions) { screenWidth, screenHeight }, (Clay_ErrorHandler) { HandleClayErrors });

    while(!WindowShouldClose()) { // Will be different for each renderer / environment

        auto mousePositionX = GetMouseX();
        auto mousePositionY = GetMouseY();
        auto isMouseDown = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        auto mouseWheel = GetMouseWheelMoveV();
        auto mouseWheelX = mouseWheel.x;
        auto mouseWheelY = mouseWheel.y;
        auto deltaTime = GetFrameTime();

        // Optional: Update internal layout dimensions to support resizing
        Clay_SetLayoutDimensions((Clay_Dimensions) { screenWidth, screenHeight });
        // Optional: Update internal pointer position for handling mouseover / click / touch events - needed for scrolling & debug tools
        Clay_SetPointerState((Clay_Vector2) { mousePositionX, mousePositionY }, isMouseDown);
        // Optional: Update internal pointer position for handling mouseover / click / touch events - needed for scrolling and debug tools
        Clay_UpdateScrollContainers(true, (Clay_Vector2) { mouseWheelX, mouseWheelY }, deltaTime);

        // All clay layouts are declared between Clay_BeginLayout and Clay_EndLayout
        Clay_BeginLayout();

        // An example of laying out a UI with a fixed width sidebar and flexible width main content
        CLAY({ .id = CLAY_ID("OuterContainer"), .layout = { .sizing = {CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0)}, .padding = CLAY_PADDING_ALL(16), .childGap = 16 }, .backgroundColor = {250,250,255,255} }) {
            CLAY({
                .id = CLAY_ID("SideBar"),
                .layout = 
                { 
                    .layoutDirection = CLAY_TOP_TO_BOTTOM, 
                    .sizing = 
                    { 
                        .width = CLAY_SIZING_FIXED(300), 
                        .height = CLAY_SIZING_GROW(0) 
                    }, 
                    .padding = CLAY_PADDING_ALL(16), 
                    .childGap = 16 
                },
                .backgroundColor = COLOR_LIGHT
            }) {
                CLAY({ .id = CLAY_ID("ProfilePictureOuter"), .layout = { .sizing = { .width = CLAY_SIZING_GROW(0) }, .padding = CLAY_PADDING_ALL(16), .childGap = 16, .childAlignment = { .y = CLAY_ALIGN_Y_CENTER } }, .backgroundColor = COLOR_RED }) {
                    CLAY({ .id = CLAY_ID("ProfilePicture"), .layout = { .sizing = { .width = CLAY_SIZING_FIXED(60), .height = CLAY_SIZING_FIXED(60) }}, .image = { .imageData = &profilePicture, .sourceDimensions = {60, 60} } }) {}
                    CLAY_TEXT(CLAY_STRING("Clay - UI Library"), CLAY_TEXT_CONFIG({ .fontSize = 24, .textColor = {255, 255, 255, 255} }));
                }

                // Standard C code like loops etc work inside components
                for (int i = 0; i < 5; i++) {
                    SidebarItemComponent();
                }

                CLAY({ .id = CLAY_ID("MainContent"), .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) } }, .backgroundColor = COLOR_LIGHT }) {}
            }
        }

        // All clay layouts are declared between Clay_BeginLayout and Clay_EndLayout
        Clay_RenderCommandArray renderCommands = Clay_EndLayout();

        // More comprehensive rendering examples can be found in the renderers/ directory
        for (int i = 0; i < renderCommands.length; i++) {
            Clay_RenderCommand *renderCommand = &renderCommands.internalArray[i];

            switch (renderCommand->commandType) {
                case CLAY_RENDER_COMMAND_TYPE_RECTANGLE: {
                    DrawRectangle( renderCommand->boundingBox, renderCommand->renderData.rectangle.backgroundColor);
                }
                // ... Implement handling of other command types
            }
        }
    }
}

// Terminal

void getWidthHeightBombCountTerminal(mswp::BoardWidth& outWidth, mswp::BoardHeight& outHeight, mswp::BombCount& outBombCount)
{
    while(true)
    {
        std::cout << "Select Difficulty: \
            \n\t1: Beginner \
            \n\t2: Intermediate \
            \n\t3: Expert\n";
        
        std::string input;
        getline(std::cin, input);
        uint8_t difficulty = std::stoi(input);

        switch (difficulty)
        {
        case 1:
            outWidth = MSWP_BEGINNER_WIDTH;
            outHeight = MSWP_BEGINNER_HEIGHT;
            outBombCount = MSWP_BEGINNER_BOMB_COUNT;
            return;
        case 2:
            outWidth = MSWP_INTERMEDIATE_WIDTH;
            outHeight = MSWP_INTERMEDIATE_HEIGHT;
            outBombCount = MSWP_INTERMEDIATE_BOMB_COUNT;
            return;
        case 3:
            outWidth = MSWP_EXPERT_WIDTH;
            outHeight = MSWP_EXPERT_HEIGHT;
            outBombCount = MSWP_EXPERT_BOMB_COUNT;
            return;
        
        default:
            break;
        }
        std::cout << "\"" << input << "\" is not a valid input!\n";
    }
}
struct Action
{
    enum Actions : uint8_t
    {
        FLAG,
        CLICK
    };
};

void getActionAndPositionTerminal(mswp::BoardWidth width, mswp::BoardHeight height, mswp::BoardXPos& xPos, mswp::BoardYPos& yPos, Action::Actions& action)
{
    while (true)
    {
        std::cout << "Enter Action and Position: (c/f) <row> <col>\n";
        std::string line;

        getline(std::cin, line);
        if (line.size() != 5)
        {
            std::cout << "Input is incorrect size!\n";
            continue;
        }

        xPos = util::letterToUI8(line[4]);
        if (xPos == 255)
        {
            std::cout << "\'" << line[4] << "\' is invalid!\n";
            continue;
        }
        if (xPos >= width)
        {
            std::cout << "\'" << static_cast<int>(xPos) << "\' is larger than width!\n";
            continue;
        }

        yPos = util::letterToUI8(line[2]);
        if (yPos == 255)
        {
            std::cout << "\'" << line[2] << "\' is invalid!\n";
            continue;
        }
        if (yPos >= height)
        {
            std::cout << "\'" << static_cast<int>(yPos) << "\' is larger than height!\n";
            continue;
        }

        action = line[0] == 'c' ? Action::CLICK : Action::FLAG;
        break;
    }
}
bool shouldExitTerminal()
{
    while (true)
    {
        std::cout << "Play another game? (Y/n)\n";
        std::string input;
        getline(std::cin, input);
    
        char firstLetter = tolower(input[0]);
        if (firstLetter == 'y')
        {
            return true;
        }
        else if (firstLetter == 'n')
        {
            return false;
        }
        std::cout << "\"" << input << "\"" << " is an invalid input!\n";
    }
}
void runInTerminal()
{
    do
    {
        mswp::BoardWidth width;
        mswp::BoardHeight height;
        mswp::BombCount bombCount;
        getWidthHeightBombCountTerminal(width, height, bombCount);
    
        mswp::MineSweeper board(width, height, bombCount, time(0));
    
        while(true)
        {
            std::cout << "Flags: " << static_cast<int>(board.flagsRemaining()) << "\n";
            std::cout << "Remaining Tiles: " << static_cast<int>(board.remainingTile()) << "\n";
            std::cout << board;

            mswp::BoardXPos xPos;
            mswp::BoardYPos yPos;
            Action::Actions action;
            getActionAndPositionTerminal(width, height, xPos, yPos, action);

            if (action == Action::CLICK)
            {
                bool res = board.click(xPos, yPos);
                if (res)
                {
                    break;
                }
            }
            else
            {
                bool res = board.flag(xPos, yPos);
            }
        }
        
        std::cout << "Flags: " << static_cast<int>(board.flagsRemaining()) << "\n";
        std::cout << "Remaining Tiles: " << static_cast<int>(board.remainingTile()) << "\n";
        std::cout << board;
        if (board.gameState() == mswp::MineSweeper::WON)
        {
            std::cout << "WON\n";
        }
        else
        {
            std::cout << "LOST\n";
        }
    } while(shouldExitTerminal());
}

} // app end