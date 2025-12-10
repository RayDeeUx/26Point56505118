#include <Geode/modify/GJRotationControl.hpp>
#include <numbers>

using namespace geode::prelude;

class $modify(MyGJRotationControl, GJRotationControl) {
	// stolen from hjfod
	static float angleOfPointOnCircle(CCPoint const& point) {
		return atan2f(point.y, point.x) * (180.f / std::numbers::pi_v<float>);
	}
	static CCPoint pointOnCircle(float degrees, float radius) {
		return ccp(
			cosf(degrees * std::numbers::pi_v<float> / 180.f) * radius,
			sinf(degrees * std::numbers::pi_v<float> / 180.f) * radius
		);
	}
	float getThumbValue() const {
		return -angleOfPointOnCircle(m_controlPosition) + 90;
	}
	void setThumbValue(float value) {
		value = -value + 90;
		m_controlPosition = pointOnCircle(value, 60);
		m_controlSprite->setPosition(m_controlPosition);
	}
	void onCW26Point56505118(CCObject* sender) {
		if (!sender || !m_delegate || sender->getTag() != 12102025) return;
		this->rotateObjectBy2656505118(false);
	}
	void onCCW26Point56505118(CCObject* sender) {
		if (!sender || !m_delegate || sender->getTag() != 12102025) return;
		this->rotateObjectBy2656505118(true);
	}
	void rotateObjectBy2656505118(const bool isCCW) {
		if (!m_delegate) return;
		const float newAngle = this->getThumbValue() + (!isCCW ? 26.56505118 : -26.56505118);
                m_delegate->angleChangeBegin();
                m_delegate->angleChanged(newAngle);
                m_delegate->angleChangeEnded();
                this->setThumbValue(newAngle);
	}
	bool init() {
		if (!GJRotationControl::init()) return false;	

		auto menu = CCMenu::create();
		menu->setContentWidth(170.f);
		menu->setID("26-point-56505118-menu"_spr);
		menu->setPosition(0.f, 90.f);

		const std::string& determinedSpriteText = Loader::get()->isModLoaded("kxtbit.high_precision_editor") && Loader::get()->getLoadedMod("kxtbit.high_precision_editor")->getSettingValue<bool>("full-precision-object-rotation") ? "26.56505118" : "26.57";

		const std::string& determinedSpriteFrameName = Loader::get()->isModLoaded("hjfod.betteredit") ? "hjfod.betteredit/button-empty.png" : "geode.loader/black-square.png";

		ButtonSprite* buttonSpriteCCW = ButtonSprite::create(fmt::format("-{}", determinedSpriteText).c_str(), "bigFont.fnt", determinedSpriteFrameName.c_str(), .8f);
        buttonSpriteCCW->setScale(.65f);
		buttonSpriteCCW->setID("26-point-56505118-counterclockwise-sprite"_spr);
		CCMenuItemSpriteExtra* buttonCCW = CCMenuItemSpriteExtra::create(buttonSpriteCCW, this, menu_selector(MyGJRotationControl::onCCW26Point56505118));
		buttonCCW->setTag(12102025);
		buttonCCW->setID("26-point-56505118-counterclockwise"_spr);
		menu->addChild(buttonCCW);

		ButtonSprite* buttonSpriteCW = ButtonSprite::create(fmt::format("+{}", determinedSpriteText).c_str(), "bigFont.fnt", determinedSpriteFrameName.c_str(), .8f);
        buttonSpriteCW->setScale(.65f);
		buttonSpriteCW->setID("26-point-56505118-clockwise-sprite"_spr);
		CCMenuItemSpriteExtra* buttonCW = CCMenuItemSpriteExtra::create(buttonSpriteCW, this, menu_selector(MyGJRotationControl::onCW26Point56505118));
		buttonCW->setTag(12102025);
		buttonCW->setID("26-point-56505118-clockwise"_spr);
		menu->addChild(buttonCW);

		menu->setLayout(RowLayout::create());
		this->addChild(menu);

		return true;
	}
};