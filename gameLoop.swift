//
//  gameLoop.swift
//  swiftRogueTutorial
//
//  Created by max goren on 6/20/20.
//  Copyright © 2020 maxcodes. All rights reserved.
//

import Foundation


func gameLoop() -> Int
{
    //stup dictionary for return value of keyReader()
    var retVal = [String:(Int32, Int32)]()  // i always that Tuple
    var (chgx, chgy) = (Int32(0),Int32(0))  //was such a pretty name.
    while(tcod.windowisClosed() == false)
    {
      if (tcod.chkKeypress()) {
        retVal = keyReader()
        for key in retVal.keys {
            if key == "move" {
              (chgx, chgy) = retVal["move"] ?? (0,0)
              if gameMap.is_blocked(x: player.px + chgx, y: player.py + chgy) == false {
                player.move(x: chgx, y: chgy)
                fovRecompute = true
              }
            }
            if key == "exit" {
                tcod.quit()
                exit(0)
            }
            if key == "tochoff" {
                
            }
        }
        if fovRecompute { fovMap.computeFov(playerx: player.px, playery: player.py, rad: 10, lwalls: true) }
        drawAll(ents: gameMap.monsters)
        fovRecompute = false
        tcod.flush()
        clearAll(ents: gameMap.monsters)
        tcod.consoleClear()
        }
    }
    return 420
}
