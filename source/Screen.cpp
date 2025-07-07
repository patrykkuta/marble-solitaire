#include "Screen.h"
#include "ScreenManager.h"

Screen::~Screen() {}

void Screen::mouse_button_callback_static(GLFWwindow* window, int button, int action, int mods) {
	ScreenManager::currentScreen->mouse_button_callback(window, button, action, mods);
}

void Screen::cursor_position_callback_static(GLFWwindow* window, double xpos, double ypos) {
	ScreenManager::currentScreen->cursor_position_callback(window, xpos, ypos);
}

void Screen::framebuffer_size_callback_static(GLFWwindow* window, int width, int height) {
	ScreenManager::currentScreen->framebuffer_size_callback(window, width, height);
}

void Screen::key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods) {
	ScreenManager::currentScreen->key_callback(window, key, scancode, action, mods);
}
