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
    textShader->setUniformMatrix4f("ortho", ortho.getBuffer());
    quadShader->setUniformMatrix4f("ortho", ortho.getBuffer());
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
    if ((std::chrono::system_clock::now() - start).count() >= CURSOR_INTERVAL) {
        cursor = !cursor;
        start = std::chrono::system_clock::now();
    }
    for (auto const &componentList : components)
        for (auto component : *componentList.second)
            renderComponent(component);
}

void UIManager::renderComponent(UIComponent *component) {
    if (component->type == UIComponentType::UITEXT) {
        auto ui = (UIText *) component;
        textShader->bind();
        textShader->setUniform4f(SHADER_COLOR_NAME, ui->r, ui->g, ui->b, ui->a);
        ui->textMesh.render();
        quadShader->bind();
    } else if (component->type == UIComponentType::UITEXTFIELD) {
        auto ui = ((UITextField *) component);
        auto bgc = ui->bgColor;
        if (ui->pressed)
            bgc = ui->pressedColor;
        else if (ui->hovered)
            bgc = ui->hoveredColor;
        quadShader->setUniform4f(SHADER_COLOR_NAME, bgc.r, bgc.g, bgc.b, bgc.a);
        if (ui->texture != nullptr)
            ui->texture->bind();
        if (ui->pressed)
            ui->pressedMesh.render();
        else if (ui->hovered)
            ui->hoverMesh.render();
        else
            ui->mesh.render();
        if (ui->pressed && cursor) {
            auto cc = ui->cursorColor;
            quadShader->setUniform4f(SHADER_COLOR_NAME, cc.r, cc.g, cc.b, cc.a);
            ui->cursorMesh.render();
        }
        auto fgc = ui->fgColor;
        textShader->bind();
        textShader->setUniform4f(SHADER_COLOR_NAME, fgc.r, fgc.g, fgc.b, fgc.a);
        ui->text.textMesh.render();
        quadShader->bind();
    } else if (component->type == UIComponentType::UIBUTTON) {
        auto ui = (UIButton *) component;
        auto bgc = ui->bgColor;
        if (ui->pressed)
            bgc = ui->pressedColor;
        else if (ui->hovered)
            bgc = ui->hoveredColor;
        quadShader->setUniform4f(SHADER_COLOR_NAME, bgc.r, bgc.g, bgc.b, bgc.a);
        if (ui->texture != nullptr)
            ui->texture->bind();
        if (ui->pressed)
            ui->pressedMesh.render();
        else if (ui->hovered)
            ui->hoverMesh.render();
        else
            ui->mesh.render();
        auto fgc = ui->fgColor;
        textShader->bind();
        textShader->setUniform4f(SHADER_COLOR_NAME, fgc.r, fgc.g, fgc.b, fgc.a);
        ui->text.textMesh.render();
        quadShader->bind();
    } else if (component->type == UIComponentType::UILAYOUT) {
        auto layout = (Layout *) component;
        for (auto ui : layout->components)
            renderComponent(ui);
    } else if (component->type == UIComponentType::UISLIDER) {
        auto ui = (UISlider *) component;
        auto fgc = ui->dragColor;
        auto bgc = ui->bgColor;
        quadShader->setUniform4f(SHADER_COLOR_NAME, bgc.r, bgc.g, bgc.b, bgc.a);
        ui->bgMesh.render();
        quadShader->setUniform4f(SHADER_COLOR_NAME, fgc.r, fgc.g, fgc.b, fgc.a);
        ui->dragMesh.render();
    } else if (component->type == UIComponentType::UISPLITPANE) {
        auto ui = (UISplitPane *) component;
        UIColor bgc = COLOR_GREEN;
        quadShader->setUniform4f(SHADER_COLOR_NAME, bgc.r, bgc.g, bgc.b, bgc.a);
        ui->mesh.render();
        renderComponent(ui->getLeft());
        renderComponent(ui->getRight());
    }
}

UIManager::~UIManager() {
    for (auto compPair : components) {
        delete compPair.second;
    }
}