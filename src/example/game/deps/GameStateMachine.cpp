#include "GameStateMachine.h"

/*
	Adding one state without removing the previous state: This way is useful
	for pause menus and so on
*/
void GameStateMachine::pushState(GameState* pState)
{
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

/*
	Removing one state and adding another: We will use this way to completely
	change states without leaving the option to return
*/
void GameStateMachine::changeState(GameState* pState)
{
	if(!m_gameStates.empty()) {
		if(m_gameStates.back()->getStateID() == pState->getStateID()) {
			return;
		}

		if(m_gameStates.back()->onExit()) {
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}

	// Push back our new state
	m_gameStates.push_back(pState);

	// Initialize it
	m_gameStates.back()->onEnter();
}

/*
	Removing one state without adding another: This way will be used to remove
	pause states or any other state that had been pushed on top of another one
*/
void GameStateMachine::popState()
{
	if(!m_gameStates.empty()) {
		if(m_gameStates.back()->onExit()) {

			delete m_gameStates.back();
			m_gameStates.pop_back();

		}
	}
}
