/****************************************************************
*  MIT License
* 
*  Copyright (c) 2020 Max Goren
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
***************************************************/
#include "master.h"


int main()
{
 int k;
 terminal_open();
 terminal_set("window: title='dj', size=160x45;");
 terminal_setf("font: VeraMoBd.ttf, size=8x16;");
 terminal_set("0xE100: Tiles.png, size=12x16, spacing=1x1;");
 terminal_bkcolor("black");
 engine* eng;
 eng = new engine();
 while(true)
 {
  terminal_clear();
  eng->update();
  terminal_refresh();
 }
 terminal_close();
 return 0;
}