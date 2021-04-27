#include "UIManager.h"

UIManager::UIManager(int width, int height) {
    TextManager::init();
    TextManager::setSize(width, height);
    ortho = orthographicMatrix(0.0f, width, height, 0.0, -1.0, 1.0);
    textShader = new Shader("../Assets/Shader/TextShader.glsl");
    textShader->setUniformMatrix4f("ortho", ortho.getBuffer());
}

void UIManager::add(UIComponent *component, int order) {
	std::vector<UIComponent *>* componentBatch;
	if (!components.count(order)) {
		componentBatch = new std::vector<UIComponent *>;
		components.insert(std::pair<int, std::vector<UIComponent *>*>(order, componentBatch));
	} else {
		componentBatch = components.find(order)->second;
	}
	componentBatch->emplace_back(component);
}

void UIManager::remove(UIComponent *component) {
	for (auto compPair : components) {
		std::vector<UIComponent *>* compList = compPair.second;
		for(int i = 0; i < compList->size(); i++)
			if(compList->at(i) == component)
				compList->erase(compList->begin() + i);
	}
}

void UIManager::setSize(int width, int height) {
    TextManager::setSize(width, height);
//CHECK THIS
   // ortho.ortho(0.0f, width, height, 0.0, -1.0, 1.0);
}

void UIManager::render() {
    for (auto const &componentList : components) {
        for (auto component : *componentList.second) {
            if(component->type == UIComponentType::UITEXT){
                textShader->bind();
                ((UIText*)component)->textMesh.render();
            }
        }
    }
}

UIManager::~UIManager() {
    for (auto compPair : components) {
        for (auto comp : *compPair.second)
            delete comp;
        delete compPair.second;
    }
}
