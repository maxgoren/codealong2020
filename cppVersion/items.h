  
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
  
  struct stuff {
   public:
    std::string things[25];
    stuff()
    {
      things[0] = "soda";
      things[1] = "eater";
      things[2] = "a brownie";
      things[3] = "beer";
      things[4] = "pain killers";
      things[5] = "penut butter";
      things[6] = "bread";
      things[7] = "sandwich";
      things[8] = "bullets";
      things[9] = "a knife";
      things[10] = "socks";
      things[11] = "salad dressing";
      things[12] = "chinese throwing stars";
      things[13] = "plattic bag";
      things[14] = "weed";
      things[15] = "adderall";
      things[16] = "S&w .40cal";
      things[17] = "tokarev-33";
      things[18] = "corn pops";
      things[19] = "survival book";
      things[20] = "$20";
      things[21] = "$5";
      things[22] = "lucky penny";
      things[23] = "cell phone";
    }
  };

class Items {
    public:
    std::string name;
    Point pos;
    float heals;
    float powers;
    void use(ent* player);
    void render();
    Items(int x, int y, std::string Name, float h, float p);
    Items();
    ~Items();
};