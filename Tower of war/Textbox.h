#pragma once
#include "Player.h"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27 


class Textbox {

private:
	Text textbox;
	ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit;

	void inputLogic(int charTyped)
	{
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
		{
			text << static_cast<char>(charTyped);
		}
		else if (charTyped == DELETE_KEY)
		{
			if (text.str().length() > 0)
			{
				deleteLastChar();
			}
		}
		textbox.setString(text.str() + "|");
	}

	void deleteLastChar()
	{
		string t = text.str();
		string newT = "";
		for (int i = 0; i < t.length() - 1; i++)
		{
			newT += t[i];
		}
		text.str("");
		text << newT;

		textbox.setString(text.str());
	}

public:
	Textbox() { }

	Textbox(int size, bool sel)
	{
		textbox.setCharacterSize(size);
		textbox.setFillColor(Color::Black);
		isSelected = sel;
		if (sel)
		{
			textbox.setString("|");
		}
		else
		{
			textbox.setString("");
		}
	}

	void setFont(Font &font)
	{
		textbox.setFont(font);
	}

	void setPosition(Vector2f pos)
	{
		textbox.setPosition(pos);
	}

	void setLimit(bool ToF, int lim)
	{
		hasLimit = ToF;
		limit = lim-1;
	}

	void setSelected(bool sel)
	{
		isSelected = sel;
		if (!sel)
		{
			string t = text.str();
			string newT = "";
			for (int i = 0; i < t.length(); i++)
			{
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}

	void DeleteString() 
	{
		for (int i = 0; i < 20; i++)
		{
			if (text.str().length() > 0)
			{
				deleteLastChar();
			}

		}
	}

	void drawTo(RenderWindow& window)
	{
		window.draw(textbox);
	}

	string getText() 
	{
		string t = text.str();
		return t;
	}

	void typedOn(Event input)
	{
		if (isSelected)
		{
			int charTyped = input.text.unicode;

			if (charTyped < 128)
			{
				cout << (char)charTyped << endl;
				if (hasLimit)
				{
					if (text.str().length() <= limit)
					{
						inputLogic(charTyped);
					}
					else if (text.str().length() > limit && charTyped == DELETE_KEY)
					{
						deleteLastChar();
					}
				}
				else
				{
					inputLogic(charTyped);
				}
			}
		}
	}
};