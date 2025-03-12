#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "mine_sweeper.hpp"
#include "mine_sweeper_constants.hpp"
#include "util.hpp"
#include "log.hpp"

#include "app.hpp"

namespace app
{

// GUI

void mainMenuBar()
{
    static bool initMenu = true;
    static char difficultyStr[Difficulty::strSize];
    static Difficulty::DifficultyEnum difficulty = Difficulty::BEGINNER;

    static char allowedSeedStr[AllowedSeeds::strSize];
    static AllowedSeeds::AllowedSeedsEnum allowedSeeds = AllowedSeeds::ALLOW_ALL_SEEDS;

    static char firstClickStr[FirstClick::strSize];
    static FirstClick::FirstClickEnum firstClick = FirstClick::_3X3_AREA;
    if (initMenu)
    {
        strcpy(difficultyStr, Difficulty::beginnerStr);
        strcpy(allowedSeedStr, AllowedSeeds::allowAllSeedsStr);
        strcpy(firstClickStr, FirstClick::_3x3AreaStr);
        initMenu = false;
    }
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu(difficultyStr))
    {
        bool helper = difficulty == Difficulty::BEGINNER;
        if (ImGui::MenuItem(Difficulty::beginnerStr, "", &helper)) 
        {
            strcpy(difficultyStr, Difficulty::beginnerStr);
            difficulty = Difficulty::BEGINNER;
        }
        helper = difficulty == Difficulty::INTERMEDIATE;
        if (ImGui::MenuItem(Difficulty::intermediateStr, "", &helper)) 
        { 
            strcpy(difficultyStr, Difficulty::intermediateStr);
            difficulty = Difficulty::INTERMEDIATE;
        }
        helper = difficulty == Difficulty::EXPERT;
        if (ImGui::MenuItem(Difficulty::expertStr, "", &helper)) 
        {
            strcpy(difficultyStr, Difficulty::expertStr);
            difficulty = Difficulty::EXPERT;
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu(allowedSeedStr))
    {
        bool helper = allowedSeeds == AllowedSeeds::ONLY_100_PERCENT_AND_0_PERCENT;
        if (ImGui::MenuItem(AllowedSeeds::only100PercentAnd0PercentStr, "", &helper)) 
        {
            strcpy(allowedSeedStr, AllowedSeeds::only100PercentAnd0PercentStr);
            allowedSeeds = AllowedSeeds::ONLY_100_PERCENT_AND_0_PERCENT;
        }
        helper = allowedSeeds == AllowedSeeds::HIGHEST_PROB_IS_BOMB;
        if (ImGui::MenuItem(AllowedSeeds::highestProbIsBombStr, "", &helper)) 
        { 
            strcpy(allowedSeedStr, AllowedSeeds::highestProbIsBombStr);
            allowedSeeds = AllowedSeeds::HIGHEST_PROB_IS_BOMB;
        }
        helper = allowedSeeds == AllowedSeeds::ALLOW_ALL_SEEDS;
        if (ImGui::MenuItem(AllowedSeeds::allowAllSeedsStr, "", &helper)) 
        {
            strcpy(allowedSeedStr, AllowedSeeds::allowAllSeedsStr);
            allowedSeeds = AllowedSeeds::ALLOW_ALL_SEEDS;
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu(firstClickStr))
    {
        bool helper = firstClick == FirstClick::_3X3_AREA;
        if (ImGui::MenuItem(FirstClick::_3x3AreaStr, "", &helper)) 
        {
            strcpy(firstClickStr, FirstClick::_3x3AreaStr);
            firstClick = FirstClick::_3X3_AREA;
        }
        helper = firstClick == FirstClick::_1X1_AREA;
        if (ImGui::MenuItem(FirstClick::_1x1AreaStr, "", &helper)) 
        { 
            strcpy(firstClickStr, FirstClick::_1x1AreaStr);
            firstClick = FirstClick::_1X1_AREA;
        }
        helper = firstClick == FirstClick::_0X0_AREA;
        if (ImGui::MenuItem(FirstClick::_0x0AreaStr, "", &helper)) 
        {
            strcpy(firstClickStr, FirstClick::_0x0AreaStr);
            firstClick = FirstClick::_0X0_AREA;
        }
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
}

void runInGUI()
{
    glfwInit();
#ifdef __APPLE__
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    LOG_INFO("LAUNCHED WINDOW");
    if (window == nullptr)
    {
        LOG_ERROR("FAILED TO OPEN WINDOW");
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // UI
        mainMenuBar();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
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