/*
 * Bitmap.h
 *
 *  Created on: Feb 2, 2013
 *      Author: villekankainen
 */

#ifndef RECT_H_
#define RECT_H_

#include <queue>
#include <map>

#include "Base.h"


namespace Gain {

typedef enum _Placement
{
	PLACEMENT_LEFT   = 0x02,
	PLACEMENT_RIGHT  = 0x01,
	PLACEMENT_TOP    = 0x20,
	PLACEMENT_BOTTOM = 0x10,

	TOP_LEFT      = 0x22,
	TOP_CENTER    = 0x20,
	TOP_RIGHT     = 0x21,

	MID_LEFT      = 0x02,
	MID_CENTER    = 0x00,
	MID_RIGHT     = 0x01,

	BOT_LEFT      = 0x12,
	BOT_CENTER    = 0x10,
	BOT_RIGHT     = 0x11

} Placement;

typedef enum _AnimationType
{
	ANIM_NONE=0,
	ANIM_MOVE,
	ANIM_COLOR
} AnimationType;

typedef struct _AnimationContainer
{
public:


	float elapsedTime, time;

	float startX,startY;
	float targetX, targetY;

	//Animation
} AnimationContainer;

class Rect: public Gain::Base {
public:
	Rect(int x, int y, int width, int height, const char* vertexShader=NULL, const char* fragmentShader=NULL);
	Rect(float x, float y, float width, float height, const char* vertexShader=NULL, const char* fragmentShader=NULL);
	Rect(const char* vertexShader=NULL, const char* fragmentShader=NULL);
private:
	void privateConstruct(const char* vertexShader, const char* fragmentShader);
public:
	virtual ~Rect();

	Rect* set(int x, int y, int width, int height);
	virtual Rect* setN(float x, float y, float width, float height);

	Rect* setX(int x);
	Rect* setY(int y);

	virtual Rect* setXN(float x);
	virtual Rect* setYN(float y);

	float getXN();
	float getYN();

	Rect* setWidth(int width);
	Rect* setHeight(int height);
	virtual Rect* setWidthN(float width);
	virtual Rect* setHeightN(float height);

	Rect* setSizeN(float width, float height);
	Rect* setPositionN(float x,float y,Placement placement);

	virtual Rect* setPlacement(Placement aPlacement);



	Rect* setCenterN(float x, float y);
	Rect* setCornersN(
			float tl_x, float tl_y,
			float tr_x, float tr_y,
			float bl_x, float bl_y,
			float br_x, float br_y
			);

	Rect* setColor(GLfloat color[4]);
	Rect* setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

	Rect* setRotation(GLfloat angle);

	//Base
	virtual bool setupGraphics();
	virtual void render() const;
	virtual void updateG(float time, float deltaTime);

	virtual void moveToN(float targetX, float targetY, float sec);

	virtual bool isWithin(float nX, float nY);
protected:
	virtual bool initVariables();
	virtual void enableAttributes() const;
	virtual void disableAttributes() const;

	virtual void updateAnimation(float sec, float deltaSec);




//	float pXcenter,pYcenter,pWidth,pHeight;

	float pHalfWidth,pHalfHeight;
	float pPositionX, pPositionY;

	Placement pPlacement;

	GLfloat pAngle;

	GLint attribute_coord2d;
	GLuint vbo_square_vertices;
	GLuint ibo_square_elements;

public:
	glm::mat4 anim;
	GLfloat square_vertices[8];
protected:

	GLint uniform_anim;
	GLint uniform_color;

	GLfloat trunslate[2];

	GLfloat TODO_fix_this_add_memoryleakage;
	GLfloat color[4];

	glm::mat4 translate_mat;
	glm::mat4 translate_parent;
	glm::mat4 scale;
	glm::mat4 rotate;

	const char* pVertexShader;
	const char* pFragmentShader;

	std::queue<AnimationContainer*> pAnimationList;
};

} /* namespace Gain */
#endif /* RECT_H_ */
