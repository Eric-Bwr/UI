#pragma once

#include "Layout.h"

class GridLayout : public Layout {
public:
	void init(float width, float height);
	void init(int rows, int cols, float width, float height);

	void adjust() override;

	void setGapX(float gapX);
	void setGapY(float gapY);
	void setRows(int rows);
	void setColumns(int cols);

    float getGapX() { return gapX; }
    float getGapY() { return gapY; }
    float getRows() { return rows; }
    float getColumns() { return cols; }

    float gapX;
    float gapY;
	int rows;
	int cols;
};