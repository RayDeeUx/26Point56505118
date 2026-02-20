#include <Geode/modify/GJRotationControl.hpp>
#include <numbers>

using namespace geode::prelude;

#define ARCTAN_ONE_HALF 26.56505117707798935157219372045329467120421429964522102798601631528806582148474061170857381060216472f

class $modify(MyGJRotationControl, GJRotationControl) {
	// stolen from hjfod
	static float angleOfPointOnCircle(const CCPoint& point) {
		return std::atan2f(point.y, point.x) * (180.f / std::numbers::pi_v<float>);
	}
	static CCPoint pointOnCircle(const float degrees, const float radius) {
		return ccp(
			std::cosf(degrees * std::numbers::pi_v<float> / 180.f) * radius,
			std::sinf(degrees * std::numbers::pi_v<float> / 180.f) * radius
		);
	}
	float getThumbValue() const {
		return -MyGJRotationControl::angleOfPointOnCircle(m_controlPosition) + 90;
	}
	void setThumbValue(float value) {
		value = -value + 90;
		m_controlPosition = MyGJRotationControl::pointOnCircle(value, 60);
		m_controlSprite->setPosition(m_controlPosition);
	}
	void setRotationTo(const float newAngle) {
		if (!m_delegate) return;
		m_delegate->angleChangeBegin();
		m_delegate->angleChanged(newAngle);
		m_delegate->angleChangeEnded();
		this->setThumbValue(newAngle);
	}
	void onCWTwentySix(CCObject* sender) {
		if (!sender || !m_delegate || sender->getTag() != 12102025) return;
		this->rotateObjectBy2656505118(false);
	}
	void onCCWTwentySix(CCObject* sender) {
		if (!sender || !m_delegate || sender->getTag() != 12102025) return;
		this->rotateObjectBy2656505118(true);
	}
	void rotateObjectBy2656505118(const bool isCCW) {
		MyGJRotationControl::setRotationTo(this->getThumbValue() + (!isCCW ? ARCTAN_ONE_HALF : -ARCTAN_ONE_HALF));
	}
	void onTwentySix(CCObject* sender) {
		if (!sender || !m_delegate || sender->getTag() != 20260114) return;
		this->setRotationTo2656505118(false);
	}
	void onSixtyThree(CCObject* sender) {
		if (!sender || !m_delegate || sender->getTag() != 20260114) return;
		this->setRotationTo2656505118(true);
	}
	void setRotationTo2656505118(const bool subtractFromNinety) {
		MyGJRotationControl::setRotationTo(!subtractFromNinety ? ARCTAN_ONE_HALF : (90.f - ARCTAN_ONE_HALF));
	}
	void onNegativeTwentySix(CCObject* sender) {
		if (!sender || !m_delegate || sender->getTag() != 20260114) return;
		this->setRotationToNegTwentySixOrNegSixtyThree(false);
	}
	void onNegativeSixtyThree(CCObject* sender) {
		if (!sender || !m_delegate || sender->getTag() != 20260114) return;
		this->setRotationToNegTwentySixOrNegSixtyThree(true);
	}
	void setRotationToNegTwentySixOrNegSixtyThree(const bool subtractFromNinety) {
		MyGJRotationControl::setRotationTo(-1.f * (!subtractFromNinety ? ARCTAN_ONE_HALF : (90.f - ARCTAN_ONE_HALF)));
	}
	void onOneHundredFiftyThree(CCObject* sender) {
		if (!sender || !m_delegate || sender->getTag() != 20260114) return;
		MyGJRotationControl::setRotationToOneHundredFiftyThree(false);
	}
	void onNegativeOneHundredFiftyThree(CCObject* sender) {
		if (!sender || !m_delegate || sender->getTag() != 20260114) return;
		MyGJRotationControl::setRotationToOneHundredFiftyThree(true);
	}
	void setRotationToOneHundredFiftyThree(const bool makeNegative) {
		MyGJRotationControl::setRotationTo((!makeNegative ? 1.f : -1.f) * (180.f - ARCTAN_ONE_HALF));
	}
	void onOneHundredSixteen(CCObject* sender) {
		if (!sender || !m_delegate || sender->getTag() != 20260114) return;
		MyGJRotationControl::setRotationToOneHundredSixteen(false);
	}
	void onNegativeOneHundredSixteen(CCObject* sender) {
		if (!sender || !m_delegate || sender->getTag() != 20260114) return;
		MyGJRotationControl::setRotationToOneHundredSixteen(true);
	}
	void setRotationToOneHundredSixteen(const bool makeNegative) {
		MyGJRotationControl::setRotationTo((!makeNegative ? 1.f : -1.f) * (90.f + ARCTAN_ONE_HALF));
	}
	bool init() {
		if (!GJRotationControl::init()) return false;

		CCMenu* menu = CCMenu::create();
		menu->setScale(.6f);
		menu->setID("26-point-56505118-menu"_spr);
		menu->setPosition(0.f, 80.f);
		menu->setAnchorPoint({.5, .0});

		const std::string& determinedSpriteFrameName = Loader::get()->isModLoaded("hjfod.betteredit") ? "hjfod.betteredit/button-empty.png" : "geode.loader/black-square.png";

		ButtonSprite* buttonSpriteCCW = ButtonSprite::create("-=26.56505118", "bigFont.fnt", determinedSpriteFrameName.c_str(), .8f);
		buttonSpriteCCW->setScale(.65f);
		buttonSpriteCCW->setID("26-point-56505118-counterclockwise-sprite"_spr);
		CCMenuItemSpriteExtra* buttonCCW = CCMenuItemSpriteExtra::create(buttonSpriteCCW, this, menu_selector(MyGJRotationControl::onCCWTwentySix));
		buttonCCW->setTag(12102025);
		buttonCCW->setID("26-point-56505118-counterclockwise"_spr);
		menu->addChild(buttonCCW);

		ButtonSprite* buttonSpriteCW = ButtonSprite::create("+=26.56505118", "bigFont.fnt", determinedSpriteFrameName.c_str(), .8f);
		buttonSpriteCW->setScale(.65f);
		buttonSpriteCW->setID("26-point-56505118-clockwise-sprite"_spr);
		CCMenuItemSpriteExtra* buttonCW = CCMenuItemSpriteExtra::create(buttonSpriteCW, this, menu_selector(MyGJRotationControl::onCWTwentySix));
		buttonCW->setTag(12102025);
		buttonCW->setID("26-point-56505118-clockwise"_spr);
		menu->addChild(buttonCW);

		CCSprite* negativeTwentySixSlope = GameObject::createWithKey(674);
		CCSprite* negativeTwentySixDashOrb = GameObject::createWithKey(1704);
		negativeTwentySixDashOrb->setRotation(-ARCTAN_ONE_HALF);
		negativeTwentySixDashOrb->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(0.f), CCDelayTime::create(1.f), CCFadeIn::create(0.f), CCDelayTime::create(1.f), nullptr)));
		CCSprite* negativeTwentySixYellowGravityPortal = GameObject::createWithKey(11);
		negativeTwentySixYellowGravityPortal->setRotation(-ARCTAN_ONE_HALF);
		negativeTwentySixYellowGravityPortal->setOpacity(0);
		negativeTwentySixYellowGravityPortal->setScale(.85f);
		negativeTwentySixYellowGravityPortal->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.f), CCDelayTime::create(1.f), CCFadeOut::create(0.f), CCDelayTime::create(1.f), nullptr)));
		negativeTwentySixSlope->addChildAtPosition(negativeTwentySixDashOrb, Anchor::Center);
		negativeTwentySixSlope->addChildAtPosition(negativeTwentySixYellowGravityPortal, Anchor::Center);
		negativeTwentySixSlope->setColor({255, 127, 0});
		ButtonSprite* buttonSpriteNegativeTwentySix = ButtonSprite::create(negativeTwentySixSlope, 30, 30, 30.f, 1.f, false); // ButtonSprite::create(fmt::format("-{}", twentySix).c_str(), "bigFont.fnt", determinedSpriteFrameName.c_str(), .7f);
		buttonSpriteNegativeTwentySix->updateBGImage(determinedSpriteFrameName.c_str());
		buttonSpriteNegativeTwentySix->setScale(.65f);
		buttonSpriteNegativeTwentySix->setID("26-point-56505118-negative-twenty-six-sprite"_spr);
		CCMenuItemSpriteExtra* buttonNegativeTwentySix = CCMenuItemSpriteExtra::create(buttonSpriteNegativeTwentySix, this, menu_selector(MyGJRotationControl::onNegativeTwentySix));
		buttonNegativeTwentySix->setTag(20260114);
		buttonNegativeTwentySix->setID("26-point-56505118-negative-twenty-six"_spr);
		menu->addChild(buttonNegativeTwentySix);

		CCSprite* twentySixSlope = GameObject::createWithKey(674);
		twentySixSlope->setRotation(180.f);
		twentySixSlope->setFlipX(true);
		CCSprite* twentySixDashOrb = GameObject::createWithKey(1704);
		twentySixDashOrb->setRotation(ARCTAN_ONE_HALF - twentySixSlope->getRotation());
		twentySixDashOrb->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(0.f), CCDelayTime::create(1.f), CCFadeIn::create(0.f), CCDelayTime::create(1.f), nullptr)));
		CCSprite* twentySixYellowGravityPortal = GameObject::createWithKey(11);
		twentySixYellowGravityPortal->setRotation(ARCTAN_ONE_HALF - twentySixSlope->getRotation());
		twentySixYellowGravityPortal->setOpacity(0);
		twentySixYellowGravityPortal->setScale(.85f);
		twentySixYellowGravityPortal->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.f), CCDelayTime::create(1.f), CCFadeOut::create(0.f), CCDelayTime::create(1.f), nullptr)));
		twentySixSlope->addChildAtPosition(twentySixDashOrb, Anchor::Center);
		twentySixSlope->addChildAtPosition(twentySixYellowGravityPortal, Anchor::Center);
		twentySixSlope->setColor({255, 127, 0});
		ButtonSprite* buttonSpriteTwentySix = ButtonSprite::create(twentySixSlope, 30, 30, 30.f, 1.f, false); // ButtonSprite::create(fmt::format("+{}", twentySix).c_str(), "bigFont.fnt", determinedSpriteFrameName.c_str(), .7f);
		buttonSpriteTwentySix->updateBGImage(determinedSpriteFrameName.c_str());
		buttonSpriteTwentySix->setScale(.65f);
		buttonSpriteTwentySix->setID("26-point-56505118-twenty-six-sprite"_spr);
		CCMenuItemSpriteExtra* buttonTwentySix = CCMenuItemSpriteExtra::create(buttonSpriteTwentySix, this, menu_selector(MyGJRotationControl::onTwentySix));
		buttonTwentySix->setTag(20260114);
		buttonTwentySix->setID("26-point-56505118-twenty-six"_spr);
		menu->addChild(buttonTwentySix);

		CCSprite* negativeSixtyThreeSlope = GameObject::createWithKey(674);
		negativeSixtyThreeSlope->setRotation(-90.f);
		negativeSixtyThreeSlope->setFlipY(true);
		CCSprite* negativeSixtyThreeDashOrb = GameObject::createWithKey(1704);
		negativeSixtyThreeDashOrb->setRotation(ARCTAN_ONE_HALF);
		negativeSixtyThreeDashOrb->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(0.f), CCDelayTime::create(1.f), CCFadeIn::create(0.f), CCDelayTime::create(1.f), nullptr)));
		CCSprite* negativeSixtyThreeYellowGravityPortal = GameObject::createWithKey(11);
		negativeSixtyThreeYellowGravityPortal->setRotation(ARCTAN_ONE_HALF);
		negativeSixtyThreeYellowGravityPortal->setOpacity(0);
		negativeSixtyThreeYellowGravityPortal->setScale(.85f);
		negativeSixtyThreeYellowGravityPortal->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.f), CCDelayTime::create(1.f), CCFadeOut::create(0.f), CCDelayTime::create(1.f), nullptr)));
		negativeSixtyThreeSlope->addChildAtPosition(negativeSixtyThreeDashOrb, Anchor::Center);
		negativeSixtyThreeSlope->addChildAtPosition(negativeSixtyThreeYellowGravityPortal, Anchor::Center);
		negativeSixtyThreeSlope->setColor({255, 127, 0});
		ButtonSprite* buttonSpriteNegativeSixtyThree = ButtonSprite::create(negativeSixtyThreeSlope, 30, 30, 30.f, 1.f, false); // ButtonSprite::create(fmt::format("-{}", sixtyThree).c_str(), "bigFont.fnt", determinedSpriteFrameName.c_str(), .7f);
		buttonSpriteNegativeSixtyThree->updateBGImage(determinedSpriteFrameName.c_str());
		buttonSpriteNegativeSixtyThree->setScale(.65f);
		buttonSpriteNegativeSixtyThree->setID("26-point-56505118-negative-sixty-three-sprite"_spr);
		CCMenuItemSpriteExtra* buttonNegativeSixtyThree = CCMenuItemSpriteExtra::create(buttonSpriteNegativeSixtyThree, this, menu_selector(MyGJRotationControl::onNegativeSixtyThree));
		buttonNegativeSixtyThree->setTag(20260114);
		buttonNegativeSixtyThree->setID("26-point-56505118-negative-sixty-three"_spr);
		menu->addChild(buttonNegativeSixtyThree);

		CCSprite* sixtyThreeSlope = GameObject::createWithKey(674);
		sixtyThreeSlope->setRotation(90.f);
		CCSprite* sixtyThreeDashOrb = GameObject::createWithKey(1704);
		sixtyThreeDashOrb->setRotation(180 - ((-1.f * (90 - ARCTAN_ONE_HALF)) + negativeSixtyThreeSlope->getRotation()));
		sixtyThreeDashOrb->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(0.f), CCDelayTime::create(1.f), CCFadeIn::create(0.f), CCDelayTime::create(1.f), nullptr)));
		CCSprite* sixtyThreeYellowGravityPortal = GameObject::createWithKey(11);
		sixtyThreeYellowGravityPortal->setRotation(180 - ((-1.f * (90 - ARCTAN_ONE_HALF)) + negativeSixtyThreeSlope->getRotation()));
		sixtyThreeYellowGravityPortal->setOpacity(0);
		sixtyThreeYellowGravityPortal->setScale(.85f);
		sixtyThreeYellowGravityPortal->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.f), CCDelayTime::create(1.f), CCFadeOut::create(0.f), CCDelayTime::create(1.f), nullptr)));
		sixtyThreeSlope->addChildAtPosition(sixtyThreeDashOrb, Anchor::Center);
		sixtyThreeSlope->addChildAtPosition(sixtyThreeYellowGravityPortal, Anchor::Center);
		sixtyThreeSlope->setColor({255, 127, 0});
		ButtonSprite* buttonSpriteSixtyThree = ButtonSprite::create(sixtyThreeSlope, 30, 30, 30.f, 1.f, false); // ButtonSprite::create(fmt::format("+{}", sixtyThree).c_str(), "bigFont.fnt", determinedSpriteFrameName.c_str(), .7f);
		buttonSpriteSixtyThree->updateBGImage(determinedSpriteFrameName.c_str());
		buttonSpriteSixtyThree->setScale(.65f);
		buttonSpriteSixtyThree->setID("26-point-56505118-sixty-three-sprite"_spr);
		CCMenuItemSpriteExtra* buttonSixtyThree = CCMenuItemSpriteExtra::create(buttonSpriteSixtyThree, this, menu_selector(MyGJRotationControl::onSixtyThree));
		buttonSixtyThree->setTag(20260114);
		buttonSixtyThree->setID("26-point-56505118-sixty-three"_spr);
		menu->addChild(buttonSixtyThree);

		CCSprite* negativeOneHundredFiftyThreeSlope = GameObject::createWithKey(674);
		negativeOneHundredFiftyThreeSlope->setFlipX(true);
		CCSprite* negativeOneHundredFiftyThreeDashOrb = GameObject::createWithKey(1704);
		negativeOneHundredFiftyThreeDashOrb->setRotation(-1.f * (180 - ARCTAN_ONE_HALF));
		negativeOneHundredFiftyThreeDashOrb->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(0.f), CCDelayTime::create(1.f), CCFadeIn::create(0.f), CCDelayTime::create(1.f), nullptr)));
		CCSprite* negativeOneHundredFiftyThreeYellowGravityPortal = GameObject::createWithKey(11);
		negativeOneHundredFiftyThreeYellowGravityPortal->setRotation(-1.f * (180 - ARCTAN_ONE_HALF));
		negativeOneHundredFiftyThreeYellowGravityPortal->setOpacity(0);
		negativeOneHundredFiftyThreeYellowGravityPortal->setScale(.85f);
		negativeOneHundredFiftyThreeYellowGravityPortal->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.f), CCDelayTime::create(1.f), CCFadeOut::create(0.f), CCDelayTime::create(1.f), nullptr)));
		negativeOneHundredFiftyThreeSlope->addChildAtPosition(negativeOneHundredFiftyThreeDashOrb, Anchor::Center);
		negativeOneHundredFiftyThreeSlope->addChildAtPosition(negativeOneHundredFiftyThreeYellowGravityPortal, Anchor::Center);
		negativeOneHundredFiftyThreeSlope->setColor({255, 127, 0});
		ButtonSprite* buttonSpriteNegativeOneHundredFiftyThree = ButtonSprite::create(negativeOneHundredFiftyThreeSlope, 30, 30, 30.f, 1.f, false); // ButtonSprite::create(fmt::format("-{}", oneHundredFiftyThree).c_str(), "bigFont.fnt", determinedSpriteFrameName.c_str(), .7f);
		buttonSpriteNegativeOneHundredFiftyThree->updateBGImage(determinedSpriteFrameName.c_str());
		buttonSpriteNegativeOneHundredFiftyThree->setScale(.65f);
		buttonSpriteNegativeOneHundredFiftyThree->setID("26-point-56505118-negative-one-hundred-fifty-three-sprite"_spr);
		CCMenuItemSpriteExtra* buttonNegativeOneHundredFiftyThree = CCMenuItemSpriteExtra::create(buttonSpriteNegativeOneHundredFiftyThree, this, menu_selector(MyGJRotationControl::onNegativeOneHundredFiftyThree));
		buttonNegativeOneHundredFiftyThree->setTag(20260114);
		buttonNegativeOneHundredFiftyThree->setID("26-point-56505118-negative-one-hundred-fifty-three"_spr);
		menu->addChild(buttonNegativeOneHundredFiftyThree);

		CCSprite* oneHundredFiftyThreeSlope = GameObject::createWithKey(674);
		oneHundredFiftyThreeSlope->setRotation(180.f);
		CCSprite* oneHundredFiftyThreeDashOrb = GameObject::createWithKey(1704);
		oneHundredFiftyThreeDashOrb->setRotation(-ARCTAN_ONE_HALF);
		oneHundredFiftyThreeDashOrb->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(0.f), CCDelayTime::create(1.f), CCFadeIn::create(0.f), CCDelayTime::create(1.f), nullptr)));
		CCSprite* oneHundredFiftyThreeYellowGravityPortal = GameObject::createWithKey(11);
		oneHundredFiftyThreeYellowGravityPortal->setRotation(-ARCTAN_ONE_HALF);
		oneHundredFiftyThreeYellowGravityPortal->setOpacity(0);
		oneHundredFiftyThreeYellowGravityPortal->setScale(.85f);
		oneHundredFiftyThreeYellowGravityPortal->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.f), CCDelayTime::create(1.f), CCFadeOut::create(0.f), CCDelayTime::create(1.f), nullptr)));
		oneHundredFiftyThreeSlope->addChildAtPosition(oneHundredFiftyThreeDashOrb, Anchor::Center);
		oneHundredFiftyThreeSlope->addChildAtPosition(oneHundredFiftyThreeYellowGravityPortal, Anchor::Center);
		oneHundredFiftyThreeSlope->setColor({255, 127, 0});
		ButtonSprite* buttonSpriteOneHundredFiftyThree = ButtonSprite::create(oneHundredFiftyThreeSlope, 30, 30, 30.f, 1.f, false); // ButtonSprite::create(fmt::format("+{}", oneHundredFiftyThree).c_str(), "bigFont.fnt", determinedSpriteFrameName.c_str(), .7f);
		buttonSpriteOneHundredFiftyThree->updateBGImage(determinedSpriteFrameName.c_str());
		buttonSpriteOneHundredFiftyThree->setScale(.65f);
		buttonSpriteOneHundredFiftyThree->setID("26-point-56505118-one-hundred-fifty-three-sprite"_spr);
		CCMenuItemSpriteExtra* buttonOneHundredFiftyThree = CCMenuItemSpriteExtra::create(buttonSpriteOneHundredFiftyThree, this, menu_selector(MyGJRotationControl::onOneHundredFiftyThree));
		buttonOneHundredFiftyThree->setTag(20260114);
		buttonOneHundredFiftyThree->setID("26-point-56505118-one-hundred-fifty-three"_spr);
		menu->addChild(buttonOneHundredFiftyThree);

		CCSprite* negativeOneHundredSixteenSlope = GameObject::createWithKey(674);
		negativeOneHundredSixteenSlope->setRotation(-90.f);
		CCSprite* negativeOneHundredSixteenDashOrb = GameObject::createWithKey(1704);
		negativeOneHundredSixteenDashOrb->setRotation(-ARCTAN_ONE_HALF);
		negativeOneHundredSixteenDashOrb->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(0.f), CCDelayTime::create(1.f), CCFadeIn::create(0.f), CCDelayTime::create(1.f), nullptr)));
		CCSprite* negativeOneHundredSixteenYellowGravityPortal = GameObject::createWithKey(11);
		negativeOneHundredSixteenYellowGravityPortal->setRotation(-ARCTAN_ONE_HALF);
		negativeOneHundredSixteenYellowGravityPortal->setOpacity(0);
		negativeOneHundredSixteenYellowGravityPortal->setScale(.85f);
		negativeOneHundredSixteenYellowGravityPortal->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.f), CCDelayTime::create(1.f), CCFadeOut::create(0.f), CCDelayTime::create(1.f), nullptr)));
		negativeOneHundredSixteenSlope->addChildAtPosition(negativeOneHundredSixteenDashOrb, Anchor::Center);
		negativeOneHundredSixteenSlope->addChildAtPosition(negativeOneHundredSixteenYellowGravityPortal, Anchor::Center);
		negativeOneHundredSixteenSlope->setColor({255, 127, 0});
		ButtonSprite* buttonSpriteNegativeOneHundredSixteen = ButtonSprite::create(negativeOneHundredSixteenSlope, 30, 30, 30.f, 1.f, false); // ButtonSprite::create(fmt::format("-{}", oneHundredSixteen).c_str(), "bigFont.fnt", determinedSpriteFrameName.c_str(), .7f);
		buttonSpriteNegativeOneHundredSixteen->updateBGImage(determinedSpriteFrameName.c_str());
		buttonSpriteNegativeOneHundredSixteen->setScale(.65f);
		buttonSpriteNegativeOneHundredSixteen->setID("26-point-56505118-negative-one-hundred-sixteen-sprite"_spr);
		CCMenuItemSpriteExtra* buttonNegativeOneHundredSixteen = CCMenuItemSpriteExtra::create(buttonSpriteNegativeOneHundredSixteen, this, menu_selector(MyGJRotationControl::onNegativeOneHundredSixteen));
		buttonNegativeOneHundredSixteen->setTag(20260114);
		buttonNegativeOneHundredSixteen->setID("26-point-56505118-negative-one-hundred-sixteen"_spr);
		menu->addChild(buttonNegativeOneHundredSixteen);

		CCSprite* oneHundredSixteenSlope = GameObject::createWithKey(674);
		oneHundredSixteenSlope->setRotation(-90.f);
		CCSprite* oneHundredSixteenDashOrb = GameObject::createWithKey(1704);
		negativeOneHundredSixteenDashOrb->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(0.f), CCDelayTime::create(1.f), CCFadeIn::create(0.f), CCDelayTime::create(1.f), nullptr)));
		CCSprite* oneHundredSixteenYellowGravityPortal = GameObject::createWithKey(11);
		oneHundredSixteenYellowGravityPortal->setOpacity(0);
		oneHundredSixteenYellowGravityPortal->setScale(.85f);
		oneHundredSixteenYellowGravityPortal->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.f), CCDelayTime::create(1.f), CCFadeOut::create(0.f), CCDelayTime::create(1.f), nullptr)));
		oneHundredSixteenSlope->addChildAtPosition(oneHundredSixteenDashOrb, Anchor::Center);
		oneHundredSixteenSlope->addChildAtPosition(oneHundredSixteenYellowGravityPortal, Anchor::Center);
		oneHundredSixteenSlope->setColor({255, 127, 0});
		ButtonSprite* buttonSpriteOneHundredSixteen = ButtonSprite::create(negativeSixtyThreeSlope, 30, 30, 30.f, 1.f, false); // ButtonSprite::create(fmt::format("+{}", oneHundredSixteen).c_str(), "bigFont.fnt", determinedSpriteFrameName.c_str(), .7f);
		buttonSpriteOneHundredSixteen->updateBGImage(determinedSpriteFrameName.c_str());
		buttonSpriteOneHundredSixteen->setScale(.65f);
		buttonSpriteOneHundredSixteen->setRotation(180.f);
		buttonSpriteOneHundredSixteen->setID("26-point-56505118-one-hundred-sixteen-sprite"_spr);
		CCMenuItemSpriteExtra* buttonOneHundredSixteen = CCMenuItemSpriteExtra::create(buttonSpriteOneHundredSixteen, this, menu_selector(MyGJRotationControl::onOneHundredSixteen));
		buttonOneHundredSixteen->setTag(20260114);
		buttonOneHundredSixteen->setID("26-point-56505118-one-hundred-sixteen"_spr);
		menu->addChild(buttonOneHundredSixteen);

		menu->setContentWidth(265.f);
		menu->setLayout(RowLayout::create()->setAutoScale(true)->setCrossAxisOverflow(true)->setGrowCrossAxis(true));
		this->addChild(menu);

		return true;
	}
};