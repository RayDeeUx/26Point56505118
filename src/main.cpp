#include <Geode/modify/GJRotationControl.hpp>
#include <numbers>

using namespace geode::prelude;

#define ARCTAN_ONE_HALF 26.56505117707798935157219372045329467120421429964522102798601631528806582148474061170857381060216472f

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
	void setRotationTo(const float newAngle) {
		if (!m_delegate) return;
		m_delegate->angleChangeBegin();
		m_delegate->angleChanged(newAngle);
		m_delegate->angleChangeEnded();
		this->setThumbValue(newAngle);
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
		MyGJRotationControl::setRotationTo(this->getThumbValue() + (!isCCW ? ARCTAN_ONE_HALF : -ARCTAN_ONE_HALF));
	}
	void on26Point56505118(CCObject* sender) {
		if (!sender || !m_delegate || sender->getTag() != 20260114) return;
		this->setRotationTo2656505118(false);
	}
	void onNinetyMinus26Point56505118(CCObject* sender) {
		if (!sender || !m_delegate || sender->getTag() != 20260114) return;
		this->setRotationTo2656505118(true);
	}
	void setRotationTo2656505118(const bool subtractFromNinety) {
		MyGJRotationControl::setRotationTo(!subtractFromNinety ? ARCTAN_ONE_HALF : (90.f - ARCTAN_ONE_HALF));
	}
	void on26Point56505118Mirrored(CCObject* sender) {
		if (!sender || !m_delegate || sender->getTag() != 20260114) return;
		this->setRotationTo2656505118Mirrored(false);
	}
	void onNinetyMinus26Point56505118Mirrored(CCObject* sender) {
		if (!sender || !m_delegate || sender->getTag() != 20260114) return;
		this->setRotationTo2656505118Mirrored(true);
	}
	void setRotationTo2656505118Mirrored(const bool subtractFromNinety) {
		MyGJRotationControl::setRotationTo(-1.f * (!subtractFromNinety ? ARCTAN_ONE_HALF : (90.f - ARCTAN_ONE_HALF)));
	}
	bool init() {
		if (!GJRotationControl::init()) return false;

		auto menu = CCMenu::create();
		menu->setScale(.6f);
		menu->setID("26-point-56505118-menu"_spr);
		menu->setPosition(0.f, 100.f);

		const bool highPrecisionRotation = Loader::get()->isModLoaded("kxtbit.high_precision_editor") && Loader::get()->getLoadedMod("kxtbit.high_precision_editor")->getSettingValue<bool>("full-precision-object-rotation");
		const std::string& determinedSpriteText = highPrecisionRotation ? "26.56505118" : "26.57";
		const std::string& theOtherThing = highPrecisionRotation ? "63.4349488229" : "63.43";

		const std::string& determinedSpriteFrameName = Loader::get()->isModLoaded("hjfod.betteredit") ? "hjfod.betteredit/button-empty.png" : "geode.loader/black-square.png";

		ButtonSprite* buttonSpriteCCW = ButtonSprite::create(fmt::format("-={}", determinedSpriteText).c_str(), "bigFont.fnt", determinedSpriteFrameName.c_str(), .8f);
		buttonSpriteCCW->setScale(.65f);
		buttonSpriteCCW->setID("26-point-56505118-counterclockwise-sprite"_spr);
		CCMenuItemSpriteExtra* buttonCCW = CCMenuItemSpriteExtra::create(buttonSpriteCCW, this, menu_selector(MyGJRotationControl::onCCW26Point56505118));
		buttonCCW->setTag(12102025);
		buttonCCW->setID("26-point-56505118-counterclockwise"_spr);
		menu->addChild(buttonCCW);

		ButtonSprite* buttonSpriteCW = ButtonSprite::create(fmt::format("+={}", determinedSpriteText).c_str(), "bigFont.fnt", determinedSpriteFrameName.c_str(), .8f);
		buttonSpriteCW->setScale(.65f);
		buttonSpriteCW->setID("26-point-56505118-clockwise-sprite"_spr);
		CCMenuItemSpriteExtra* buttonCW = CCMenuItemSpriteExtra::create(buttonSpriteCW, this, menu_selector(MyGJRotationControl::onCW26Point56505118));
		buttonCW->setTag(12102025);
		buttonCW->setID("26-point-56505118-clockwise"_spr);
		menu->addChild(buttonCW);

		ButtonSprite* buttonSpriteRSU = ButtonSprite::create(fmt::format("+{}", determinedSpriteText).c_str(), "bigFont.fnt", determinedSpriteFrameName.c_str(), .7f);
		buttonSpriteRSU->setScale(.65f);
		buttonSpriteRSU->setID("26-point-56505118-right-side-up-sprite"_spr);
		CCMenuItemSpriteExtra* buttonRSU = CCMenuItemSpriteExtra::create(buttonSpriteRSU, this, menu_selector(MyGJRotationControl::on26Point56505118));
		buttonRSU->setTag(20260114);
		buttonRSU->setID("26-point-56505118-right-side-up"_spr);
		menu->addChild(buttonRSU);

		ButtonSprite* buttonSpriteRSUM = ButtonSprite::create(fmt::format("-{}", determinedSpriteText).c_str(), "bigFont.fnt", determinedSpriteFrameName.c_str(), .7f);
		buttonSpriteRSUM->setScale(.65f);
		buttonSpriteRSUM->setID("26-point-56505118-right-side-up-mirrored-sprite"_spr);
		CCMenuItemSpriteExtra* buttonRSUM = CCMenuItemSpriteExtra::create(buttonSpriteRSUM, this, menu_selector(MyGJRotationControl::on26Point56505118Mirrored));
		buttonRSUM->setTag(20260114);
		buttonRSUM->setID("26-point-56505118-right-side-up-mirrored"_spr);
		menu->addChild(buttonRSUM);

		ButtonSprite* buttonSpriteTTR = ButtonSprite::create(fmt::format("+{}", theOtherThing).c_str(), "bigFont.fnt", determinedSpriteFrameName.c_str(), .7f);
		buttonSpriteTTR->setScale(.65f);
		buttonSpriteTTR->setID("26-point-56505118-to-the-right-sprite"_spr);
		CCMenuItemSpriteExtra* buttonTTR = CCMenuItemSpriteExtra::create(buttonSpriteTTR, this, menu_selector(MyGJRotationControl::onNinetyMinus26Point56505118));
		buttonTTR->setTag(20260114);
		buttonTTR->setID("26-point-56505118-to-the-right"_spr);
		menu->addChild(buttonTTR);

		ButtonSprite* buttonSpriteTTRM = ButtonSprite::create(fmt::format("-{}", theOtherThing).c_str(), "bigFont.fnt", determinedSpriteFrameName.c_str(), .7f);
		buttonSpriteTTRM->setScale(.65f);
		buttonSpriteTTRM->setID("26-point-56505118-to-the-right-mirrored-sprite"_spr);
		CCMenuItemSpriteExtra* buttonTTRM = CCMenuItemSpriteExtra::create(buttonSpriteTTRM, this, menu_selector(MyGJRotationControl::onNinetyMinus26Point56505118Mirrored));
		buttonTTRM->setTag(20260114);
		buttonTTRM->setID("26-point-56505118-to-the-right-mirrored"_spr);
		menu->addChild(buttonTTRM);

		menu->setContentWidth(buttonCCW->getContentWidth() + buttonCW->getContentWidth());
		menu->setLayout(RowLayout::create()->setAutoScale(true)->setCrossAxisOverflow(true)->setGrowCrossAxis(true));
		this->addChild(menu);

		return true;
	}
};