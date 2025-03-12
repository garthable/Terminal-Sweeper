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
    ImGuiIO& io = ImGui::GetIO(); (void)io;
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
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
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

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

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