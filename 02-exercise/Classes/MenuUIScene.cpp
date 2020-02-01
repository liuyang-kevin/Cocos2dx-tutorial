#include "MenuUIScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define TABLE_LABEL_TAG 1024

// 自定义一个TableView
class MenuTableView : public TableView {
public:
    static MenuTableView *create(TableViewDataSource *dataSource, Size size) {
        auto table = new(std::nothrow) MenuTableView();
        table->initWithViewSize(size, nullptr);
        table->autorelease();
        table->setDataSource(dataSource);
        table->_updateCellPositions();
        table->_updateContentSize();

        return table;
    }

    virtual void onTouchEnded(Touch *touch, Event *event) override {
        if (!this->isVisible()) {
            return;
        }

        if (_touchedCell) {
            auto label = (Label *) _touchedCell->getChildByTag(TABLE_LABEL_TAG);

            Rect bbox = label->getBoundingBox();
            bbox.origin = _touchedCell->convertToWorldSpace(bbox.origin);

            if (bbox.containsPoint(touch->getLocation()) && _tableViewDelegate != nullptr) {
                _tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
                _tableViewDelegate->tableCellTouched(this, _touchedCell);
            }

            _touchedCell = nullptr;
        }

        ScrollView::onTouchEnded(touch, event);
    }

    void onMouseScroll(Event *event) {
        auto mouseEvent = static_cast<EventMouse *>(event);
        float moveY = mouseEvent->getScrollY() * 20;

        auto minOffset = this->minContainerOffset();
        auto maxOffset = this->maxContainerOffset();

        auto offset = this->getContentOffset();
        offset.y += moveY;

        if (offset.y < minOffset.y) {
            offset.y = minOffset.y;
        } else if (offset.y > maxOffset.y) {
            offset.y = maxOffset.y;
        }
        this->setContentOffset(offset);
    }

protected:
    MenuTableView() {
        auto mouseListener = EventListenerMouse::create();
        mouseListener->onMouseScroll = CC_CALLBACK_1(MenuTableView::onMouseScroll, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    }
};


Scene *MenuUI::createScene() {
    return MenuUI::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MenuUI::init() {
    //////////////////////////////
    // 1. super init first
    // 父类内容初始化
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // getVisibleOrigin：获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. 增加列表
    // 可以点击
    _cellTouchEnabled = true;
    // 准备假数据
    _childTestNames.emplace_back(StringUtils::format("%d", static_cast<int>(_childTestNames.size() + 1)) + ":" + "假数据");
    _childTestNames.emplace_back(StringUtils::format("%d", static_cast<int>(_childTestNames.size() + 1)) + ":" + "假数据");
    _childTestNames.emplace_back(StringUtils::format("%d", static_cast<int>(_childTestNames.size() + 1)) + ":" + "假数据");
    _childTestNames.emplace_back(StringUtils::format("%d", static_cast<int>(_childTestNames.size() + 1)) + ":" + "假数据");
    _childTestNames.emplace_back(StringUtils::format("%d", static_cast<int>(_childTestNames.size() + 1)) + ":" + "假数据");
    _childTestNames.emplace_back(StringUtils::format("%d", static_cast<int>(_childTestNames.size() + 1)) + ":" + "假数据");
    // 准备View
    auto tableView = MenuTableView::create(this, Size(400, visibleSize.height));
    tableView->setPosition(origin.x + (visibleSize.width - 400) / 2, origin.y);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tableView->setDelegate(this);
    this->addChild(tableView);
    tableView->reloadData();

    if (_shouldRestoreTableOffset) {
        tableView->setContentOffset(_tableOffset);
    }
    /////////////////////////////
    // 3. 增加关闭图标

    // 关闭按钮，图片两个状态，加一个回调函数
    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(MenuUI::menuCloseCallback, this));

    // 通过检查按钮宽高检查是否图片加载成功
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0) {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    } else {
        // GL坐标系x轴朝右，y轴朝上。默认原点在左下角。所以y轴坐标是是 org+图片一半大小
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));  // 计算坐标，把按钮放在对应位置。
    }

    // 创建菜单。
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO); // 添加在坐标0，0的位置，（目测是是左下角，menu会充满屏幕）
    this->addChild(menu, 1);       // 添加到Scene中去



    return true;
}

void MenuUI::menuCloseCallback(Ref *pSender) {
    //Close the cocos2d-x game scene and quit the application
    // 获取Director单例，结束应用
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void MenuUI::tableCellTouched(TableView *table, TableViewCell *cell) {
    if (_cellTouchEnabled) {
        auto index = cell->getIdx();
        CCLOG("第 %ld 个Cell被点击了\n", index);

        auto test = _testCallbacks[index]();

    }
}

Size MenuUI::tableCellSizeForIndex(TableView *table, ssize_t idx) {
    return Size(400, 30);
}

TableViewCell *MenuUI::tableCellAtIndex(TableView *table, ssize_t idx) {
    auto cell = table->dequeueCell();
    if (!cell) {
        cell = TableViewCell::create();
        auto label = Label::createWithTTF(_childTestNames[idx], "fonts/arial.ttf", 20.0f);
        label->setTag(TABLE_LABEL_TAG);
        label->setPosition(200, 15);
        cell->addChild(label);
    } else {
        auto label = (Label *) cell->getChildByTag(TABLE_LABEL_TAG);
        label->setString(_childTestNames[idx]);
    }

    return cell;
}

ssize_t MenuUI::numberOfCellsInTableView(TableView *table) {
    return _childTestNames.size();
}
