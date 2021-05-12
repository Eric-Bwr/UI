#include "UIManager.h"

void UIManager::init(int width, int height, bool scaleOnResize) {
    DataManager::init();
    ortho = orthographicMatrix(0.0f, width, height, 0.0, -1.0, 1.0);
    textShader = new Shader("../Assets/Shader/TextShader.glsl");
    textShader->setUniformMatrix4f("ortho", ortho.getBuffer());
    quadShader = new Shader("../Assets/Shader/QuadShader.glsl");
    quadShader->setUniformMatrix4f("ortho", ortho.getBuffer());
    start = std::chrono::system_clock::now();
    this->width = width;
    this->height = height;
    this->scaleOnResize = scaleOnResize;
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
    textShader->bind();
    textShader->setUniformMatrix4f("ortho", ortho.getBuffer());
    quadShader->bind();
    quadShader->setUniformMatrix4f("ortho", ortho.getBuffer());
    if (scaleOnResize) {
        float factorX = (float) width / (float) this->width;
        float factorY = (float) height / (float) this->height;
        for (auto const &componentList : components)
            for (auto component : *componentList.second)
                component->setBounds(component->positionX * factorX, component->positionY * factorY, component->width * factorX, component->height * factorY);
    }
    this->width = width;
    this->height = height;
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
    this->mouseX = x;
    this->mouseY = y;
    for (auto const &componentList : components)
        for (auto component : *componentList.second)
            component->mousePositionInput(x, y);
}

void UIManager::mouseButtonInput(int button, int action) {
    for (auto const &componentList : components) {
        for (auto component : *componentList.second) {
            component->mouseButtonInput(button, action);
            component->mousePositionInput(mouseX, mouseY);
        }
    }
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
        auto bgc = ui->bgColor.standard;
        if (ui->pressed)
            bgc = ui->bgColor.pressed;
        else if (ui->hovered)
            bgc = ui->bgColor.hover;
        quadShader->setUniform4f(SHADER_COLOR_NAME, bgc.r, bgc.g, bgc.b, bgc.a);
        if (ui->texture != nullptr)
            ui->texture->bind();
        if (ui->pressed)
            ui->mesh.render(2);
        else if (ui->hovered)
            ui->mesh.render(1);
        else
            ui->mesh.render(0);
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
        auto bgc = ui->bgColor.standard;
        if (ui->pressed)
            bgc = ui->bgColor.pressed;
        else if (ui->hovered)
            bgc = ui->bgColor.hover;
        quadShader->setUniform4f(SHADER_COLOR_NAME, bgc.r, bgc.g, bgc.b, bgc.a);
        if (ui->texture != nullptr)
            ui->texture->bind();
        if (ui->pressed)
            ui->mesh.render(2);
        else if (ui->hovered)
            ui->mesh.render(1);
        else
            ui->mesh.render(0);
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
        auto bgc = ui->bgColor;
        auto dc = ui->dragColor;
        auto sc = ui->slideColor;
        if (ui->texture != nullptr)
            ui->texture->bind();
        if (ui->dragging) {
            quadShader->setUniform4f(SHADER_COLOR_NAME, bgc.pressed.r, bgc.pressed.g, bgc.pressed.b, bgc.pressed.a);
            ui->bgMesh.render(2);
            quadShader->setUniform4f(SHADER_COLOR_NAME, sc.pressed.r, sc.pressed.g, sc.pressed.b, sc.pressed.a);
            ui->slideMesh.render(2);
            quadShader->setUniform4f(SHADER_COLOR_NAME, dc.pressed.r, dc.pressed.g, dc.pressed.b, dc.pressed.a);
            ui->dragMesh.render(2);
        } else if (ui->hovered) {
            quadShader->setUniform4f(SHADER_COLOR_NAME, bgc.hover.r, bgc.hover.g, bgc.hover.b, bgc.hover.a);
            ui->bgMesh.render(1);
            quadShader->setUniform4f(SHADER_COLOR_NAME, sc.hover.r, sc.hover.g, sc.hover.b, sc.hover.a);
            ui->slideMesh.render(1);
            quadShader->setUniform4f(SHADER_COLOR_NAME, dc.hover.r, dc.hover.g, dc.hover.b, dc.hover.a);
            ui->dragMesh.render(1);
        } else {
            quadShader->setUniform4f(SHADER_COLOR_NAME, bgc.standard.r, bgc.standard.g, bgc.standard.b, bgc.standard.a);
            ui->bgMesh.render(0);
            quadShader->setUniform4f(SHADER_COLOR_NAME, sc.standard.r, sc.standard.g, sc.standard.b, sc.standard.a);
            ui->slideMesh.render(0);
            quadShader->setUniform4f(SHADER_COLOR_NAME, dc.standard.r, dc.standard.g, dc.standard.b, dc.standard.a);
            ui->dragMesh.render(0);
        }
    } else if (component->type == UIComponentType::UISPLITPANE) {
        auto ui = (UISplitPane *) component;
        UIColor bgc = ui->dividerColor;
        quadShader->setUniform4f(SHADER_COLOR_NAME, bgc.r, bgc.g, bgc.b, bgc.a);
        ui->mesh.render();
        renderComponent(ui->getLeft());
        renderComponent(ui->getRight());
    } else if (component->type == UIComponentType::UISCROLLBAR) {
        auto scrollbar = (UIScrollbar *) component;
        UIColor bgc = scrollbar->barBgColor;
        quadShader->setUniform4f(SHADER_COLOR_NAME, bgc.r, bgc.g, bgc.b, bgc.a);
        scrollbar->barBgMesh.render();
        UIColor fgc = scrollbar->barFgColor;
        quadShader->setUniform4f(SHADER_COLOR_NAME, fgc.r, fgc.g, fgc.b, fgc.a);
        scrollbar->barFgMesh.render();
	    glEnable(GL_SCISSOR_TEST);
	    glScissor(scrollbar->positionX, height - (scrollbar->positionY + scrollbar->height), scrollbar->target->width, scrollbar->height);
        renderComponent(scrollbar->target);
        glDisable(GL_SCISSOR_TEST);
    }
}

UIManager::~UIManager() {
    for (auto compPair : components)
        delete compPair.second;
    delete quadShader;
    delete textShader;
}