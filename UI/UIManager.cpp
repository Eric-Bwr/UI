#include "UIManager.h"

void UIManager::init(int width, int height) {
    DataManager::init();
    ortho = orthographicMatrix(0.0f, width, height, 0.0, -1.0, 1.0);
    textShader = new Shader("../Assets/Shader/TextShader.glsl");
    textShader->setUniformMatrix4f("ortho", ortho.getBuffer());
    quadShader = new Shader("../Assets/Shader/QuadShader.glsl");
    quadShader->setUniformMatrix4f("ortho", ortho.getBuffer());
    start = std::chrono::system_clock::now();
}

void UIManager::add(UIComponent *component, int order) {
    std::vector<UIComponent *> *componentBatch;
    if (!components.count(order)) {
        componentBatch = new std::vector<UIComponent *>;
        components.insert(std::pair<int, std::vector<UIComponent *> *>(order, componentBatch));
    } else {
        componentBatch = components.find(order)->second;
    }
    componentBatch->emplace_back(component);
}

void UIManager::remove(UIComponent *component) {
    for (auto compPair : components) {
        std::vector<UIComponent *> *compList = compPair.second;
        for (int i = 0; i < compList->size(); i++)
            if (compList->at(i) == component)
                compList->erase(compList->begin() + i);
    }
}

void UIManager::setSize(int width, int height) {
    ortho.orthographic(0.0f, width, height, 0.0, -1.0, 1.0);
}

void UIManager::keyInput(int key, int action, int mods) {
    for (auto const &componentList : components)
        for (auto component : *componentList.second)
            component->keyInput(key, action, mods);
}

void UIManager::charInput(unsigned int key) {
    for (auto const &componentList : components)
        for (auto component : *componentList.second)
            component->charInput(key);
}

void UIManager::mousePositionInput(double x, double y) {
    for (auto const &componentList : components)
        for (auto component : *componentList.second)
            component->mousePositionInput(x, y);
}

void UIManager::mouseButtonInput(int button, int action) {
    for (auto const &componentList : components)
        for (auto component : *componentList.second)
            component->mouseButtonInput(button, action);
}

void UIManager::render() {
    if((std::chrono::system_clock::now() - start).count() >= CURSOR_INTERVAL){
        cursor = !cursor;
        start = std::chrono::system_clock::now();
    }
    for (auto const &componentList : components)
        for (auto component : *componentList.second)
            renderComponent(component);
}

void UIManager::renderComponent(UIComponent *component) {
    if (component->type == UIComponentType::UITEXT) {
        auto text = (UIText *) component;
        textShader->bind();
        textShader->setUniform4f(SHADER_COLOR_NAME, text->r, text->g, text->b, text->a);
        text->textMesh.render();
        quadShader->bind();
    }else if (component->type == UIComponentType::UITEXTFIELD) {
        auto textField = ((UITextField *) component);
        UIColor bgc = textField->bgColor;
        if (textField->hovered)
            bgc = textField->hoveredColor;
        if (textField->pressed)
            bgc = textField->pressedColor;
        quadShader->setUniform4f(SHADER_COLOR_NAME, bgc.r, bgc.g, bgc.b, bgc.a);
        if (textField->texture != nullptr)
            textField->texture->bind();
        textField->mesh.render();
        if(textField->pressed && cursor) {
            quadShader->setUniform4f(SHADER_COLOR_NAME, textField->cursorColor.r, textField->cursorColor.g, textField->cursorColor.b, textField->cursorColor.a);
            textField->cursorMesh.render();
        }
        textShader->bind();
        textShader->setUniform4f(SHADER_COLOR_NAME, textField->fgColor.r, textField->fgColor.g, textField->fgColor.b, textField->fgColor.a);
        textField->text.textMesh.render();
        quadShader->bind();
    } else if (component->type == UIComponentType::UIBUTTON) {
        auto btn = (UIButton *) component;
        UIColor bgc = btn->bgColor;
        if (btn->hovered)
        	bgc = btn->hoveredColor;
	    if (btn->pressed)
		    bgc = btn->pressedColor;
        quadShader->setUniform4f(SHADER_COLOR_NAME, bgc.r, bgc.g, bgc.b, bgc.a);
        if (btn->texture != nullptr)
	        btn->texture->bind();
        if (btn->pressed)
            btn->pressedMesh.render();
        else if (btn->hovered)
            btn->hoverMesh.render();
        else
            btn->mesh.render();
        textShader->bind();
        textShader->setUniform4f(SHADER_COLOR_NAME, btn->fgColor.r, btn->fgColor.g, btn->fgColor.b, btn->fgColor.a);
        btn->text.textMesh.render();
        quadShader->bind();
    } else if (component->type == UIComponentType::UILAYOUT) {
        auto layout = (Layout *) component;
        for (auto subComp : layout->components)
        	renderComponent(subComp);
    } else if (component->type == UIComponentType::UISLIDER) {
    	auto slider = (UISlider *) component;
    	UIColor dc = slider->dragColor;
    	UIColor bgc = slider->bgColor;
    	quadShader->setUniform4f(SHADER_COLOR_NAME, bgc.r, bgc.g, bgc.b, bgc.a);
    	slider->bgMesh.render();
	    quadShader->setUniform4f(SHADER_COLOR_NAME, dc.r, dc.g, dc.b, dc.a);
	    slider->dragMesh.render();
    } else if (component->type == UIComponentType::UISPLITPANE) {
    	auto splitpane = (UISplitPane *) component;

	    UIColor bgc = COLOR_GREEN;
	    quadShader->setUniform4f(SHADER_COLOR_NAME, bgc.r, bgc.g, bgc.b, bgc.a);
	    splitpane->mesh.render();

    	renderComponent(splitpane->getLeft());
    	renderComponent(splitpane->getRight());
    }
}

UIManager::~UIManager() {
    for (auto compPair : components) {
        delete compPair.second;
    }
}