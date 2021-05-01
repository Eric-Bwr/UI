#include "UIManager.h"

void UIManager::init(int width, int height) {
    DataManager::init();
    ortho = orthographicMatrix(0.0f, width, height, 0.0, -1.0, 1.0);
    textShader = new Shader("../Assets/Shader/TextShader.glsl");
    textShader->setUniformMatrix4f("ortho", ortho.getBuffer());
    quadShader = new Shader("../Assets/Shader/QuadShader.glsl");
    quadShader->setUniformMatrix4f("ortho", ortho.getBuffer());
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
            component->mousePositionInput(button, action);
}

void UIManager::render() {
    for (auto const &componentList : components)
        for (auto component : *componentList.second)
            renderComponent(component);
}

void UIManager::renderComponent(UIComponent *component) {
    if (component->type == UIComponentType::UITEXT) {
        auto element = ((UIText *) component);
        textShader->bind();
        textShader->setUniform4f(SHADER_COLOR_NAME, element->r, element->g, element->b, element->a);
        element->textMesh.render();
        quadShader->bind();
    } else if (component->type == UIComponentType::UIBUTTON) {
        auto btn = ((UIButton *) component);
        UIColor bgc = btn->bgColor;
        if (btn->hovered)
        	bgc = btn->hoveredColor;
	    if (btn->pressed)
		    bgc = btn->pressedColor;
        quadShader->setUniform4f(SHADER_COLOR_NAME, bgc.r, bgc.g, bgc.b, bgc.a);
        if (btn->texture != nullptr)
	        btn->texture->bind();
	    btn->mesh.render();
    } else if (component->type == UIComponentType::UILAYOUT) {
        auto layout = ((Layout *) component);
        for (auto subComp : layout->components)
            renderComponent(subComp);
    }
}

UIManager::~UIManager() {
    for (auto compPair : components) {
        delete compPair.second;
    }
}