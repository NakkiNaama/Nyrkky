#include "Application.h"

#include "Basics.h"
#include <fstream>
#include <sstream>

#include "Engine/Renderer.h"
#include "Engine/VertexBuffer.h"
#include "Engine/IndexBuffer.h"
#include "Engine/Render/Text.h"

#include "Engine/VertexArray.h"
#include "Engine/Shader.h"
#include "Timer.h"
#include "TextureList.h"


static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}
static void GLCheckError() {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << std::endl;
    }
}

Application::Application()
{
}

Application::~Application()
{
}

void Application::CreateWindow() {
    if (!glfwInit()) {
        std::printf("glfw init failed\n");
    }
    else std::printf("glfw init success\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window = glfwCreateWindow(GameData::GetResolutionX(), GameData::GetResolutionY(), "Nyrkky Engine - Bunker Bound", NULL, NULL);
    if (!Window)
    {
        glfwTerminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(Window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app != nullptr) {
        app->KeyPressEvent(key, scancode, action, mods);
    }
    else printf("app was nullptr");
}

static void mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app != nullptr) {
        app->MouseClickEvent(button, action, mods);
    }
    else printf("app was nullptr");
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app != nullptr) {
        app->MouseScrollEvent(xoffset, yoffset);
    }
    else printf("app was nullptr");
}

void Application::SetScreenState(bool fullScreen)
{
    if (fullScreen)
    {
        // Enter fullscreen mode
        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
        glfwSetWindowMonitor(Window, primaryMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else
    {
        // Exit fullscreen and return to windowed mode with specified dimensions
        glfwSetWindowMonitor(Window, NULL, 100, 100, 800, 600, 0);
    }
}

void Application::KeyPressEvent(int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) _pressedKeys.insert(key);
    else if (action == GLFW_RELEASE) _pressedKeys.erase(key);
}

void Application::MouseClickEvent(int button, int action, int mods)
{
    if (action == GLFW_PRESS) 
    {
        switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
        {
            _mouseInUse = true;
            LeftClick(CTRL);
        }
        break;

        case GLFW_MOUSE_BUTTON_RIGHT:
            RightClick();
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            printf("middle mouse clicked\n"); break;

        }
    }
    else if (action == GLFW_RELEASE)
    {
        switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
        {
            _mouseInUse = false;
        }
        break;

        case GLFW_MOUSE_BUTTON_RIGHT:
            RightClick();
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            printf("middle mouse clicked\n"); break;

        }
    }
}

void Application::MouseScrollEvent(double xoffset, double yoffset)
{
    if (GameData::GetUI()->GetUIView() == 0)
    {
        if (xoffset > 0) yoffset = 1;
        else if (xoffset < 0) yoffset = -1;
        GameData::GetUI()->AddTextureOffset(int(yoffset));
    }
    else
    {
        if (xoffset > 0)
        {
            if (xoffset > 0) yoffset = 1;
            else if (xoffset < 0) yoffset = -1;
            GameData::GetUI()->AddObjectOffset(int(yoffset));
        }      
    }
}

void Application::UpdateViewMatrix() {
    _view = glm::translate(glm::mat4(1.0f), glm::vec3(-GameData::GetCameraPosition(), 0.0f));
}

int Application::GetClickedTile()
{
    glm::vec2 location = ScreenToWorld();
    if (location.x >= 0 && location.y < 0)
    {
        if (GameData::GetMap() != nullptr)
        {
            int x = int(abs(location.x / GameData::GetMap()->GetTileSize()));
            int y = int(abs(location.y / GameData::GetMap()->GetTileSize()));
            if (x < GameData::GetMap()->GetGridSize() && y < GameData::GetMap()->GetGridSize())
            {
                return y * GameData::GetMap()->GetGridSize() + x;
            }
            return -1;
        }
    }
    return -1;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    // Update the projection matrix based on the new framebuffer size
    GameData::SetProj(glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f));
    GameData::GetUI()->UpdateUIOnFramebufferResize(width, height);

}

void Application::Run()
{
    CreateWindow();
    glfwSetWindowUserPointer(Window, this);
    glfwSetKeyCallback(Window, keyCallback);
    glfwSetMouseButtonCallback(Window, mouseCallback);
    glfwSetScrollCallback(Window, scroll_callback);
    InitTextureArray();
    StartGame();

    std::shared_ptr<Shader> shader = std::make_shared<Shader>("../Nyrkky/Resources/shaders/basic.shader");
    std::shared_ptr<Shader> textShader = std::make_shared<Shader>("../Nyrkky/Resources/shaders/text.shader");
    GameData::InitalizeShaders(shader, textShader);

    std::shared_ptr<Renderer> renderer;
    GameData::InitalizeRenderer(renderer);

    InitalizeGameStartingState();

    Timer timer;
    int uix, uiy;

    if (Window != nullptr) {
        while (!glfwWindowShouldClose(Window))
        {

            float deltaTime = timer.GetDeltaTime();
            HandleKeyPress(deltaTime);

            GameData::GetRenderer()->Clear();

            // -------------------------------
            UpdateViewMatrix();

            glm::mat4 mvp = GameData::GetProj() * _view;
            GameData::GetShader()->Bind();
            GameData::GetShader()->SetUniformMat4f("u_MVP", mvp);
            // -------------------------------

            HandleEntity(GameData::GetMap(), deltaTime);

            HandleEntity(GameData::GetPlayer(), deltaTime);

            for (auto& e : _textEntities)
            {
                e->view = _view;
                HandleEntity(e, deltaTime);
            }

            glfwGetFramebufferSize(Window, &uix, &uiy);
            GameData::GetUI()->UpdateUIOnFramebufferResize(uix, uiy);
            GameData::GetUI()->RenderUI(_editor);

            GLCheckError();
            glfwSwapBuffers(Window);
            glfwPollEvents();

            UpdateKeys();

        }
        glfwTerminate();
    }
}

void Application::HandleEntity(std::shared_ptr<Entity> entity, float deltaTime)
{
    entity->Tick(deltaTime);
    entity->RenderEntity();
}

void Application::UpdateKeys()
{
    CTRL = glfwGetKey(Window, GLFW_KEY_LEFT_CONTROL);
}

void Application::StartGame()
{
    printf("base start game called\n");
}

int main()
{
    Application app;
    app.Run();
    return 0;
}

void Application::InitalizeGameStartingState()
{

    glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(Window, &windowWidth, &windowHeight);
    GameData::SetProj(glm::ortho(0.0f, static_cast<float>(windowWidth), 0.0f, static_cast<float>(windowHeight), -1.0f, 1.0f));
    std::vector<uint32_t> textures;


    textures.push_back(GameData::GetCharacterTextureIndex("emily-front.png"));
    textures.push_back(GameData::GetCharacterTextureIndex("emily-right.png"));
    textures.push_back(GameData::GetCharacterTextureIndex("emily-back.png"));
    textures.push_back(GameData::GetCharacterTextureIndex("emily-left.png"));

    std::shared_ptr<CharacterEntity> mainCharacter = std::make_shared<CharacterEntity>("Emily", ECharacter::Emily, Event(EventNone, 0), 2, 2, textures);
    GameData::SetPlayer(mainCharacter);
    GameData::AddCharacter(mainCharacter);
    textures.clear();


    Event EventArisu = Event(EventTalk, 0);
    textures.push_back(GameData::GetCharacterTextureIndex("Arisu.png"));
    textures.push_back(GameData::GetCharacterTextureIndex("Arisu.png"));
    textures.push_back(GameData::GetCharacterTextureIndex("Arisu.png"));
    textures.push_back(GameData::GetCharacterTextureIndex("Arisu.png"));

    std::shared_ptr<CharacterEntity> arisu = std::make_shared<CharacterEntity>("Arisu", ECharacter::Arisu, EventArisu, 4, 4, textures);
    GameData::AddCharacter(arisu);
    textures.clear();


    std::shared_ptr<MapLoader> mapLoader = std::make_shared<MapLoader>();
    GameData::SetMapLoader(mapLoader);

    GameData::AddMap(std::make_shared<MapEntity>("Maps/Map01.xml", int(GameData::GetMaps().size())));
    GameData::GetMaps().back()->InitMap(int(GameData::GetMaps().size() - 1), true);
    
    GameData::AddMap(std::make_shared<MapEntity>("Maps/Map02.xml", int(GameData::GetMaps().size())));
    GameData::GetMaps().back()->InitMap(int(GameData::GetMaps().size() - 1));

    /* UI */
    int width, height;
    glfwGetFramebufferSize(Window, &width, &height);

    std::shared_ptr<Inventory> inv = std::make_shared<Inventory>();
    GameData::InitalizeInventory(inv);

    std::shared_ptr<UI> ui = std::make_shared<UI>(width, height);
    GameData::InitalizeUI(ui);

    std::shared_ptr<Story> story = std::make_shared<Story>();
    GameData::SetStory(story);

    /* ---------- */

    std::shared_ptr<TextEntity> textEntity = std::make_shared<TextEntity>(0, 0, 24);
    _textEntities.push_back(textEntity);

    /* camera */
    int center = GameData::GetMap()->GetGridSize() / 2 * GameData::GetMap()->GetTileSize();
    _centerOfMap = { 0, -center - (GameData::GetMap()->GetTileSize() * 8) };
    GameData::SetCameraPosition(_centerOfMap);

    mainCharacter->SetPosition(2, GameData::GetMap()->GetGridSize() / 2);

}

void Application::UpdateProjectionMatrix() {
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(Window, &windowWidth, &windowHeight);

    GameData::SetProj(glm::ortho(0.0f, static_cast<float>(windowWidth), static_cast<float>(windowHeight), 0.0f, -1.0f, 1.0f));
}

glm::vec2 Application::ScreenToWorld()
{
    double mouseX;
    double mouseY;
    glfwGetCursorPos(Window, &mouseX, &mouseY);

    int windowWidth, windowHeight;
    glfwGetFramebufferSize(Window, &windowWidth, &windowHeight);

    double normalizedX = (2.0f * mouseX / windowWidth) - 1.0f;
    double normalizedY = 1.0f - (2.0f * mouseY / windowHeight);
    glm::vec4 normalizedPositions(normalizedX, normalizedY, 0.0f, 1.0f);

    glm::mat4 inverseProjection = glm::inverse(GameData::GetProj());

    glm::vec4 worldPosition = inverseProjection * normalizedPositions;

    worldPosition /= worldPosition.w;

    glm::vec2 finalWorldPosition = glm::vec2(worldPosition);
    finalWorldPosition += GameData::GetCameraPosition();

    return finalWorldPosition;
}

void Application::LeftClick(bool ctrl)
{
    bool uiClick = false;
    if (GameData::GetUI() != nullptr)
    {
        double x, y;
        int id;
        GetClickedUIPosition(x, y);
        ClickResponse click = GameData::GetUI()->IdentifyClick(glm::vec2(x, y), id);
        switch (click)
        {
        case ENoneClick: break;
        case EGameClick:
            break;
        case EButtonClick:
            uiClick = true;
            GameData::GetStory()->ChoiceSelected(id);
            GameData::SetIsChoice(false);
            std::cout << "game button clicked" << std::endl;
            break;
        case EEditorButtonClick:
            if (_editor)
            {
                uiClick = true;
                if (id >= 0)
                {
                    if (GameData::GetUI()->GetUIView() == 0) GameData::GetUI()->SetTextureID(id);
                    else GameData::GetUI()->SetObjectID(id);
                }
            }
            break;
        case EStaticElementClick:
            uiClick = true;
            break;
        }

        if (!uiClick)
        {
            if (!_editor)
            {
                if (GameData::IsDialogVisible())
                {
                    std::cout << "click dialog" << std::endl;
                    DialogExecute();
                }
                else
                {

                    int charX, charY;
                    GameData::GetCharacter(ECharacter::Emily)->GetPosition(charX, charY);

                    std::pair<int, int> oldPos = std::pair<int, int>(charX, charY);
                    std::pair<int, int> clickedPos = GameData::IndexToCoordinate(GetClickedTile());
                   

                    int deltaX = clickedPos.first - oldPos.first;
                    int deltaY = clickedPos.second - oldPos.second;

                    Direction dir = Direction::DirNone;

                    if      (deltaY > 0) dir = Direction::Backwards;
                    else if (deltaY < 0) dir = Direction::Forward;
                    else if (deltaX > 0) dir = Direction::Right;
                    else if (deltaX < 0) dir = Direction::Left;

                    MoveMainCharacter(dir);

                    /*
                    if (_pressedKeys.count(GLFW_KEY_W)) MoveMainCharacter(Direction::Forward);
                    if (_pressedKeys.count(GLFW_KEY_D)) MoveMainCharacter(Direction::Right);
                    if (_pressedKeys.count(GLFW_KEY_S)) MoveMainCharacter(Direction::Backwards);
                    if (_pressedKeys.count(GLFW_KEY_A)) MoveMainCharacter(Direction::Left);
                    */
                }
            }
            else
            {
                if (GameData::IsDialogVisible()) return;
                int tile = GetClickedTile();
                if (tile != -1)
                {
                    if (GameData::GetUI()->GetUIView() == 0)
                    {
                        if (!ctrl) GameData::GetMap()->ChangeTile(GameData::GetUI()->GetLayer(), tile, GameData::GetUI()->GetTextureID(), GameData::GetUI()->GetIsSolid());
                        else GameData::GetMap()->ResetTile(tile, GameData::GetUI()->GetLayer());
                    }
                    else
                    {
                        std::cout << GameData::GetUI()->GetObjectName() << std::endl;
                        GameData::GetMap()->SpawnTileEntity(GameData::GetUI()->GetObjectName(), tile);
                    }
                }
            }
        }
    }
    else std::cout << "ui was nullptr!" << std::endl;
}

void Application::RightClick()
{

}

void Application::ChangeOffset(int offset, bool cursorPosCheck)
{
    bool valid = true;
    if (cursorPosCheck)
    {
        double x, y;
        GetClickedUIPosition(x, y);
        valid = GameData::GetUI()->IsHoveringEditorUI(glm::vec2(x, y));
    }
    if (valid)
    {
        if (GameData::GetUI()->GetUIView() == 0)
        {
            GameData::GetUI()->AddTextureOffset(offset);
        }
        else
        {
            GameData::GetUI()->AddObjectOffset(offset);
        }
    }
}

void Application::HandleKeyPress(float DeltaTime)
{
    if (!_mouseInUse)
    {
        if (!GameData::IsDialogVisible())
        {
            if (_pressedKeys.count(GLFW_KEY_UP)) MoveCamera(0);
            if (_pressedKeys.count(GLFW_KEY_RIGHT)) MoveCamera(1);
            if (_pressedKeys.count(GLFW_KEY_DOWN)) MoveCamera(2);
            if (_pressedKeys.count(GLFW_KEY_LEFT)) MoveCamera(3);

            MoveMainCharacter(Direction::DirNone);
            if (_pressedKeys.count(GLFW_KEY_W)) MoveMainCharacter(Direction::Forward);
            if (_pressedKeys.count(GLFW_KEY_D)) MoveMainCharacter(Direction::Right);
            if (_pressedKeys.count(GLFW_KEY_S)) MoveMainCharacter(Direction::Backwards);
            if (_pressedKeys.count(GLFW_KEY_A)) MoveMainCharacter(Direction::Left);

            StaticDelayPress(DeltaTime);
        }
        else
        {
            StaticDelayPressDialog(DeltaTime);
        }
    }
}

void Application::StaticDelayPress(float DeltaTime)
{
    _staticDelayTimer += DeltaTime;

    if (_staticDelayTimer > 0.5)
    {

        if (_pressedKeys.count(GLFW_KEY_E))
        {
            InteractWithObject();
            _staticDelayTimer = 0;
        }

        if (_pressedKeys.count(GLFW_KEY_P))
        {
            GameData::GetInventory()->AddItem(EKey);
            _staticDelayTimer = 0;
        }

        if (_pressedKeys.count(GLFW_KEY_J))
        {
            GameData::ChangeMap(1);
            _staticDelayTimer = 0;
        }

        if (_pressedKeys.count(GLFW_KEY_K))
        {
            GameData::ChangeMap(0);
            _staticDelayTimer = 0;
        }

        if (_pressedKeys.count(GLFW_KEY_Q))
        {
            if (glfwGetKey(Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            {
                _staticDelayTimer = 0;
                glfwSetWindowShouldClose(Window, GLFW_TRUE);
            }
        }

        if (_pressedKeys.count(GLFW_KEY_T))
        {
            if (_editor)
            {
                std::cout << "t" << std::endl;
                SaveMap();
                _staticDelayTimer = 0;
            }
        }

        if (_pressedKeys.count(GLFW_KEY_F11))
        {
            _fullScreen = !_fullScreen;
            SetScreenState(_fullScreen);
            std::cout << "full screen state change" << std::endl;
            _staticDelayTimer = 0;
        }

        if (_pressedKeys.count(GLFW_KEY_F10))
        {
            _editor = !_editor;
            std::cout << "editor state change" << std::endl;
            _staticDelayTimer = 0;
        }

        if (_pressedKeys.count(GLFW_KEY_KP_ADD))
        {
            ChangeOffset(1, false);
            _staticDelayTimer = 0;
        }

        if (_pressedKeys.count(GLFW_KEY_KP_SUBTRACT))
        {
            ChangeOffset(-1, false);
            _staticDelayTimer = 0;
        }

    }
}

void Application::StaticDelayPressDialog(float DeltaTime)
{
    _staticDelayTimer += DeltaTime;

    if (_staticDelayTimer > 0.5)
    {
        if (_pressedKeys.count(GLFW_KEY_ENTER) || _pressedKeys.count(GLFW_KEY_E))
        {
            _staticDelayTimer = 0;
            DialogExecute();
        }
    }
}

void Application::DialogExecute()
{
    if (!GameData::GetStory()->ProceedLine())
    {
        if (!GameData::IsChoice())
        {
            bool hasNext = GameData::GetStory()->HasNextNode();
            if (hasNext)
            {
                GameData::GetStory()->NextNode();
            }
            else
            {
                if (GameData::GetStory()->currentNode->choices.size() > 0)
                {
                    GameData::SetIsChoice(true);
                }
                else
                {
                    GameData::GetStory()->FinishChain();
                    GameData::SetDialogVisible(false);
                }
            }

        }
        else std::cout << "press ignored!" << std::endl;

    }
}


