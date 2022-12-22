#pragma once

#include <OpenGL/Texture.h>
#include "../UIComponent.h"
#include "../../UIStructure/QuadMesh.h"
#include "../Text/UIText.h"

class UISwitch : public UIComponent {
public:
	void init(float positionX, float positionY, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT);

	void setPosition(float positionX, float positionY) override;
	void setSize(float width, float height);
    void setBounds(float positionX, float positionY, float width, float height) override;
	void mousePositionInput(double x, double y) override;
	void mouseButtonInput(int action) override;
	void updateMesh() override;
	bool isEnabled();
	void setEnabled(bool);
	float getSwitchSize() const;
	void setSwitchSize(float);
	void setSwitchX(float);
	float getSwitchX();
	void setCircular(bool);
	bool isCircular();

	bool hovered = false;

	QuadMesh bgMesh;
	QuadMesh switchMesh;

	UIColor bgColor;
	UIColor switchColor;

	void updateRadius();

	float switchSize;

	bool enabled = false;
	bool circular = false;
	float switchX;
};