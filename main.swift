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
let width: Int32 = 80   //absolute console width
let height: Int32 = 40  //asbsolute console height
let maxWidth: Int32 = width - 2   //map width
let maxHeight: Int32 = height - 5  //map height
let roomMaxSize: Int32 = 12 //largest diameter a room can be
let roomMinSize: Int32 = 6 // smallest "      "
let maxRooms = 20        //max number of rooms for our makeMap algo
let fovAlgo: UInt32 = 2          //libtcod offers several different fov algo's
let fovLitWalls = 0
let fovRad = 20
var fovRecompute: Bool = true;

tcod.initRoot(w: width, h: height, title: title)

let player = Entity(x: (width / 2), y: (height / 2), char: "@", color: stcodFuscia)
let npc = Entity(x: (width / 2) - 5, y: (height / 2) - 1, char: "N", color: stcodBlue)
var ents = [player, npc]
var gameMap = GameMap(mwidth: maxWidth, mheight: maxHeight)
var fovMap = tcodmap(w: gameMap.mapwidth, h: gameMap.mapheight, algo: fovAlgo)

gameMap.makeMap()
drawAll(ents: ents)
tcod.flush()

let _ = gameLoop()
