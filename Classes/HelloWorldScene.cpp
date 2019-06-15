/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <cmath>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	sprite = Sprite::create("Revolver.png");
	this->addChild(sprite);

	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	sprite->setScale(3);
	sprite->setAnchorPoint(Vec2(0.0f, 1.0f));
	sprite->getTexture()->setAliasTexParameters();
	//sprite->setColor(Color3B::RED);

	catSprite = Sprite::create("Sample01.png");
	this->addChild(catSprite);
	catSprite->setPosition(Vec2(0, visibleSize.height / 2));
	catSprite->setScale(3);
	catSprite->getTexture()->setAliasTexParameters();

	animIndex = 0;
	animRects[0] = Rect(0, 64, 32, 32);
	animRects[1] = Rect(32, 64, 32, 32);
	animRects[2] = Rect(64, 64, 32, 32);

	catSprite->setTextureRect(animRects[0]);
	catMove = Vec2(10, 0);

	laserSprite = Sprite::create("Pixel.png");
	this->addChild(laserSprite);
	laserSprite->setAnchorPoint(Vec2(0, 0.5f));
	laserSprite->setPosition(Vec2(0, visibleSize.height / 2));
	laserSprite->setRotation(-30);

	this->scheduleUpdate();

	alpha = 255;
	nextPos = 0;

	//¶ã
	points[0] = Vec2(visibleSize.width - 128, visibleSize.height - 128);
	//‰Eã
	points[1] = Vec2(128, visibleSize.height - 128);
	//‰E‰º
	points[2] = Vec2(128, 128);
	//¶‰º
	points[3] = Vec2(visibleSize.width - 128, 128);
	catAnimEnd = false;
	return true;
}

void HelloWorld::update(float delta)
{
	float rotation = sprite->getRotation();
	sprite->setRotation(rotation + 1);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	animTime += delta;
	CatAnim();
	LaserAnim();
	//Vec2 pos = catSprite->getPosition();
	//if (pos.x >= visibleSize.width || pos.x <= 0)
	//	catMove *= -1;
	//pos += catMove;
	//catSprite->setPosition(pos);

	//catSprite->setFlippedX(catMove.x < 0);

	//animTime += delta;
	//if (animTime >= 0.25f)
	//{
	//	animTime = 0;
	//	if (!animPingPongFlag)
	//		animIndex += 1;
	//	else
	//		animIndex -= 1;
	//}

	//if (animIndex < 0 || animIndex > 2)
	//	animPingPongFlag = !animPingPongFlag;

	//animIndex = std::min(2, std::max(0, animIndex));

	//catSprite->setTextureRect(animRects[animIndex]);

	//Color3B color = sprite->getColor();
	//float blue = color.b;
	//float red = color.r;
	//blue += 255 / 3 * delta;
	//red -= 255 / 3 * delta;

	//if (blue >= 255)
	//	blue = 255;
	//if (red <= 0)
	//	red = 0;

	//color.b = blue;
	//color.r = red;

	//sprite->setColor(color);

	//Vec2 pos = sprite->getPosition();
	//if ((points[nextPos] - pos).getLength() < 1)
	//{
	//	nextPos += 1;
	//	if (nextPos == 4)
	//		nextPos = 0;
	//}

	//Vec2 velocity = points[nextPos] - pos;
	//velocity.normalize();
	//pos = pos + velocity;
	//sprite->setPosition(pos);

	/*alpha -= 255 / 5 * delta;
	if (alpha >= 0)
		sprite->setOpacity((int)alpha);*/

		//float alpha1 = sprite->getOpacity();
		//float alpha2 = sprite2->getOpacity();

		//alpha1 -= 255 / 5 * delta;
		//if (alpha1 >= 0)
		//	sprite->setOpacity((int)alpha1);

		//alpha2 += 255 / 5 * delta;
		//if (alpha2 <= 255)
		//	sprite2->setOpacity((int)alpha2);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}

void HelloWorld::CatAnim()
{
	if (catAnimEnd) return;

	if (animTime >= 0.5f)
	{
		animTime = 0;
		if (!animPingPongFlag)
			animIndex += 1;
		else
			animIndex -= 1;
	}

	if (animIndex == 3)
	{
		animIndex = 1;
		catAnimEnd = true;
		laserSprite->setPosition(catSprite->getPosition());
	}

	catSprite->setTextureRect(animRects[animIndex]);
	Vec2 pos = catSprite->getPosition();
	pos += Vec2(1, 0);
	catSprite->setPosition(pos);
}

void HelloWorld::LaserAnim()
{
	if (!catAnimEnd) return;

	float rotation = laserSprite->getRotation();
	if (rotation < 30)
		rotation += 0.5f;
	laserSprite->setRotation(rotation);

	if (scaleY < 50)
		scaleX += 200;
	laserSprite->setScaleX(scaleX);

	if (scaleX < 200 * 60 * 1.5f && scaleY < 50)
		scaleY += 2.5f;
	else if (scaleY > 0)
		scaleY -= 2.5f;
	laserSprite->setScaleY(scaleY);
}
