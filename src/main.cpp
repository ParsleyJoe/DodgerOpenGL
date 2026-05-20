#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H


#include "game.hpp"
#include "util.hpp"

bool running = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// TODO: Enemy Spawning not implemented, or the enemy class for that matter

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.Colors[ImGuiCol_WindowBg].w = 0.0f;
		style.Colors[ImGuiCol_DockingEmptyBg].w = 0.0f;
	}

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");



	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType libraray" << std::endl;
	}

	FT_Face face;
	if (FT_New_Face(ft, RESOURCES_PATH"PixelifySans.ttf", 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return -1;
	}
	FT_Set_Pixel_Sizes(face, 0, 48);
	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
	{
		std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
		return -1;
	}

	// Function to initialize global std::map characters
	InitCharacters(face);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);


	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Game Class
	Game game;
	game.Init();

	float lastFrameTime = 0.0f;
	float deltaTime = 0.0f;
	// Main Loop
	// ---------
	while (running)
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrameTime;
		lastFrameTime = currentFrame;
		glfwPollEvents();

		game.Update(window, deltaTime);

		if (glfwWindowShouldClose(window))
			running = false;
		
		glClearColor(0.0f, 0.4f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		ImGui::Begin("Debug");
		ImGui::Text("Working..");

		game.Draw();

		ImGui::End();
		ImGui::Render();
		
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
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

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
