  
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
class Attacks {
public:
  std::vector<std::tuple<double, std::string>> hurts;
  std::map<std::string, std::tuple<double, std::string>> specials;
  std::string adjecs[6];
  std::string verb[6];
  Attacks()
  {
    verb[0] = " responds with a ";
    verb[1] = " issues a ";
    verb[2] = " dispatches a ";
    verb[3] = " unleashes a ";
    verb[4] = " sends a ";
    verb[5] = " lets loose a ";
    adjecs[0] = "savage ";
    adjecs[1] = "vicious ";
    adjecs[2] = "whithering ";
    adjecs[3] = "ferocious ";
    adjecs[4] = "unrlenting ";
    adjecs[5] = "brutal ";
    hurts.push_back(std::tuple<double, std::string> (1.65, "punch"));
    hurts.push_back(std::tuple<double, std::string> (1.92, "kick"));
    hurts.push_back(std::tuple<double, std::string> (2.34, "bite"));
    hurts.push_back(std::tuple<double, std::string> (.95, "slap"));
    specials["Goblin"] = std::tuple<int, std::string> (3.1, "Clobbering");
    specials["Vampire"] = std::tuple<int, std::string> (4.20, "Bloodsucking");
  }

};

class ent {
public:
 Point pos;
 char sym[2];
 color_t col;
 double health;
 double dmgPow;
 int battlesWon;
 int id;
 int killCount;
 std::string name;
 std::vector<Items*> inventory;
 direction dir;
 Attacks attack;
 void render();
 double getDmg(int method);
 void fight(Map*, Gui*, int method, double dmg);
 void handleItem(Map*, Gui*);
 void move(Map*, int, int);
 ent(int x, int y, std::string name, char ch, color_t col);
 ~ent();
};

