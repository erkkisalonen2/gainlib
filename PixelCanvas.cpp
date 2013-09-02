/*
 * PixelCanvas.cpp
 *
 *  Created on: Feb 2, 2013
 *      Author: villekankainen
 */

#include "PixelCanvas.h"

namespace Gain {

static const char gVertexShader[] =
        "attribute vec2 coord2d;\n"
		"attribute vec2 texcoord;"
		"varying vec2 f_texcoord;"
		"uniform mat4 anim;"
		"void main() {\n"
		"  gl_Position = anim * vec4(coord2d.x, -coord2d.y, 0.0, 1.0);"
		"  f_texcoord = texcoord;"
		"}\n";

static const char gFragmentShader[] =
        "precision mediump float;\n"
		"varying vec2 f_texcoord;"
		"uniform sampler2D mytexture;"
		"uniform vec4 color;"

		"void main(void) {"
		"  vec2 flipped_texcoord = vec2(f_texcoord.x, f_texcoord.y);"
		"  gl_FragColor = texture2D(mytexture, flipped_texcoord)*color;"
		"}"
		;

PixelCanvas::PixelCanvas(int x,int y, int width, int height) :
		super(x,y,width,height, gVertexShader, gFragmentShader)
{
    pMaxPixelBufferSize = width*height;
    pBitmap = (unsigned char*)malloc(pMaxPixelBufferSize*4 + 4);
    memset(pBitmap,0x00,pMaxPixelBufferSize*4);
//    memset(pPixelBuffer+pMaxPixelBufferSize*2,0x00,pMaxPixelBufferSize*2);
}

PixelCanvas::~PixelCanvas() {
	// TODO Auto-generated destructor stub
}

bool PixelCanvas::initVariables()
{
	if(!super::initVariables()) {
		return false;
	}

	const char* attribute_name;
	const char* uniform_name;

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
	        GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
			GL_CLAMP_TO_EDGE);

	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, /*GL10.GL_REPLACE*/ GL_MODULATE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	glTexImage2D(GL_TEXTURE_2D, // target
			0,  // level, 0 = base, no minimap,
            GL_RGBA, // internalformat
			pBitmapWidth,  // width
			pBitmapHeight,  // height
			0,  // border, always 0 in OpenGL ES
			GL_RGBA,  // format
			GL_UNSIGNED_BYTE, // type
			pBitmap);
	checkGlError("glTexImage2D");
	updateBitmap = false;

	GLfloat square_texcoords[] = {
			// front
			0.0, 0.0,
			1.0, 0.0,
			1.0, 1.0,
			0.0, 1.0,
	};
    GL_EXT_FUNC glGenBuffers(1, &vbo_square_texcoords);
	checkGlError("glGenBuffers");

    GL_EXT_FUNC glBindBuffer(GL_ARRAY_BUFFER, vbo_square_texcoords);
	checkGlError("glBindBuffer");

    GL_EXT_FUNC glBufferData(GL_ARRAY_BUFFER, sizeof(square_texcoords), square_texcoords, GL_STATIC_DRAW);
	checkGlError("glBufferData");

	return true;
}



void PixelCanvas::updateG(float time, float timeDelta) 
{
	super::updateG( time,  timeDelta);
}


void PixelCanvas::enableAttributes() 
{
	super::enableAttributes();

	if(updateBitmap)
	{
		GL_EXT_FUNC glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
						GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
						GL_CLAMP_TO_EDGE);

		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, /*GL10.GL_REPLACE*/ GL_MODULATE);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexImage2D(GL_TEXTURE_2D, // target
				0,  // level, 0 = base, no minimap,
	            GL_RGBA, // internalformat
				pBitmapWidth,  // width
				pBitmapHeight,  // height
				0,  // border, always 0 in OpenGL ES
				GL_RGBA,  // format
				GL_UNSIGNED_BYTE, // type
				pBitmap);
		updateBitmap = false;

		GL_EXT_FUNC glUniform1i(uniform_mytexture, 0);

		GL_EXT_FUNC glEnableVertexAttribArray(attribute_texcoord);
		GL_EXT_FUNC glBindBuffer(GL_ARRAY_BUFFER, vbo_square_texcoords);
		GL_EXT_FUNC glVertexAttribPointer(
				attribute_texcoord, // attribute
				2,                  // number of elements per vertex, here (x,y)
				GL_FLOAT,           // the type of each element
				GL_FALSE,           // take our values as-is
				0,                  // no extra data between each position
				0                   // offset of first element
		);
	}
}

void PixelCanvas::disableAttributes() {
    GL_EXT_FUNC glDisableVertexAttribArray(attribute_texcoord);
	super::disableAttributes();
}

void PixelCanvas::setPixel(int x, int y, unsigned int abgr)
{
	int width = pBitmapWidth;
    unsigned int location = y*width + x;

	int* buffer = (int*)pBitmap;
    if(buffer && location < pMaxPixelBufferSize)
    {
		buffer[location] = abgr;
    }
	updateBitmap = true;
}

void PixelCanvas::setPixel(int x, int y, char a,char b,char g,char r)
{
	unsigned int value =  a<<24 | b<<16 | g<<8 | r;
	setPixel(x,y,value);
}

} /* namespace Gain */
