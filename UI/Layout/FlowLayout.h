#ifndef UI_FLOWLAYOUT_H
#define UI_FLOWLAYOUT_H

#include "Layout.h"

class FlowLayout: public Layout {
public:
	float marginX;
	float marginY;

	FlowLayout(float, float);

	void adjust() override;

	void setMarginX(float);
	void setMarginY(float);
	float getMarginX() const;
	float getMarginY() const;
};

#endif //UI_FLOWLAYOUT_H
