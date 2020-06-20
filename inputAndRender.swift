//
//  input.swift
//  swiftRogueTutorial
//
//  Created by max goren on 6/18/20.
//  Copyright © 2020 maxcodes. All rights reserved.
//

import Foundation

func keyReader() -> [String:(Int32,Int32)] {
    switch (tcod.key.vk) {
        case TCODK_UP:
            return ["move":(0, -1)]
        case TCODK_DOWN:
            return ["move":(0, 1)]
        case TCODK_LEFT:
            return ["move":(-1, 0)]
        case TCODK_RIGHT:
            return ["move":(1, 0)]
        case TCODK_ESCAPE:
            return ["exit":(0,0)]
        default: return ["unknown":(0,0)]
    }
}

//Declare some additional default colors that will be used in drawing map.
let dark_wall = TCOD_color_RGB(0, 0, 100)
let dark_ground = TCOD_color_RGB(50, 50, 150)

func drawAll(ents: [Entity]) {
    for y in 0..<gameMap.mapheight {
        for x in 0..<gameMap.mapwidth {
            let wall = gameMap.tiles[Int(x)][Int(y)].blockSight
            if wall == true {
                tcod.setCharBG(x: x, y: y, col: dark_wall)
            } else {
                tcod.setCharBG(x: x, y: y, col: dark_ground)
            }
        }
    }
    for ent in ents {
        drawEnt(ent: ent)
    }
    tcod.blit(xScr: 0, yScr: 0, wScr: width, hScr: height, xDst: 0, yDst: 0, fgalpha: 0.0, bgalpha: 0.0)
}

//say this five times fast:
func clearAll(ents: [Entity]) {
    for ent in ents {
        clearEnt(ent: ent)
    }
}
func drawEnt(ent: Entity) {
    tcod.putColorChar(x: ent.px, y: ent.py, char: ent.symbol, color: ent.color)
}

func clearEnt(ent: Entity) {
    tcod.putChar(x: ent.px, y: ent.py, char: " ")
}
