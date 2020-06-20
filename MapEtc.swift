//
//  rendering.swift
//  swiftRogueTutorial
//
//  Created by max goren on 6/18/20.
//  Copyright © 2020 maxcodes. All rights reserved.
//

import Foundation

struct Tile {
    var blocked: Bool
    var blockSight: Bool
    init(_ blocked: Bool, _ block_sight: Bool)
    {
        self.blocked = blocked
        self.blockSight = block_sight
    }
}

class GameMap {
    let mapwidth: Int32
    let mapheight: Int32
    var tiles = [[Tile]]()
    init(width: Int32, height: Int32)
    {
        self.mapwidth = width
        self.mapheight = height
        self.tiles = self.makeTiles()
        self.blockAfew()
    }
    
    func blockAfew() {

    }
    
    func makeTiles() -> [[Tile]] {
        tiles = Array(repeating: Array(repeating: Tile(false, false), count: Int(self.mapheight)), count: Int(self.mapwidth))
        tiles[22][19].blocked = true
        tiles[22][19].blockSight = true
        tiles[23][19].blocked = true
        tiles[23][19].blockSight = true
        return tiles
    }
    
    func is_blocked(x: Int32, y: Int32) -> Bool {
        if self.tiles[Int(x)][Int(y)].blocked == true {
            return true
        }
        return false
    }
   
}
