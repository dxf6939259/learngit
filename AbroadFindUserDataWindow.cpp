//
//  AbroadFindUserDataWindow.cpp
//  JellyBlast
//
//  Created by Adrian Xi on 16/9/28.
//
//

#include "AbroadFindUserDataWindow.hpp"
#include "WindowBackground.h"
#include "SimpleButton.h"
#include "Match3Common.h"
#include "GameTextModel.h"
#include "SyncDataWindow.h"
#include "PropertyModel.h"
#include "UserModel.h"
#include "InviteFriendsWindow.h"
#include "GeneralInnerBoard.h"

#include "FindUserModel.h"

#pragma mark AbroadFindUserDataWindow

bool AbroadFindUserDataWindow::init()
{
    BasePopupWindow::init();
    
  // CC_RETURN_VALUE_IF_ASSERT_FAIL(pTransUserData != nullptr, false);
    
    WindowBackground* pBackGround = WindowBackground::create(WIN_SIZE_TYPE::BIG_WIN, WIN_BANNER_TYPE::GENERAL_BANNER);
    m_pContentLayer->addChild(pBackGround);
    
    Size bgSize = pBackGround->getContentSize();
    
    SimpleButton* pCloseButton = SimpleButton::create(GENERAL_CLOSE_BUTTON_PURPLE, this, callfuncO_selector(AbroadFindUserDataWindow::onCloseButtonPressed));
    pCloseButton->setPosition(CLOSE_BUTTON_POINT_BIG);
    pCloseButton->setTouchAreaScale(1.3f);
    m_pContentLayer->addChild(pCloseButton);
    
    Label* pTitleLabel = Utility::createLabel(TTF_CONFIG_TITLE, GAME_TEXT_MODEL->getText("data_recovery_title_1"), TITLE_TEXT_COLOR, Color4B::WHITE, -2.0f);
    Utility::resizeLabelByWidth(pTitleLabel, pBackGround->getContentSize().width-20);
    pTitleLabel->setPositionY(370);
    m_pContentLayer->addChild(pTitleLabel);
    
    Label* pDescLabel = Utility::createLabel(TTF_CONFIG_30_NORMAL, GAME_TEXT_MODEL->getText("data_recovery_desc_1"), MAIN_TEXT_COLOR, Color4B::WHITE, -2.0f);
    pDescLabel->setPosition(0, 142);
    if (LOCALIZATION_MODEL->getLanguage() != ZH_CN && LOCALIZATION_MODEL->getLanguage() != ZH_TW && LOCALIZATION_MODEL->getLanguage() != EN_US)
    {
        pDescLabel->setPosition(0, 152);
    }
    pDescLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
    pDescLabel->setDimensions(bgSize.width-160, 350);
    m_pContentLayer->addChild(pDescLabel);
    
    Sprite* pNameIdBg = Sprite::create("res/UI/Sync/sync_info_bg.png");
    pNameIdBg->setPositionY(190);
    m_pContentLayer->addChild(pNameIdBg);
    
    string strName = FIND_USER_MODEL->getUserName();
    Label* pNameLabel = Label::createWithSystemFont(GAME_TEXT_MODEL->getTextWithParameter("data_recovery_user_name", strName.c_str()), "", 25);
    pNameLabel->setColor(Color3B(MAIN_TEXT_COLOR));
    pNameLabel->setPosition(30, 107);
    pNameLabel->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    pNameLabel->setDimensions(bgSize.width-120, 350);
    pNameIdBg->addChild(pNameLabel);
    
    string strDisplayID = FIND_USER_MODEL->getUserDisplayId();
    Label* pUidLabel = Label::createWithSystemFont(GAME_TEXT_MODEL->getTextWithParameter("data_recovery_user_id", strDisplayID.c_str()), "", 25);
    pUidLabel->setColor(Color3B(MAIN_TEXT_COLOR));
    pUidLabel->setPosition(30, 47);
    pUidLabel->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    pUidLabel->setDimensions(bgSize.width-120, 350);
    pNameIdBg->addChild(pUidLabel);
    
    int nMaxLevel = FIND_USER_MODEL->getMaxLevel();
    PropertyItem* pLevelItem = PropertyItem::create(PropertyItem::TYPE_LEVEL, nMaxLevel, false);
    pLevelItem->setPosition(-130, 40);
    m_pContentLayer->addChild(pLevelItem);
    
//    int nMaxTransLevel = FIND_USER_MODEL->getMaxTranscriptLevel() - 3000;
//    nMaxTransLevel = MAX(0, nMaxTransLevel);
//    PropertyItem* pTrancriptItem = PropertyItem::create(PropertyItem::TYPE_TRANSCRIPT, nMaxTransLevel, false);
//    pTrancriptItem->setPosition(122, 75);
//    m_pContentLayer->addChild(pTrancriptItem);
    
//    PropertyItem* pBeanItem = PropertyItem::create(PropertyItem::TYPE_BEAN, FIND_USER_MODEL->getPropertyNum(PROPERTY_TYPE_BEAN, PROPERTY_POTION_ID_SMALL), false);
//    pBeanItem->setPosition(pLevelItem->getPositionX(), -18);
//    m_pContentLayer->addChild(pBeanItem);
    
    PropertyItem* pGoldItem = PropertyItem::create(PropertyItem::TYPE_GOLD, FIND_USER_MODEL->getPropertyNum(PROPERTY_TYPE_GOLD, PROPERTY_POTION_ID_SMALL), false);
    pGoldItem->setPosition(122, 40);
    m_pContentLayer->addChild(pGoldItem);
    
    PropertyItem* pEnergyItem = PropertyItem::create(PropertyItem::TYPE_ENERGY, FIND_USER_MODEL->getTotalPotionNum(), false);
    pEnergyItem->setPosition(pLevelItem->getPositionX(), -90);
    m_pContentLayer->addChild(pEnergyItem);
    
    PropertyItem* pPowerItem = PropertyItem::create(PropertyItem::TYPE_ITEM, FIND_USER_MODEL->getTotalPowerNum(), false);
    pPowerItem->setPosition(pGoldItem->getPositionX(), -90);
    m_pContentLayer->addChild(pPowerItem);
    
    SimpleButton* pConfirmButton = SimpleButton::create(btnColor::GREEN, Size(300, 95), this, callfuncO_selector(AbroadFindUserDataWindow::onConfirmButtonPressed));
    pConfirmButton->setPositionY(-215);
    pConfirmButton->setLabel(GAME_TEXT_MODEL->getText("data_recovery_btn_1"), TTF_CONFIG_30_OUTLINE, Color4B::WHITE, GREEN_OUTLINE_COLOR);
    Utility::resizeLabelByWidth(pConfirmButton->getContentLabel(), 260);
    m_pContentLayer->addChild(pConfirmButton);
    
    SimpleButton* pFindOtherButton = SimpleButton::create(btnColor::YELLOW, Size(300, 95), this, callfuncO_selector(AbroadFindUserDataWindow::onFindOtherIdButtonPressed));
    pFindOtherButton->setPositionY(-325);
    pFindOtherButton->setLabel(GAME_TEXT_MODEL->getText("data_recovery_btn_2"), TTF_CONFIG_30_OUTLINE, Color4B::WHITE, YELLOW_OUTLINE_COLOR);
    Utility::resizeLabelByWidth(pFindOtherButton->getContentLabel(), 260);
    m_pContentLayer->addChild(pFindOtherButton);
    
    UIEditInterface::init(m_pContentLayer);
    return true;
}

void AbroadFindUserDataWindow::onCloseButtonPressed(Ref* pObject)
{
    exitWithAnimation();
    NOTIFICATION_CENTER->postNotification(EVENT_CHECK_VENDOR_FINISH);
}

void AbroadFindUserDataWindow::onConfirmButtonPressed(Ref* pObject)
{
    FIND_USER_MODEL->updateDeviceInfo();
}

void AbroadFindUserDataWindow::onFindOtherIdButtonPressed(Ref* pObject)
{
    exitWithAnimation();
    FIND_USER_MODEL->openFindUserDataByIdWindow();
}

AbroadFindUserDataWindow::~AbroadFindUserDataWindow()
{
    NOTIFICATION_CENTER->removeAllObservers(this);
}


#pragma mark FindUserDataByIdWindow
bool FindUserDataByIdWindow::init()
{
    BasePopupWindow::init();
    
    WindowBackground* pBackGround = WindowBackground::create(WIN_SIZE_TYPE::MIDDLE_WIN, WIN_BANNER_TYPE::GENERAL_BANNER);
    m_pContentLayer->addChild(pBackGround);
    
    Size bgSize = pBackGround->getContentSize();
    
    SimpleButton* pCloseButton = SimpleButton::create(GENERAL_CLOSE_BUTTON_PURPLE, this, callfuncO_selector(FindUserDataByIdWindow::onCloseButtonPressed));
    pCloseButton->setPosition(CLOSE_BUTTON_POINT_MIDDLE);
    pCloseButton->setTouchAreaScale(1.3f);
    m_pContentLayer->addChild(pCloseButton);
    
    Label* pTitleLabel = Utility::createLabel(TTF_CONFIG_TITLE, GAME_TEXT_MODEL->getText("data_recovery_title_2"), TITLE_TEXT_COLOR, Color4B::WHITE, -2.0f);
    Utility::resizeLabelByWidth(pTitleLabel, pBackGround->getContentSize().width-20);
    pTitleLabel->setPositionY(250);
    m_pContentLayer->addChild(pTitleLabel);
    
    Label* pDescLabel = Utility::createLabel(TTF_CONFIG_30_NORMAL, GAME_TEXT_MODEL->getText("data_recovery_desc_2"), MAIN_TEXT_COLOR, Color4B::WHITE, -2.0f);
    pDescLabel->setPosition(0, 32);
    pDescLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
    pDescLabel->setDimensions(bgSize.width-150, 350);
    pDescLabel->setScale(0.85);
    m_pContentLayer->addChild(pDescLabel);
    
    GeneralInnerBoard* pInnerBoard = GeneralInnerBoard::create(Size(614, 380));
    pInnerBoard->setPosition(Point(-27, -65));
    m_pContentLayer->addChild(pInnerBoard);
    
    vector<St_DescConfig> rgFirstCellDescConfig;
    rgFirstCellDescConfig = {
        {GAME_TEXT_MODEL->getText("data_recovery_step_desc_1"), TTF_CONFIG_30_NORMAL, MAIN_TEXT_COLOR, true}
    };
    InviteStepCell* pFirstCell = InviteStepCell::create(1, rgFirstCellDescConfig);
    pFirstCell->setPosition(1, 81);
    pInnerBoard->addChild(pFirstCell);
    
    
    vector<St_DescConfig> rgSecondCellDescConfig;
    rgSecondCellDescConfig = {
        {GAME_TEXT_MODEL->getText("data_recovery_step_desc_2"), TTF_CONFIG_30_NORMAL, MAIN_TEXT_COLOR, true}
    };
    float offsetY = 0;
    if (LOCALIZATION_MODEL->getLanguage() == LANG_KO || LOCALIZATION_MODEL->getLanguage() == LANG_RU)
    {
        offsetY = 12;
    }
    InviteStepCell* pSecondCell = InviteStepCell::create(2, rgSecondCellDescConfig, offsetY);
    pSecondCell->setPosition(pFirstCell->getPositionX(), -86);
    pInnerBoard->addChild(pSecondCell);
    
    m_pMCCBox = MyEditBox::create(MyEditBox::FILTER_ALPHA_DIGIT, GAME_TEXT_MODEL->getText("data_recovery_input_tips"), Size(310, 56));
    m_pMCCBox->getInputField()->setTextColor(SUBTITLE_TEXT_COLOR);
    m_pMCCBox->getInputField()->setString("");
    m_pMCCBox->setAnchorPoint(Point(0.0f, 0.5f));
    m_pMCCBox->setPosition(-240, -37);
    pSecondCell->addChild(m_pMCCBox);
    
    
    SimpleButton* pConfirmButton = SimpleButton::create(btnColor::GREEN, Size(200, 70), this, callfuncO_selector(FindUserDataByIdWindow::onFindUserDataButtonPressed));
    pConfirmButton->setPosition(190, -35);
    pConfirmButton->setLabel(GAME_TEXT_MODEL->getText("data_recovery_btn_3"), TTF_CONFIG_30_OUTLINE, Color4B::WHITE, GREEN_OUTLINE_COLOR);
    Utility::resizeLabelByWidth(pConfirmButton->getContentLabel(), 165);
    pSecondCell->addChild(pConfirmButton);
    pConfirmButton->setScale(0.88f);
    pInnerBoard->setScale(0.91f);
    
    SimpleButton* pRestartButton = SimpleButton::create(btnColor::YELLOW, Size(260, 80), this, callfuncO_selector(FindUserDataByIdWindow::onRestartUserDataButtonPressed));
    pRestartButton->setPositionY(-250);
    pRestartButton->setLabel(GAME_TEXT_MODEL->getText("data_recovery_new_beginning"), TTF_CONFIG_30_NORMAL, MAIN_TEXT_COLOR, GREEN_OUTLINE_COLOR);
    pRestartButton->getBtnSprite()->setVisible(false);
    m_pContentLayer->addChild(pRestartButton);
    pRestartButton->setVisible(false);
    
    NOTIFICATION_CENTER->addObserver(this, callfuncO_selector(FindUserDataByIdWindow::onCloseWindowEvent), EVENT_CLOSE_FIND_DATA_BY_ID_WINDOW, nullptr);
    NOTIFICATION_CENTER->addObserver(this, callfuncO_selector(FindUserDataByIdWindow::onKeyboardShow), EVENT_MYEDITBOX_KEYBOARD_SHOW, nullptr);
    NOTIFICATION_CENTER->addObserver(this, callfuncO_selector(FindUserDataByIdWindow::onKeyboardHide), EVENT_MYEDITBOX_KEYBOARD_HIDE, nullptr);
    
    UIEditInterface::init(m_pContentLayer);
    return true;
}

void FindUserDataByIdWindow::onCloseButtonPressed(Ref* pObject)
{
    exitWithAnimation();
    m_pMCCBox->detachWithIME();
    NOTIFICATION_CENTER->postNotification(EVENT_CHECK_VENDOR_FINISH);
}

void FindUserDataByIdWindow::onCloseWindowEvent(Ref* pObject)
{
    exitWithAnimation();
    m_pMCCBox->detachWithIME();
}

void FindUserDataByIdWindow::onFindUserDataButtonPressed(Ref* pObject)
{
    m_pMCCBox->detachWithIME();
    FIND_USER_MODEL->checkUniqueID(m_pMCCBox->getText());
}

void FindUserDataByIdWindow::onRestartUserDataButtonPressed(Ref* pObject)
{
    m_pMCCBox->detachWithIME();
    BaseMsgBox* pMsgBox = BaseMsgBox::create(BaseMsgBox::YESNO_TYPE);
    pMsgBox->setYesNoEvent(this, callfuncO_selector(FindUserDataByIdWindow::onRestartUserConfirm), NULL, NULL);
    pMsgBox->setMessageContent(GAME_TEXT_MODEL->getText("start_from_beginning"), GAME_TEXT_MODEL->getText("start_from_beginning_desc"));
    CURRENT_SCENE->addChild(pMsgBox);
}

void FindUserDataByIdWindow::onRestartUserConfirm(Ref* pObject)
{
    
}

FindUserDataByIdWindow::~FindUserDataByIdWindow()
{
    NOTIFICATION_CENTER->removeAllObservers(this);
}

void FindUserDataByIdWindow::onKeyboardShow(Ref* pObject)
{
    m_pContentLayer->runAction(MoveTo::create(0.4f, Point(0, 220)));
}

void FindUserDataByIdWindow::onKeyboardHide(Ref* pObject)
{
    m_pContentLayer->runAction(MoveTo::create(0.4f, Point(0, 0)));
}

