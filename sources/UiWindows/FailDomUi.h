#pragma once

#include "W4Framework.h"
#include "FlowUi/Ui/DomUi.h"

class FailDomUi : public DomUi {
public:
    FailDomUi(float baseOrder) : DomUi(baseOrder) {
    }
    void setVisible(std::string id, bool flag);
    void setReturnToMenuCallback(std::function<void()> callback) {
        m_returnToMenuCallback = callback;
    };
protected:
    void initContent() override;

private:
    std::function<void()> m_returnToMenuCallback;
};

