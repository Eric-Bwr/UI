#include "UIManager.h"
#include "Text/TextManager.h"

UIManager::UIManager(int width, int height) {
    TextManager::init();
    TextManager::setSize(width, height);
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
}

void UIManager::render() {

}

UIManager::~UIManager() {
    for (auto compPair : components) {
        for (auto comp : *compPair.second)
            delete comp;
        delete compPair.second;
    }
}
