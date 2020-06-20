/*********************************************************
 *  TCOD-Wrapper.swift
 *  libTCOD implementation in swift for the development of
 *  ASCII or sprite/tile based, and especially,
 *  Rogue Like Games. more below
 *  -0bj3ct Disoriented.
 *  Created by max goren on 6/9/20.
 *  Copyright © 2020 max goren. MIT License (see at bottom)
 *  http://www.github.com/maxgoren maxgoren@icloud.com
 *(*)**(*)**************************************************
 * What Is/not here:
 * any variadic functions, the printf's etc, i did how ever implement a function
 * that will let us print strings (thank you, thank you, your too kind...)
 * Given Swifts vast string implementation it will more than do.
 * rectangles and all that have unfortunatley not been implemented
 * i may or may not get around to it.
 * what IS here is any function or type that is necessary to complete the
 * libtcod how to create a Rogue Like tutorial. Other functions that
 * you need implementing, should not be too difficult to implement
 * anybody that would like to help me improve this wrapper, please
 * get ahold of me on github (github.com/maxgoren) so we can keep everything
 * where others can benefit from our work! and most importantly, Have Fun!
 * -0bj3ct Disoriented
 *******************(8)**************************************/

import Foundation

///libTCOD made niiiice and Swift Friendly =)

class TCOD {
    // C typedef enum { }
    let bkgndf = TCOD_bkgnd_flag_t(rawValue: UInt32())
    let keyCode = TCOD_keycode_t(rawValue: UInt32())
    
    var console: UnsafeMutablePointer<TCOD_Console>?
    
    
    let TCrenderer = TCOD_renderer_t(1)
    
    var offscr_console: UnsafeMutablePointer<TCOD_Console>?
    var shuffle_console: UnsafeMutablePointer<TCOD_Console>?
    var mouse: UnsafeMutablePointer<TCOD_mouse_t>?
    var rng = TCOD_random_t.self
    let font_f = TCOD_font_flags_t(2)
    var key = TCOD_key_t()
    let colors = TCOD_color_t()
    var tileset_t = TCOD_tileset_new(32, 32)
    init()
    {
      
    }
    

    ///check console for event for keypress.
    func chkKeypress() -> Bool {
        let i: Int32 = Int32(TCOD_sys_check_for_event(Int32(Float(TCOD_EVENT_KEY_PRESS.rawValue)), &key, mouse).rawValue)
        if i > 0 {
            return true;
        }
        return false;
    }
    
    ///place a tile on the screen
    func putChar_ex(x: Int32, y: Int32, code: Int32) {
        TCOD_console_put_char_ex(tcod.console, x, y, code, TCOD_color_t(r: 255, g: 255, b: 255), TCOD_color_t(r: 0, g: 0, b: 0))

    }
    
    ///place a colored character on the screen. is that PC?
    func putColorChar(x: Int32, y: Int32, char: String, color: TCOD_color_t)
    {
        let toBeSent = char.cString(using: .utf8)
        TCOD_console_set_default_foreground(console, color)
        TCOD_console_put_char(console, x, y,Int32(toBeSent![0]), bkgndf)
    }
    
    ///display a char w/ random color on the screen
    func putRainbowChar(x: Int32, y: Int32, char: String) {
        let toBeSent = char.cString(using: .utf8)
        //print(toBeSent![0])
        TCOD_console_set_default_foreground(console, randColor())
        TCOD_console_put_char(console, x, y, Int32(toBeSent![0]), bkgndf)
    }
    
    ///Generates a randome R/G/B value for every character
    func printRainbowStr(x: Int32, y: Int32, str: String) {
        let pew = Array(str.unicodeScalars)
        var nextX = x
        for letters in 0...pew.count - 1 {
            TCOD_console_set_default_foreground(console, randColor())
            putChar(x: nextX, y: y, char: String(pew[letters]))
            nextX = nextX + 1
        }
    }
    
    ///display a character on the screen
    func putChar(x: Int32, y: Int32, char: String) {
        let toBeSent = char.cString(using: .utf8)
        //print(toBeSent![0])
        TCOD_console_put_char(console, x, y, Int32(toBeSent![0]), bkgndf)
    }
    
    ///same as putChar
    func setChar(x: Int32, y: Int32, ch: Int32)
    {
        TCOD_console_set_char(console, x, y, ch)
    }
    
    
    ///variadic functions not accesible via Swift, so this is our own
    func printStr(x: Int32, y: Int32, str: String) {
        let pew = Array(str.unicodeScalars)
        var nextX = x
        for letters in 0...pew.count - 1 {
            putChar(x: nextX, y: y, char: String(pew[letters]))
            nextX = nextX + 1
        }
    }
    
    ///set the background color of a char/tile
    func setCharBG(x: Int32, y: Int32, col: TCOD_color_t)
    {
        TCOD_console_set_char_background(console, x, y, col, TCOD_BKGND_SET)
    }
    
    ///set the background color of the console
    func setConsoleBG(col: TCOD_color_t) {
        TCOD_console_set_default_background(console, col)
        
    }
    
    
    
    ///default current: 1, Desired: 2? i havent put much thought into this...
    func shuffleConsoles(current: Int, Desired: Int)
    {
        var tmp: UnsafeMutablePointer<TCOD_Console>?
        tmp = console
        console = offscr_console
        shuffle_console = tmp
        //jesus fucking christ.... im gonna have to put more thought into this
    }
    
    ///blit le console
    func blit(xScr: Int32, yScr: Int32, wScr: Int32, hScr: Int32, xDst: Int32, yDst: Int32, fgalpha: Float, bgalpha: Float)
    {
        TCOD_console_blit(console, xScr, yScr, wScr, hScr, nil, xDst, yDst, fgalpha, bgalpha)
    }
    
    
    ///load tilesheet from file
    func loadTileSet(path: String, col: Int32, row: Int32, n: Int32) -> TCOD_Tileset {
       let Tfile = TCOD_tileset_load(path, col, row, n, nil).pointee
        return Tfile
    }
    
    
    func loadFont(path: UnsafePointer<Int8>!, flags: TCOD_font_flags_t, charH: Int32, charV: Int32) {
        
        TCOD_console_set_custom_font(path, Int32(flags.rawValue), charH, charV)
    }
    
    func setAsciiCodes(sRow: Int32, eRow: Int32, stride: Int32, sChar: Int32)
    {
        var a = sChar
        for t in sRow...eRow {
            TCOD_console_map_ascii_codes_to_font(Int32(a), stride, 0, Int32(t))
            a += stride
        }
    }
    
    ///map a tile to an ascii code
    func setTileCode(code: Int32, chrX: Int32, chrY: Int32) {
        TCOD_console_map_ascii_code_to_font(code, chrX, chrY)
    }
    
    ///sets up the console root screen for the game
    func initRoot(w: Int32, h: Int32, title: String)
    {
       let _ = TCOD_console_init_root(w, h, title, false, TCrenderer)
    }
    
    ///make a frama around the window
    func frame(x: Int32, y: Int32, w: Int32, h: Int32, n: Int32, title: String, fg: UnsafePointer<TCOD_color_t>, bg: UnsafePointer<TCOD_color_t>, empty: Bool) {
        TCOD_console_printn_frame(console, x, y, w, h, n, title, fg, bg, bkgndf, empty)
    }
    
    ///draw a vertical line
    func vLine(x: Int32, y: Int32, length: Int32) {
        TCOD_console_vline(console, x, y, length, bkgndf)
    }
    
    ///draw a horizontal line
    func hLine(x: Int32, y: Int32, length: Int32) {
        TCOD_console_hline(console, x, y, length, bkgndf)
    }
    
    ///make the console a rectangle, clear is a bool to clear it or not.
    func rect(x: Int32, y: Int32, w: Int32, h: Int32, clear: Bool)
    {
        TCOD_console_rect(console, x, y, w, h, clear, bkgndf)
    }
    
    
    ///returns if the console window is open or not
    func windowisClosed() -> Bool
    {
        let yesno: Bool = TCOD_console_is_window_closed()
        return yesno
    }

    ///sets color of charachter ch is ascii code for char
    func setCharFG(x: Int32, y: Int32, ch: Int32, col: TCOD_color_t)
    {
        TCOD_console_set_char_foreground(console, x,y, col)
    }
    

    /*
    func setDefaultFG(col: OpaquePointer?) {
        TCOD_console_set_default_foreground(console, boogaloo)
    }*/
    
    ///lib tcods RNG - native Swfit works better.
    func rndGetInstance() -> TCOD_random_t
    {
        return TCOD_random_get_instance()
        
    }
    
    func randColor() -> TCOD_color_t
    {
        return TCOD_color_t(r: UInt8.random(in: 0...255), g: UInt8.random(in: 0...255), b: UInt8.random(in: 0...255))
    }
    
    func getRandInt(min: Int, max: Int) -> Int
    {
        return Int.random(in: min...max)
    }
    ///same as getRandom
    func getInt32(min: Int32, max: Int32) -> Int32
    {
        return Int32.random(in: min...max)
    }
    
    ///Our own random number generator using Swift,
    func getRandom(high: Int32, low: Int32) -> Int32
    {
        return Int32.random(in: high...low)
    }
    
    func timeOut(amt: UInt32) {
        TCOD_sys_sleep_milli(amt)
    }
    
    ///clears console before displaying
    func consoleClear()
    {
       TCOD_console_clear(console)
    }
    
    ///must be called before program exits
    func quit()
    {
        TCOD_quit();
    }
    
    ///flush the console
    func flush()
    {
        TCOD_console_flush()
        
    }
}
/* I tried to do this differently, i tried a million ways */
/* swift is really advanced and strong in some areas, but */
/* it continues to suprise me with its odd quirks, especially when it comes*/
/* to passing types and type conversions when dealing with C libraries */
/* so all of the predefined colors in libtcod are useless to us */
/* but we do still have the ability to create and define our own*/
/* and that IS what this wrapper is all about, right? */

    let stcodGreen = TCOD_ColorRGB(r: 0, g: 255, b: 0)
    let stcodGrey = TCOD_ColorRGB(r: 128, g: 128, b: 128)
    let stcodRed = TCOD_ColorRGB(r: 255, g: 0, b: 0)
    let stcodBlue = TCOD_ColorRGB(r: 0, g: 0, b: 255)
    let stcodYellow = TCOD_ColorRGB(r: 255, g: 255, b: 0)
    let stcodPurple = TCOD_ColorRGB(r:128, g: 0, b: 128)
    let stcodWhite = TCOD_ColorRGB(r: 255, g: 255, b: 255)
    let stcodLime = TCOD_ColorRGB(r: 0,g: 255, b: 0)
    let stcodFuscia = TCOD_ColorRGB(r: 255, g: 0, b: 255)


class tcodbsp {

    let pos: Int32 = 0
    let lvl: UInt8 = 0
    let hzntl: Bool = false
    var tree = TCOD_tree_new()
    var bsp_t = TCOD_bsp_new()
    
    init()
    {
       print("soid mate")
    }
    
    func splitRecursive(randomizer: TCOD_random_t, nb: Int32, minHsz: Int32, minVsz: Int32, maxHRat: Float, maxVRat: Float)
    {
        TCOD_bsp_split_recursive(bsp_t, randomizer, nb, minHsz, minVsz, maxHRat, maxVRat)
    }
    
   /* func TCOD_callbacck() -> TCOD_bsp_callback_t
    {
        
        return TCOD_bsp_callback_t
    }*/
    
    ///This is something your better off implementing on your own. i quick hacked it.
    func traverseInvLayerOrder(/*comingsoong */)
    {
        TCOD_bsp_traverse_inverted_level_order(bsp_t, nil, nil) //wishful thinking?
        //TCOD_bsp_traverse_inverted_level_order(bsp_t, TCOD_bsp_callback_t?, 0)
    }
}


///tcod map class
class tcodmap {
    //well fuck me, that was simple.
    var w: Int32
    var h: Int32
    var map: TCOD_map_t
    var alg: TCOD_fov_algorithm_t
    
    init(w: Int32, h: Int32, algo: UInt32)
    {
      self.map  = TCOD_map_new(w, h)
      self.w = w
      self.h = h
      self.alg = TCOD_fov_algorithm_t.init(rawValue: algo)
    }
    
    ///only ghosts walk through walls.
    func isWalkable(x: Int32, y: Int32) -> Bool {
        let yesno = TCOD_map_is_walkable(map, x, y)
        return yesno
    }
    
    ///is <x> in our FOV
    func isInFov(x: Int32, y: Int32) -> Bool {
        let yesno = TCOD_map_is_in_fov(map, x, y)
        return yesno
    }
    
    ///self descriptive
    func computeFov(playerx: Int32, playery: Int32, rad: Int32, lwalls: Bool) {
       TCOD_map_compute_fov(map, playerx, playery, rad, lwalls, alg)
    }
    
    ///set properties
    func setProps(x: Int32, y: Int32, transparent: Bool, walkable: Bool)
    {
        TCOD_map_set_properties(map, x, y, transparent, walkable)
    }
}

class tcodImage {
    
    var img: TCOD_image_t
    var w: Int32
    var h: Int32
    
    
    init(w: Int32, h: Int32)
    {
        self.w = w
        self.h = h
        self.img = TCOD_image_new(w, h)
    }
    
    ///remember brisk ice tea? Its blit2x babbyyyy
    func blitTwice(x: Float, y: Float, scalex: Float, scaley: Float, angle: Float)
    {
        TCOD_image_blit(img, tcod.console, x, y, tcod.bkgndf, scalex, scaley, angle)
    }
}


/*********************************
 
 MIT License
 
 Copyright (c) 2020 Max Goren
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
