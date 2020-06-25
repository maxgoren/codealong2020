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
    //base values we will pass to the object as it is initialized.
    init(x: Int32, y: Int32, char: String, color: TCOD_color_t)
    {
        self.px = x
        self.py = y
        self.symbol = char
        self.color = color
    }
    
    //a function to move the object around
    func move(x: Int32, y: Int32)
    {
        self.px += x
        self.py += y
    }
}
