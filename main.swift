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
tcod.initRoot(w: width, h: height, title: title)
tcod.consoleClear()
var playerx: Int32 = width / 2
var playery: Int32 = height / 2
tcod.putChar(x: playerx, y: playery, char: "@")
tcod.flush()


while(tcod.windowisClosed() == false)
{
    if (tcod.chkKeypress()) {
       
        switch (tcod.key.vk) {
        case TCODK_UP:
            playery -= 1; tcod.consoleClear()
        case TCODK_DOWN:
            playery += 1; tcod.consoleClear()
        case TCODK_LEFT:
            playerx -= 1; tcod.consoleClear()
        case TCODK_RIGHT:
            playerx += 1; tcod.consoleClear()
        default: if (true) { }
        }
        tcod.putChar(x: playerx, y: playery, char: "@")
        tcod.flush()
    }
}
