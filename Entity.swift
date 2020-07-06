//
//  Entity.swift
//  swiftRogueTutorial
//
//  Created by max goren on 6/18/20.
//  Copyright © 2020 maxcodes. All rights reserved.
//

import Foundation
//A building block for populating our map with objects and characters
class Entity {
    var px: Int32  //X and Y coordinates of our object
    var py: Int32
    let symbol: String //the symbol that will represent the object on the console
    let color: TCOD_color_t //the color that symbol will appear as.
    let name: String
    var inBattle: Bool = false
    init(x: Int32, y: Int32, char: String, name: String, color: TCOD_color_t)
    {
        self.name = name
        self.px = x
        self.py = y
        self.symbol = char
        self.color = color
    }
    
    //a function to move the object around
    func move(x: Int32, y: Int32)
    {
        if gameMap.is_populated(x: self.px + x, y: self.py + y) == false {
            self.px += x
            self.py += y
        } else {
            for i in gameMap.monsters {
                if (i.px, i.py) == (self.px + x, self.px + y) {
                    print("A \(i.name) has smelled your advance, the fight is on!")
                    self.inBattle = true;
                    i.inBattle =  true;
                    let fightclub = Battle(oponent: i)
                    fightclub.battleLoop()
                }
            }
        }
    }
}
