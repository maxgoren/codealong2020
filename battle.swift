//
//  battle.swift
//  swiftRogueTutorial
//
//  Created by max goren on 7/5/20.
//  Copyright © 2020 maxcodes. All rights reserved.
//

import Foundation

class Battle {
    var enemy: Entity
    var yourTurn: Bool
    init(oponent: Entity)
    {
        self.enemy = oponent
        self.yourTurn = false
    }
    
    func battleLoop() {
        
    }
    
    func enemyAttacks() {
        if self.yourTurn == false {
            //enemy takeAction()
            self.yourTurn = true;
        }
    }

}
