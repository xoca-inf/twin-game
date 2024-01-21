Базовый проект, имеет кастомный загрузчик,
ресурсную парсилку, парсилку настроек, переходы по fsm,
меню выполнены на FlowUi(WorldUi).

### FSM ###

* Описывается в gameFSM.h
* Хранится в main структуре игры
* onEnterFunc, onLeaveFunc, onUpdateFunc
### ResourceLibary ###

* Синглтон для назначения id для путей
* Можно оборудовать предзагрузкой в onStart
* Инициализируется в OnStart
* Пути прописываются в resources.json
* ResourceLibary::instance().getTexture("MyButton")
* ResourceLibary::instance().getModelPath("House");

### Settings ###

* Синглтон для хранения пользовательских настроек
* Инициализируется в OnStart
* Пути прописываются в settings.json
* Settings::instance().getFloat("SomeDuration");
* Settings::instance().getVec3("ObjectPosition");

### FlowUi ###

* WorldUi меню лежат в UiWindows
* Примеры DomUi(на виджетах) лежат в репе flowUi

### CSS ###
* Кастомный загрузчик лежит в index.css
* Картинка для загрузки закодирована в base64:
https://elmah.io/tools/base64-image-encoder/