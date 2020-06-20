//
//  main.swift
//  swiftRogueTutorial
//
//  Created by max goren on 6/16/20.
//  Copyright © 2020 maxcodes. All rights reserved.
//

import Foundation

let tcod = TCOD()
let title: String = "Swift Rogue Like Tutorial"
let width: Int32 = 80
let height: Int32 = 40
let maxWidth: Int32 = 75
let maxHeight: Int32 = 35
tcod.initRoot(w: width, h: height, title: title)
tcod.consoleClear()
let player = Entity(x: 33, y: 19, char: "@", color: stcodFuscia)
let npc = Entity(x: (width / 2) - 5, y: (height / 2) - 1, char: "N", color: stcodBlue)
var ents = [player, npc]
let gameMap = GameMap(width: maxWidth, height: maxHeight)

drawAll(ents: ents)
tcod.flush()

var retVal = [String:(Int32, Int32)]()
var (chgx, chgy) = (Int32(0),Int32(0))
while(tcod.windowisClosed() == false)
{
    if (tcod.chkKeypress()) {
        retVal = keyReader()
        for key in retVal.keys {
            if key == "move" {
                (chgx, chgy) = retVal["move"] ?? (0,0)
                if gameMap.is_blocked(x: player.px + chgx, y: player.py + chgy) == false {
                    player.move(x: chgx, y: chgy)
                }
            }
            if key == "exit" {
                tcod.quit()
                exit(0)
            }
        }
    }
    drawAll(ents: ents)
    tcod.flush()
    clearAll(ents: ents)
    
}
