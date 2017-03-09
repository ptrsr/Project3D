#ifndef TEXT_H
#define TEXT_H

#include <mge/core/AbstractGame.hpp>

#include "mge/core/GameObject.hpp"
#include "mge/scenes/menuStates/AbstactState.hpp"
class DebugHud;

enum TextType {
	IP,
	Score,
	DisplayNormal
};

class Text
{
    //PUBLIC FUNCTIONS

	public:
		Text(TextType textType);
		virtual ~Text();

		virtual void _initializeScene();
		virtual void Update();
		virtual int CheckSelection();
		void setText(string textToDislpay);
		virtual GameObject* getPlane();
		virtual void deleteScene();
		int CheckState();

	private:
		GameObject * placeToRenderText;
		int _counter = 0;
		void _updateIP();
		void _updateScore();
		void _updateDisplay();
		void createObject(char obj);
		void deleteLastObject();
		string _textToDislplay;
		TextType _textType;
		string text = "";
		string ip;
		string copyForCompare;
		std::vector<GameObject*> objs;
		GameObject* posOfObjs[23];
		
		bool _isKeyPress = true;
		int _delay = 15;
		int _delayCounter = 0;

		Text(const Text&);
		Text& operator=(const Text&);
};

#endif // TEXT_H
