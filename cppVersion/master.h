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
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <chrono>
#include <vector>
#include <array>
#include <list>
#include <queue>
#include <map>
#include <random>
#include <thread>
#include <math.h>
#include "BearLibTerminal.h"
#include "queue.h"
#include "helpers.h"
#ifndef engine_h
#define engine_h
class Battle;
class Gui;
class ent;
class engine;
#endif
#ifndef dungeon_h 
#define dungeon_h
class item;
class ent;
class dungeon;
#endif
#include "dungeon.h"
#include "entity.h"
#include "djik.h"
#include "bfirst.h"
#include "engine.h"
#include "gui.h"
#include "items.h"
#include "battle.h"
#include "dungeon.cpp"
#include "roomconnecter.cpp"
#include "djik.cpp"
#include "bfirst.cpp"
#include "battle.cpp"
#include "engine.cpp"
#include "items.cpp"
#include "entity.cpp"
#include "gui.cpp"
