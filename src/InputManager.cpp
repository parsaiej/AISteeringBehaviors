#include "InputManager.h"
#include "KinematicUnitManager.h"

InputManager::InputManager()
{
	mp_eventque = NULL;
}

InputManager::~InputManager()
{
	al_destroy_event_queue(mp_eventque);
}

void InputManager::init()
{
	mp_eventque = al_create_event_queue();

	if (!mp_eventque)
	{
		std::cout << "The event queue did not create successfully." << std::endl;
		return;
	}

	//show the mouse
	if (!al_hide_mouse_cursor(GRAPHICS_SYSTEM->getDisplay()))
	{
		printf("Mouse cursor not able to be hidden!\n");
		return;
	}

	if (!al_install_mouse())
	{
		std::cout << "Failed to initialize the mouse!\n";
		return;
	}

	if (!al_install_keyboard())
	{
		std::cout << "Failed to initialize the keyboard!\n";
	}

	al_register_event_source(mp_eventque, al_get_display_event_source(GRAPHICS_SYSTEM->getDisplay()));
	al_register_event_source(mp_eventque, al_get_mouse_event_source());
	al_register_event_source(mp_eventque, al_get_keyboard_event_source());
}

void InputManager::update()
{
	//###############MOUSE RUNTIME EVENTS##############
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	MESSAGE_MANAGER->addMessage(new CoordinatesFollowMouseMessage(mouseState), 0);
	//#################################################

	//###############MOUSE/KEY DOWN EVENTS########################
	if(isMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		MESSAGE_MANAGER->addMessage( new PlayerMoveToMessage(Vector2D(mouseState.x, mouseState.y)), 0 );
	}
	if (isMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
	}

	if (isKeyboardKeyDown(ALLEGRO_KEY_1))
	{
		MESSAGE_MANAGER->addMessage(new AddKinematicUnit(SEEK, 1), 0);
	}
	if (isKeyboardKeyDown(ALLEGRO_KEY_2))
	{
		MESSAGE_MANAGER->addMessage(new AddKinematicUnit(ARRIVE, 1), 0);
	}
	if (isKeyboardKeyDown(ALLEGRO_KEY_3))
	{
		MESSAGE_MANAGER->addMessage(new AddKinematicUnit(FLEE, 1), 0);
	}
	if (isKeyboardKeyDown(ALLEGRO_KEY_4))
	{
		MESSAGE_MANAGER->addMessage(new AddKinematicUnit(WANDER, 1), 0);
	}
	if (isKeyboardKeyDown(ALLEGRO_KEY_5))
	{
		MESSAGE_MANAGER->addMessage(new AddKinematicUnitNearPlayerMessage(ALIGN, 200), 0);
	}
	if (isKeyboardKeyDown(ALLEGRO_KEY_6))
	{
		MESSAGE_MANAGER->addMessage(new AddKinematicUnitNearPlayerMessage(FACE, 200), 0);
	}
	if (isKeyboardKeyDown(ALLEGRO_KEY_7))
	{
		MESSAGE_MANAGER->addMessage(new AddKinematicUnit(PURSUE, 1), 0);
	}
	if (isKeyboardKeyDown(ALLEGRO_KEY_8))
	{
		MESSAGE_MANAGER->addMessage(new AddKinematicUnit(WANDERFLEE, 1), 0);
	}
	if (isKeyboardKeyDown(ALLEGRO_KEY_9))
	{
		MESSAGE_MANAGER->addMessage(new AddKinematicUnit(WANDERSEEK, 1), 0);
	}
	if (isKeyboardKeyDown(ALLEGRO_KEY_0))
	{
		MESSAGE_MANAGER->addMessage(new AddKinematicUnit(SEPARATE, 1), 0);
	}
	if (isKeyboardKeyDown(ALLEGRO_KEY_P))
	{
		MESSAGE_MANAGER->addMessage(new AddKinematicUnit(COHESION, 1), 0);
	}
	if (isKeyboardKeyDown(ALLEGRO_KEY_L))
	{
		MESSAGE_MANAGER->addMessage(new AddKinematicUnit(FLOCKING, 1), 0);
	}
	//############################################################
	
	//###############MOUSE/KEY PRESS/RELEASE EVENTS###############
	while (!al_is_event_queue_empty(mp_eventque))
	{
		ALLEGRO_EVENT input;
		al_get_next_event(mp_eventque, &input);
		if (input.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			Vector2D mousePos = Vector2D(input.mouse.x, input.mouse.y);
			if (input.mouse.button == 1)
			{
			}
			if (input.mouse.button == 2)
			{
			}
		}

		if (input.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			Vector2D mousePos = Vector2D(input.mouse.x, input.mouse.y);
			if (input.mouse.button == 1)
			{
			}
			if (input.mouse.button == 2)
			{
			}
		}

		if (input.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (input.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				MESSAGE_MANAGER->addMessage(new ExitGameMessage(), 0);
				break;
			case ALLEGRO_KEY_SPACE:
				MESSAGE_MANAGER->addMessage(new ToggleDebugMessage(), 0);
			}
		}

		if (input.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (input.keyboard.keycode)
			{
			case ALLEGRO_KEY_A:
				MESSAGE_MANAGER->addMessage(new AddKinematicUnit(FLOCKING, 10), 0);
				break;
			case ALLEGRO_KEY_D:
				UNIT_MANAGER->removeAllBoids();//MESSAGE_MANAGER->addMessage(new RemoveRandomKinematicUnitMessage(), 0);
				break;
			case ALLEGRO_KEY_Y:
				MESSAGE_MANAGER->addMessage(new ModifyFlockingWeightMessage(WEIGHT_SEPARATION, 0.05), 0);
				break;
			case ALLEGRO_KEY_U:
				MESSAGE_MANAGER->addMessage(new ModifyFlockingWeightMessage(WEIGHT_COHESION, 0.05), 0);
				break;
			case ALLEGRO_KEY_I:
				MESSAGE_MANAGER->addMessage(new ModifyFlockingWeightMessage(WEIGHT_GROUP_ALIGNMENT, 0.1), 0);
				break;
			case ALLEGRO_KEY_O:
				MESSAGE_MANAGER->addMessage(new ModifyFlockingWeightMessage(WEIGHT_GROUP_VELOCITY_MATCH, 0.1), 0);
				break;
			case ALLEGRO_KEY_H:
				MESSAGE_MANAGER->addMessage(new ModifyFlockingWeightMessage(WEIGHT_SEPARATION, -0.05), 0);
				break;
			case ALLEGRO_KEY_J:
				MESSAGE_MANAGER->addMessage(new ModifyFlockingWeightMessage(WEIGHT_COHESION, -0.05), 0);
				break;
			case ALLEGRO_KEY_K:
				MESSAGE_MANAGER->addMessage(new ModifyFlockingWeightMessage(WEIGHT_GROUP_ALIGNMENT, -0.1), 0);
				break;
			case ALLEGRO_KEY_L:
				MESSAGE_MANAGER->addMessage(new ModifyFlockingWeightMessage(WEIGHT_GROUP_VELOCITY_MATCH, -0.1), 0);
				break;
			case ALLEGRO_KEY_SPACE:
				MESSAGE_MANAGER->addMessage(new ToggleDebugMessage(), 0);
				break;
			}
		}
	}
	//###############################################
}

bool InputManager::isMouseButtonDown(int keycode)
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);
	return al_mouse_button_down(&mouseState, keycode);
}

//Keycode = ALLEGRO_KEY_[X]. EX: ALLEGRO_KEY_G
bool InputManager::isKeyboardKeyDown(int keycode)
{
	ALLEGRO_KEYBOARD_STATE keyboardState;
	al_get_keyboard_state(&keyboardState);
	return al_key_down(&keyboardState, keycode);
}