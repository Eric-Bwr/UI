#pragma once

#include "Layout.h"

class GridLayout : public Layout {
public:

	GridLayout(float, float);
	GridLayout(int, int, float, float);

	void adjust() override;

	void setGapX(float);
	void setGapY(float);
	float getGapX() const;
	float getGapY() const;

	void setRows(int);
	void setColumns(int);

	int getRows();
	int getColumns();

private:
	float gapX;
	float gapY;
	int rows;
	int cols;
};
