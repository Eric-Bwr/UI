#include "GridLayout.h"

GridLayout::GridLayout(float _width, float _height) : Layout(_width, _height) {
	gapX = 10;
	gapY = 10;
	rows = 1;
	cols = 0;
}

GridLayout::GridLayout(int _rows, int _cols, float _width, float _height) : Layout(_width, _height) {
	gapX = 10;
	gapY = 10;
	rows = _rows;
	cols = _cols;
	if (rows != 0 && cols != 0) /* either rows or cols has to be 0 */
		; /* TODO: Error */
}

void GridLayout::adjust() {
	int compn = components.size();

	if (compn == 0)
		return;

	int real_rows = rows;
	int real_cols = cols;
	if (real_rows == 0)
		real_rows = (compn + real_cols - 1) / real_cols;
	else
		real_cols = (compn + real_rows - 1) / real_rows;

	if (compn < real_cols)
		real_cols = compn;

	float cellWidth = width - insets.left - insets.right;
	float cellHeight = height - insets.top - insets.bottom;
	cellWidth = (cellWidth - (real_cols - 1) * gapX) / real_cols;
	cellHeight = (cellHeight - (real_rows - 1) * gapY) / real_rows;

	float x = insets.left;
	float y = insets.top;
	int i = 0;
	int yc = 0;

	while (i < compn) {
		auto comp = components[i];
		comp->setBounds(x, y, cellWidth, cellHeight);
		i++;
		yc++;

		if (yc == real_cols) {
			yc = 0;
			y += gapY + cellHeight;
			x = insets.left;
		} else {
			x += gapX + cellWidth;
		}
	}
}

void GridLayout::setGapX(float m) {
	gapX = m;
}

void GridLayout::setGapY(float m) {
	gapY = m;
}

float GridLayout::getGapX() const {
	return gapX;
}

float GridLayout::getGapY() const {
	return gapY;
}

void GridLayout::setRows(int r) {
	rows = r;
}

void GridLayout::setColumns(int c) {
	cols = c;
}

int GridLayout::getRows() {
	return rows;
}

int GridLayout::getColumns() {
	return cols;
}