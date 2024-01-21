#pragma once

#include "W4Framework.h"
#include "FlowUi/Ui/DomUi.h"

class GameDomUi : public DomUi
{
public:
    GameDomUi(float baseOrder) : DomUi(baseOrder) {}
    void setVisible(std::string id, bool flag);
    void finalMenu();
protected:
    void initContent() override;
    
private:
    //std::unordered_map<std::string, sptr<FlexGuiWidget> > m_items;
};

