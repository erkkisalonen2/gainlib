// Copyright 2014
//   erkki.salonen@tpnet.fi
//   ville.kankainen@gmail.com
//   ville.kankainen@kangain.com
// 
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TEXT_H_
#define TEXT_H_

#include "Bitmap.h"

namespace Gain {

class Text :
    public Gain::Bitmap
{
private:
	typedef Gain::Bitmap super;


public:
	Text(float x, float y, float pixelSize, const char* text);
	Text(int x, int y, int pixelSize, const char* text);
	virtual ~Text();

	void setText(const char* text);
	char *getText();
	//Base
	virtual void updateG(float time, float timeDelta);


private:
	void internalInit(int pixelSize);

protected:

	virtual bool initVariables();
	virtual void enableAttributes() const;
	virtual void disableAttributes() const;

	char pTextBuffer[256];
	int pPixelSize;
};

} /* namespace Gain */
#endif /* TEXT_H_ */
