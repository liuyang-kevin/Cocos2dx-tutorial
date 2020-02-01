#ifndef __MENU_UI_SCENE_H__
#define __MENU_UI_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MenuUI : public Scene, public TableViewDataSource, public TableViewDelegate {
public:

    static cocos2d::Scene *createScene();

    virtual bool init();

// implement the "static create()" method manually
// 这里应该是个宏，实现构造方法。
    CREATE_FUNC(MenuUI);

// 一个回调函数
    void menuCloseCallback(cocos2d::Ref *pSender);

public:
/*
 * TableView 必须实现的函数 */
// 当滑动 tableView 时触发该方法 参数为当前的 tableView 对象
    virtual void scrollViewDidScroll(ScrollView *view) {};

// 当tableview被放大或缩小时触发该方法  参数为当前tableview对象
    virtual void scrollViewDidZoom(ScrollView *view) {}

// 当cell被点击时调用该方法 参数为当前的tableview对象与被点击的cell对象
    virtual void tableCellTouched(TableView *table, TableViewCell *cell);

// 设置tableview的Cell大小
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);

// 获取编号为idx的cell
    virtual TableViewCell *tableCellAtIndex(TableView *table, ssize_t idx);

// 设置tableview中cell的个数
    virtual ssize_t numberOfCellsInTableView(TableView *table);

private:
    bool _cellTouchEnabled;
    cocos2d::Vec2 _tableOffset;
    bool _shouldRestoreTableOffset;
    std::vector<std::string> _childTestNames;
};

#endif // __MENU_UI_SCENE_H__
