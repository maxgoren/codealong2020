//
//  rendering.swift
//  swiftRogueTutorial
//
//  Created by max goren on 6/18/20.
//  Copyright © 2020 maxcodes. All rights reserved.
//

import Foundation

struct Rectangle {
    let x1: Int32
    let x2: Int32
    let y1: Int32
    let y2: Int32
    var centX: Int32
    var centY: Int32
    init(x: Int32, y: Int32, width: Int32, height: Int32)
    {
        self.x1 = x
        self.y1 = y
        self.x2 = x + width
        self.y2 = y + height
        self.centX = (self.x1 + self.x2) / 2
        self.centY = (self.y1 + self.y2) / 2
    }
    
    func collision(other: Rectangle) -> Bool {
        if (self.x1 <= other.x2 && self.x2 >= other.x1 &&
            self.y1 <= other.y2 && self.y2 >= other.y1) {
            print("Collison!")
            return true
        }
        return false
    }
    
    func center() -> (Int32, Int32) {
        return (centX, centY)
    }
}

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
    var rooms = [Rectangle]()
    var numRooms: Int
    var newX: Int32, newY: Int32, prevX: Int32, prevY: Int32
    init(mwidth: Int32, mheight: Int32)
    {
        self.newX = 0; self.newY = 0; self.prevX = 0; self.prevY = 0
        self.mapwidth = mwidth
        self.mapheight = mheight
        self.numRooms = 0
        self.tiles = self.makeTiles()
    }
    
    
    //create an 2d array and populate it with tiles to represent
    //the map of our game
    func makeTiles() -> [[Tile]] {
        tiles = Array(repeating: Array(repeating: Tile(true, true), count: Int(self.mapheight)), count: Int(self.mapwidth))
        return tiles
    }
    
    //carve out rectangular chunks of "unblocked" rooms
    func makeRoom(dim: Rectangle) {
        for x in dim.x1 + 1..<dim.x2 {
            for y in dim.y1 + 1..<dim.y2 {
                self.tiles[Int(x)][Int(y)].blocked = false
                self.tiles[Int(x)][Int(y)].blockSight = false
                
            }
        }
        
    }
    
    

    
    
    
    
    
    ///tunnel between rooms horizontally
    func makeHtunnel(x1: Int32, x2: Int32, y: Int32) {
        if x1 < x2 + 1 {
            for x in x1...x2 + 1 {
                self.tiles[Int(x)][Int(y)].blocked = false
                self.tiles[Int(x)][Int(y)].blockSight = false
            }
        } else {
            for x in x2 + 1...x1{
                self.tiles[Int(x)][Int(y)].blocked = false
                self.tiles[Int(x)][Int(y)].blockSight = false
            }
        }
    }
    
    ///tunnel between rooms vertically
    func makeVtunnel(y1: Int32, y2: Int32, x: Int32) {
        if (y1 <= y2)
        {
          for y in y1...y2 + 1 {
             self.tiles[Int(x)][Int(y)].blocked = false
             self.tiles[Int(x)][Int(y)].blockSight = false
          }
        } else {
            for y in y2 + 1...y1 {
             self.tiles[Int(x)][Int(y)].blocked = false
             self.tiles[Int(x)][Int(y)].blockSight = false
            }
        }
    }
    
    func makeMap() {
        for t in 0..<maxRooms {
            print("makeMap Loop #: \(t)")
            let w = tcod.getRandInt(min: Int(roomMinSize), max: Int(roomMaxSize))
            let h = tcod.getRandInt(min: Int(roomMinSize), max: Int(roomMaxSize))
            let x = tcod.getRandInt(min: 0, max: Int(self.mapwidth) - w - 1)
            let y = tcod.getRandInt(min: 0, max: Int(self.mapheight) - h - 1)
            let newRoom = Rectangle(x: Int32(x), y: Int32(y), width: Int32(w), height: Int32(h))
            if (numRooms == 0) {
                self.makeRoom(dim: newRoom); rooms.append(newRoom); numRooms += 1
                
            }
            for otros in 0..<rooms.count {
                if newRoom.collision(other: rooms[otros]) == true {
                    break;
                } else {
                    self.makeRoom(dim: newRoom)
                    (self.newX, self.newY) = newRoom.center()
                    if numRooms == 0 {
                        (player.px, player.py) = (self.prevX, self.prevY)
                    } else {
                        (self.prevX, self.prevY) = rooms[self.numRooms - 1].center()
                    }
                    if tcod.getRandInt(min: 0, max: 1) == 1 {
                        self.makeHtunnel(x1: self.prevX, x2: self.newX, y: self.prevY)
                        self.makeVtunnel(y1: self.prevY, y2: self.newY, x: self.newX)
                    } else {
                        self.makeVtunnel(y1: self.prevY, y2: self.newY, x: self.prevX)
                        self.makeHtunnel(x1: self.prevX, x2: self.newX, y: self.newY)
                    }
                }
                rooms.append(newRoom)
                numRooms += 1
                print("Room added! numRooms = \(numRooms)")
            }
        }
}
    
    //returns the blocking state of the tile queried
    func is_blocked(x: Int32, y: Int32) -> Bool {
        if self.tiles[Int(x)][Int(y)].blocked == true {
            return true
        }
        return false
    }
   
}
