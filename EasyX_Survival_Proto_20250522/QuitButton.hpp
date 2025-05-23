#include "Button.hpp"

class QuitButton : public Button
{
public:
	QuitButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
		: Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {
	}
protected:
	void OnClick()
	{
		clicked = true;
	}

public:
	bool clicked = false;
};