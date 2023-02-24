#include "MenuPhase.h"
#include "engine/input/Keyboard.h"
#include "StartPhase.h"

MenuPhase::MenuPhase()
{
	hud_shader_ = new Shader("res/shaders/hud.vert", "res/shaders/hud.frag");

	hud_elements_["play"] = new HUDElement(new Texture("res/textures/menu/play.png", IMAGE), hud_shader_, -0.99f);
	hud_elements_["settings"] = new HUDElement(new Texture("res/textures/menu/settings.png", IMAGE), hud_shader_, -0.99f);
	hud_elements_["credits"] = new HUDElement(new Texture("res/textures/menu/credits.png", IMAGE), hud_shader_, -0.99f);
	hud_elements_["credits_page"] = new HUDElement(new Texture("res/textures/menu/credits_page.png", IMAGE), hud_shader_, -0.99f);
	hud_elements_["use_keyboard"] = new HUDElement(new Texture("res/textures/menu/use_keyboard.png", IMAGE), hud_shader_, -0.99f);
	hud_elements_["use_gamepad"] = new HUDElement(new Texture("res/textures/menu/use_gamepad.png", IMAGE), hud_shader_, -0.99f);
	hud_elements_["keyboard_back"] = new HUDElement(new Texture("res/textures/menu/keyboard_back.png", IMAGE), hud_shader_, -0.99f);
	hud_elements_["gamepad_back"] = new HUDElement(new Texture("res/textures/menu/gamepad_back.png", IMAGE), hud_shader_, -0.99f);

	state_ = PLAY;
}

MenuPhase::~MenuPhase()
{
	delete hud_shader_;
	for (auto obj : hud_elements_)
		delete obj.second;
}

void MenuPhase::HandleInput()
{
	Game& game = Game::GetInstance();

	static bool s_was_released = true;
	static bool w_was_released = true;
	static bool a_was_released = true;
	static bool d_was_released = true;
	static bool enter_was_released = true;

	if (Keyboard::GetKey(KEY_S) == RELEASE)
		s_was_released = true;
	if (Keyboard::GetKey(KEY_W) == RELEASE)
		w_was_released = true;
	if (Keyboard::GetKey(KEY_A) == RELEASE)
		a_was_released = true;
	if (Keyboard::GetKey(KEY_D) == RELEASE)
		d_was_released = true;
	if (Keyboard::GetKey(KEY_ENTER) == RELEASE)
		enter_was_released = true;

	switch (state_)
	{
	case PLAY:
		if (Keyboard::GetKey(KEY_S) == PRESS && s_was_released)
		{
			s_was_released = false;
			state_ = SETTINGS;
		}
		else if (Keyboard::GetKey(KEY_ENTER) == PRESS)
			game.ChangePhase(new StartPhase());
		break;
	case SETTINGS:
		if (Keyboard::GetKey(KEY_S) == PRESS && s_was_released)
		{
			s_was_released = false;
			state_ = CREDITS;
		}
		else if (Keyboard::GetKey(KEY_W) == PRESS && w_was_released)
		{
			w_was_released = false;
			state_ = PLAY;
		}
		else if (Keyboard::GetKey(KEY_ENTER) == PRESS && enter_was_released)
		{
			enter_was_released = false;
			if (game.GetDevice() == KEYBOARD_AND_MOUSE)
				state_ = USE_KEYBOARD;
			else if (game.GetDevice() == GAMEPAD)
				state_ = USE_GAMEPAD;
		}
		break;
	case CREDITS:
		if (Keyboard::GetKey(KEY_W) == PRESS && w_was_released)
		{
			w_was_released = false;
			state_ = SETTINGS;
		}
		else if (Keyboard::GetKey(KEY_ENTER) == PRESS && enter_was_released)
		{
			enter_was_released = false;
			state_ = CREDITS_PAGE;
		}
		break;
	case CREDITS_PAGE:
		if (Keyboard::GetKey(KEY_ENTER) == PRESS && enter_was_released)
		{
			enter_was_released = false;
			state_ = CREDITS;
		}
		break;
	case USE_KEYBOARD:
		if (Keyboard::GetKey(KEY_A) == PRESS && a_was_released)
		{
			a_was_released = false;
			state_ = USE_GAMEPAD;
		}
		else if (Keyboard::GetKey(KEY_D) == PRESS && d_was_released)
		{
			d_was_released = false;
			state_ = USE_GAMEPAD;
		}
		else if (Keyboard::GetKey(KEY_S) == PRESS && s_was_released)
		{
			s_was_released = false;
			state_ = KEYBOARD_BACK;
		}
		break;
	case USE_GAMEPAD:
		if (Keyboard::GetKey(KEY_A) == PRESS && a_was_released)
		{
			a_was_released = false;
			state_ = USE_KEYBOARD;
		}
		else if (Keyboard::GetKey(KEY_D) == PRESS && d_was_released)
		{
			d_was_released = false;
			state_ = USE_KEYBOARD;
		}
		else if (Keyboard::GetKey(KEY_S) == PRESS && s_was_released)
		{
			s_was_released = false;
			state_ = GAMEPAD_BACK;
		}
		break;
	case KEYBOARD_BACK:
		if (Keyboard::GetKey(KEY_W) == PRESS && w_was_released)
		{
			w_was_released = false;
			state_ = USE_KEYBOARD;
		}
		else if (Keyboard::GetKey(KEY_ENTER) == PRESS && enter_was_released)
		{
			enter_was_released = false;
			state_ = SETTINGS;
		}
		break;
	case GAMEPAD_BACK:
		if (Keyboard::GetKey(KEY_W) == PRESS && w_was_released)
		{
			w_was_released = false;
			state_ = USE_GAMEPAD;
		}
		else if (Keyboard::GetKey(KEY_ENTER) == PRESS && enter_was_released)
		{
			enter_was_released = false;
			state_ = SETTINGS;
		}
		break;
	}
}

void MenuPhase::HandlePadInput()
{
	HandleInput();
}

void MenuPhase::Update()
{
	switch (state_)
	{
	case USE_KEYBOARD:
		Game::GetInstance().SetDevice(KEYBOARD_AND_MOUSE);
		break;
	case USE_GAMEPAD:
		Game::GetInstance().SetDevice(GAMEPAD);
		break;
	}
}

void MenuPhase::Draw()
{
	switch (state_)
	{
	case PLAY:
		hud_elements_["play"]->Render();
		break;
	case SETTINGS:
		hud_elements_["settings"]->Render();
		break;
	case CREDITS:
		hud_elements_["credits"]->Render();
		break;
	case CREDITS_PAGE:
		hud_elements_["credits_page"]->Render();
		break;
	case USE_KEYBOARD:
		hud_elements_["use_keyboard"]->Render();
		break;
	case USE_GAMEPAD:
		hud_elements_["use_gamepad"]->Render();
		break;
	case KEYBOARD_BACK:
		hud_elements_["keyboard_back"]->Render();
		break;
	case GAMEPAD_BACK:
		hud_elements_["gamepad_back"]->Render();
		break;
	}
}
