#pragma once

#include "Layout.h"

class GridLayout : public Layout {
public:
	GridLayout(float width, float height);
	GridLayout(int rows, int cols, float width, float height);

	void adjust() override;

	void setGapX(float gapX);
	void setGapY(float gapY);
	void setRows(int rows);
	void setColumns(int cols);

    inline float getGapX() { return gapX; }
    inline float getGapY() { return gapY; }
    inline float getRows() { return rows; }
    inline float getColumns() { return cols; }

    float gapX;
    float gapY;
	int rows;
	int cols;
};